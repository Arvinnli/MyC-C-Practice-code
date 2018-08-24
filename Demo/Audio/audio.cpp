// #include <atlstr.h>
#include<algorithm>
#include <DSound.h>
#include <WINNT.H>
#include <mmsystem.h>   
#include "audio.h"
#include <cguid.h>
#include <devguid.h>

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
 
#define BUFFER_SIZE (44100*16*2/8*5)	// 录制声音长度
#define FRAGMENT_SIZE 1024				// 缓存区大小
#define FRAGMENT_NUM 4					// 缓存区个数


static unsigned char buffer[BUFFER_SIZE] = {0};
static int buf_count = 0;
 
// 函数定义
void CALLBACK waveInProc(HWAVEIN hwi,      
						 UINT uMsg,         
						 DWORD_PTR dwInstance,  
						 DWORD_PTR dwParam1,  
						 DWORD_PTR dwParam2     );
void CALLBACK waveOutProc(  HWAVEOUT hwo,   
						  UINT uMsg,         
						  DWORD_PTR dwInstance,   
						  DWORD_PTR dwParam1,    
						  DWORD_PTR dwParam2     );
 
// 入口
int main()
{
	/* 录音 */
	// Device
	int nReturn = waveInGetNumDevs();
	printf("input device num:%d\n", nReturn);
	for (int i=0; i<nReturn; i++)
	{
		WAVEINCAPS wic;
		waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS));
		printf("#%d\tdevice name:%s\n", i, wic.szPname);
	}
 
	// open
	HWAVEIN hWaveIn;
	WAVEFORMATEX wavform;
	wavform.wFormatTag = WAVE_FORMAT_PCM;
	wavform.nChannels = 2;
	wavform.nSamplesPerSec = 44100;
	wavform.nAvgBytesPerSec = 44100*16*2/8;
	wavform.nBlockAlign = 4;
	wavform.wBitsPerSample = 16;
	wavform.cbSize = 0;
 
	WAVEINCAPS wic;

	/* 放音 */
	
	// Device
	nReturn = waveOutGetNumDevs();
	printf("\noutput device num:%d\n", nReturn);
	for (int i=0; i<nReturn; i++)
	{
		WAVEOUTCAPS woc;
		waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS));
		printf("#%d\tdevice name:%s\n", i, wic.szPname);
	}
 
	// open
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wavform, (DWORD_PTR)waveOutProc, 0, CALLBACK_FUNCTION);
 
	WAVEOUTCAPS woc;
	waveOutGetDevCaps((UINT_PTR)hWaveOut, &woc, sizeof(WAVEOUTCAPS));
	printf("opened device name:%s\n", wic.szPname);
 
	// prepare buffer
	WAVEHDR wavhdr;
	wavhdr.lpData = (LPSTR)buffer;
	wavhdr.dwBufferLength = BUFFER_SIZE;
	wavhdr.dwFlags = 0;
	wavhdr.dwLoops = 0;
 
	waveOutPrepareHeader(hWaveOut, &wavhdr, sizeof(WAVEHDR));
 
	// play
	printf("Start to Play...\n");
 
	buf_count = 0;
	waveOutWrite(hWaveOut, &wavhdr, sizeof(WAVEHDR));
	// while (buf_count < BUFFER_SIZE)
	// {
	// 	Sleep(1);
	// }
 
	// clean
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &wavhdr, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
 
	printf("Play Over!\n\n");
 
	return 0;
}
 
// 录音回调函数
void CALLBACK waveInProc(HWAVEIN hwi,      
						 UINT uMsg,         
						 DWORD_PTR dwInstance,  
						 DWORD_PTR dwParam1,  
						 DWORD_PTR dwParam2     )
{
	LPWAVEHDR pwh = (LPWAVEHDR)dwParam1;
 
	if ((WIM_DATA==uMsg) && (buf_count<BUFFER_SIZE))
	{
		int temp = BUFFER_SIZE - buf_count;
		temp = (temp>pwh->dwBytesRecorded) ? pwh->dwBytesRecorded : temp;
		memcpy(buffer+buf_count, pwh->lpData, temp);
		buf_count += temp;
		
		waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));
	}
}
 
// 放音回调函数
void CALLBACK waveOutProc(  HWAVEOUT hwo,   
						  UINT uMsg,         
						  DWORD_PTR dwInstance,   
						  DWORD_PTR dwParam1,    
						  DWORD_PTR dwParam2     )
{
	if (WOM_DONE == uMsg)
	{
		buf_count = BUFFER_SIZE;
	}
}