/*
http://sdr-reu.wikispaces.com/file/view/SoundIn.c
File to read sound from sound card and record it to a file in PCM format.
*/

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <conio.h>

#pragma comment(lib, "winmm.lib")

#define IN_BUFFERS_NUMBER 4 //开辟三个数据缓冲区
#define REC_STATUS_STARTING_RECORD 1
#define REC_STATUS_RECORDING 2
#define REC_STATUS_ALL_DONE -2  //录音完成
#define REC_STATUS_FINISHING -1 //即将完成
#define REC_STATUS_FAIL -3
#define SIZE_OF_WAVEHDR 32 //wave头大小

//函数
void FreeBuffers(WAVEHDR *buffers);
DWORD WINAPI waveInProc(LPVOID threadControls);

typedef struct soundInDataAndControls
{
    WAVEHDR buffers[IN_BUFFERS_NUMBER]; //开辟三个数据缓冲区
    int recordingStatus;                //录音状态
    HWAVEIN inWaveDevice;   //句柄
    int buffers_left; //可用内存数目
} SoundThreadInfo;

WAVEFORMATEX sampleFormat; //全局变量
char *outfilename;
HMMIO m_hFile;
MMCKINFO m_MMCKInfoData;
MMCKINFO m_MMCKInfoParent;
MMCKINFO m_MMCKInfoChild;

int main()
{
    MMRESULT errorResult = 0;
    SoundThreadInfo soundIn;
    HANDLE inWaveThreadHandle;                //线程
    int x = 0;                                //计数器
    soundIn.recordingStatus = 0;              //设置录音状态
    soundIn.buffers_left = IN_BUFFERS_NUMBER; //设置预期缓冲数量
    outfilename = ".\\1.wav";

    inWaveThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)waveInProc, /*参数*/ &soundIn, 0, &errorResult); //创建线程
    if (!inWaveThreadHandle)
    {
        printf("Can't create sound in thread! -- %08X\n", GetLastError());
        return 0;
    }
    CloseHandle(inWaveThreadHandle); //关闭线程

    for (x = 0; x < IN_BUFFERS_NUMBER; x++) //清空缓存
    {
        ZeroMemory(&soundIn.buffers[x], SIZE_OF_WAVEHDR);
    }

    //设置 waveFormat
    sampleFormat.wFormatTag = WAVE_FORMAT_PCM;
    sampleFormat.nChannels = 2; //声道
    sampleFormat.nSamplesPerSec = 44100;
    sampleFormat.wBitsPerSample = 16;
    sampleFormat.nBlockAlign = sampleFormat.nChannels * (sampleFormat.wBitsPerSample >> 3);
    sampleFormat.nAvgBytesPerSec = sampleFormat.nSamplesPerSec * sampleFormat.nBlockAlign;

    if (!CreateWaveFile())
    {
        return getchar();
    }

    //分配 memory sound in buffers.
    for (x = 0; x < IN_BUFFERS_NUMBER; x++) //this loop is not need after testing
    {                                       //can be replaced with hard coded buffer allocation
        //clear waveheaders
        ZeroMemory(&soundIn.buffers[x], SIZE_OF_WAVEHDR);
        soundIn.buffers[x].dwBufferLength = sampleFormat.nAvgBytesPerSec << 2; //内存大小估计一块
        soundIn.buffers[x].dwFlags = 0;
        soundIn.buffers[x].lpData = (char *)VirtualAlloc(NULL, soundIn.buffers[0].dwBufferLength, MEM_COMMIT, PAGE_READWRITE); //申请内存

        if (soundIn.buffers[x].lpData == NULL)
        {
            printf("Sound In Buffer number %d failed to get allocate memory.\n", x);

            for (--x; x; x--) // start 1 down, and while x!=0 x--
            {
                VirtualFree(soundIn.buffers[x].lpData, 0, MEM_RELEASE); //释放内存
            }
            return 0;
        }
        else
        {
            printf(" %d Buffer Application  sucsess\n", x);
        }
    }

    //open wave device
    errorResult = waveInOpen(&soundIn.inWaveDevice, WAVE_MAPPER, &sampleFormat, (DWORD)errorResult, 0, CALLBACK_THREAD);
    if (errorResult != MMSYSERR_NOERROR)
    {
        FreeBuffers(soundIn.buffers);
        return getchar();
    }

    // buffers and queue them
    for (x = 0; x < IN_BUFFERS_NUMBER; x++)
    {
        errorResult = waveInPrepareHeader(soundIn.inWaveDevice, &soundIn.buffers[x], SIZE_OF_WAVEHDR);
        if (errorResult != MMSYSERR_NOERROR)
        {
            printf("Failed to prepare header %d. Error %d\n", x, errorResult);
            //fprintf(std,"Last was %s
            FreeBuffers(soundIn.buffers);
            errorResult = waveInClose(soundIn.inWaveDevice);
            if (errorResult)
            {
                printf("Can't Close Wave Device!\n");
                getchar();
            }
            return 0;
        }

        errorResult = waveInAddBuffer(soundIn.inWaveDevice, &soundIn.buffers[x], SIZE_OF_WAVEHDR);
        if (errorResult != MMSYSERR_NOERROR)
        {
            printf("Failed to queue wave buffer %d.\n", x);
            soundIn.buffers_left--;
            if (soundIn.buffers_left < 2)
            {
                FreeBuffers(soundIn.buffers);
                errorResult = waveInClose(soundIn.inWaveDevice);
                if (errorResult)
                {
                    printf("Can't Close Wave Device!\n");
                    getchar();
                }
                return 0;
            }
        }
    }
    //set record flag
    printf("Hit any key to begin recording.\n");
    getchar();
    soundIn.recordingStatus = 1; //1 == starting recording

    //start recording
    errorResult = waveInStart(soundIn.inWaveDevice);
    if (errorResult == MMSYSERR_NOERROR)
    {
        //wait for user to stop recording
        printf("Hit any key to stop recording.\n");
        getchar();
        soundIn.recordingStatus = REC_STATUS_FINISHING;
    }
    else
    {
        //Recording never started.
        soundIn.recordingStatus = REC_STATUS_ALL_DONE;
    }
    //reset headers
    waveInReset(soundIn.inWaveDevice); //this should send a MM_WIM_DONE for each of the buffers/headers

    //wait thread
    while ((soundIn.recordingStatus != REC_STATUS_ALL_DONE)) //status -2 is finished
    {
        Sleep(100); //tenth of a second
        printf("Waiting for all done.\n");
        printf("Recording status = %d\n", soundIn.recordingStatus);
    }

    //un prepare the buffers
    for (x = 0; x < IN_BUFFERS_NUMBER; x++)
    {
        errorResult = waveInUnprepareHeader(soundIn.inWaveDevice, &soundIn.buffers[x], SIZE_OF_WAVEHDR);
        if (errorResult != 0)
        {
            printf("Failed to unprepare wave header.\n");
        }
    }
    //deallocate memory
    FreeBuffers(soundIn.buffers);

    mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
    mmioAscend(m_hFile, &m_MMCKInfoParent, 0);

    //close wave device
    errorResult = waveInClose(soundIn.inWaveDevice);
    if (errorResult)
    {
        printf("Can't Close Wave Device!\n");
        getchar();
    }
    return getchar();
}

void FreeBuffers(WAVEHDR *buffers)
{
    int x;
    for (x = 0; x < IN_BUFFERS_NUMBER; x++)
    {
        VirtualFree(buffers[x].lpData, 0, MEM_RELEASE); //zero meams all memory
    }
}

int CreateWaveFile()
{
    MMRESULT mmResult = 0;

    ZeroMemory(&m_MMCKInfoParent, sizeof(MMCKINFO));
    ZeroMemory(&m_MMCKInfoChild, sizeof(MMCKINFO));
    ZeroMemory(&m_MMCKInfoData, sizeof(MMCKINFO));

    m_hFile = mmioOpen(outfilename, NULL, MMIO_CREATE | MMIO_WRITE | MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
    if (m_hFile == NULL)
    {
        return getchar();
    }

    m_MMCKInfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mmResult = mmioCreateChunk(m_hFile, &m_MMCKInfoParent, MMIO_CREATERIFF);
    m_MMCKInfoChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
    m_MMCKInfoChild.cksize = sizeof(WAVEFORMATEX) + sampleFormat.cbSize;
    mmResult = mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
    mmResult = mmioWrite(m_hFile, (char *)&sampleFormat, sizeof(WAVEFORMATEX) + sampleFormat.cbSize);
    mmResult = mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
    m_MMCKInfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mmResult = mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
    return 1;
}

DWORD WINAPI waveInProc(void *threadControls)
{
    MSG msg;
    SoundThreadInfo *inFORMATION = (SoundThreadInfo *)threadControls;
    MMRESULT errorResult;
    int outputlenth = 0;

    while (GetMessage(&msg, 0, 0, 0) == 1) //得到一消息
    {
        if (msg.message == MM_WIM_DATA)
        {
            printf("Data amount %d\n", ((WAVEHDR *)msg.lParam)->dwBytesRecorded);
            //collect data
            if (inFORMATION->recordingStatus != 0) //recording not began or stopped只有0 ，-1 -2 三个值
            {

                if (inFORMATION->recordingStatus == REC_STATUS_ALL_DONE)
                {
                    printf("Possible error recieving WIM_DATA during condition ALL_DONE\n");
                    break; //time for thread to end
                }

                outputlenth = mmioWrite(m_hFile, ((WAVEHDR *)msg.lParam)->lpData, ((WAVEHDR *)msg.lParam)->dwBytesRecorded);
                if (outputlenth == ((WAVEHDR *)msg.lParam)->dwBytesRecorded)
                {
                    printf("sucsess save data_dwBytesRecorded %d\n", outputlenth);
                    printf("sucsess save data_dwBufferLength  %d\n", ((WAVEHDR *)msg.lParam)->dwBufferLength);
                }

                //was this that last block the user wanted.
                if (inFORMATION->recordingStatus == REC_STATUS_FINISHING)
                {
                    //the buffers are each sent back, but not requeue
                    if (--inFORMATION->buffers_left == 0)
                    {
                        inFORMATION->recordingStatus = REC_STATUS_ALL_DONE;
                    }
                    printf("Buffer finished.\n");
                    continue;
                }
            }
            //if stopped it only requeue s the buffer and continues.
            //requeue buffer
            if (!waveInAddBuffer(inFORMATION->inWaveDevice, (WAVEHDR *)msg.lParam, SIZE_OF_WAVEHDR))
            {
                if (!waveInAddBuffer(inFORMATION->inWaveDevice, (WAVEHDR *)msg.lParam, SIZE_OF_WAVEHDR))
                {
                    printf("Buffer requeue error.\n");

                    if (--inFORMATION->buffers_left < 2)
                    {
                        FreeBuffers(inFORMATION->buffers);
                        printf("in requeue error device.");
                        errorResult = waveInClose(inFORMATION->inWaveDevice);
                        if (errorResult)
                        {
                            printf("Can't Close Wave Device!\n");
                            getchar();
                        }
                        return 0;
                        inFORMATION->recordingStatus = REC_STATUS_FINISHING;
                        //finishing means takes the queued blocks and no more
                        //in thoery the next block (the last one) that was queue
                        //previously
                        mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
                        mmioAscend(m_hFile, &m_MMCKInfoParent, 0);
                        return -1;
                    }
                }
            }
        }
    }
    return 1;
}