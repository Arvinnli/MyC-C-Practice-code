
// #pragma comment(lib,"avrt.lib")
#include <windows.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <iostream>

#include <avrt.h>
#include <mmsystem.h>

#include <mmreg.h>
#include <ksmedia.h>


class CSoundCardAudioCapture
{

public:

	CSoundCardAudioCapture()
	{
		m_pAudioCaptureClient = NULL;
		m_pAudioClient = NULL;
		m_pMMDevice = NULL;
		m_hEventStop = NULL;
		m_hTimerWakeUp = NULL;
		m_hTask = NULL;
		m_pwfx = NULL;
	}

	int StartCapture()
	{
		CoInitialize(NULL);
		IMMDeviceEnumerator *pMMDeviceEnumerator = NULL;
		HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, 
									__uuidof(IMMDeviceEnumerator),(void**)&pMMDeviceEnumerator);
		REFERENCE_TIME hnsDefaultDevicePeriod(0);
		DWORD nTaskIndex = 0;
        LARGE_INTEGER liFirstFire;
        LONG lTimeBetweenFires;
        BOOL bOK;

		if(FAILED(hr)) 
		{
			CoUninitialize();
			return -1;
		}
		hr = pMMDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pMMDevice);
		if(FAILED(hr)) 
		{
			CoUninitialize();
			return -1;
		}
		pMMDeviceEnumerator->Release();

		m_hEventStop = CreateEvent(NULL, TRUE, FALSE, NULL);
		if(m_hEventStop == NULL)
		{
			CoUninitialize();
			return -1;
		}
		
		hr = m_pMMDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&m_pAudioClient);
		if(FAILED(hr))
			goto __error_LABEL;

		hr = m_pAudioClient->GetDevicePeriod(&hnsDefaultDevicePeriod, NULL);
		if(FAILED(hr))
			goto __error_LABEL;

		hr = m_pAudioClient->GetMixFormat(&m_pwfx);
		if (FAILED(hr))
			goto __error_LABEL;

		if(!AdjustFormatTo16Bits(m_pwfx))
			goto __error_LABEL;

		m_hTimerWakeUp = CreateWaitableTimer(NULL, FALSE, NULL);
		if(m_hTimerWakeUp == NULL)
			goto __error_LABEL;

		hr = m_pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, 0, 0, m_pwfx, 0);
		if(FAILED(hr))
			goto __error_LABEL;

		hr = m_pAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&m_pAudioCaptureClient);
		if(FAILED(hr))
			goto __error_LABEL;

		m_hTask = AvSetMmThreadCharacteristics("Capture", &nTaskIndex);
		if (NULL == m_hTask)
			goto __error_LABEL;

		
		liFirstFire.QuadPart = -hnsDefaultDevicePeriod / 2; // negative means relative time
		lTimeBetweenFires = (LONG)hnsDefaultDevicePeriod / 2 / (10 * 1000); // convert to milliseconds

		bOK = SetWaitableTimer(m_hTimerWakeUp,&liFirstFire,lTimeBetweenFires,NULL, NULL, FALSE);
		if(!bOK)
			goto __error_LABEL;

		hr = m_pAudioClient->Start();
		if(FAILED(hr))
			goto __error_LABEL;

		m_hThread = CreateThread(NULL,0,PTHREAD_START_ROUTINE_CALLBACK,this,0,0);
		if(m_hThread == NULL)
			goto __error_LABEL;

		CoUninitialize();
		return 0;
__error_LABEL:
		Close();
		CoUninitialize();
		return -1;
	}

	int StopCapture()
	{
		if(m_pAudioClient)
			m_pAudioClient->Stop();
		SetEvent(m_hEventStop);
		WaitForSingleObject(m_hThread,-1);
		Close();
		return 0;
	}

	void DoWork()
	{
		HANDLE waitArray[2] = { m_hEventStop, m_hTimerWakeUp };
		DWORD dwWaitResult;
		UINT32 nNextPacketSize(0);
		BYTE *pData = NULL;
		UINT32 nNumFramesToRead;
		DWORD dwFlags;
		CoInitialize(NULL);
		while(TRUE)
		{
			dwWaitResult = WaitForMultipleObjects(sizeof(waitArray)/sizeof(waitArray[0]), waitArray, FALSE, INFINITE);
			if(WAIT_OBJECT_0 == dwWaitResult) break;

			if (WAIT_OBJECT_0 + 1 != dwWaitResult)
			{
				break;
			}

			HRESULT hr = m_pAudioCaptureClient->GetNextPacketSize(&nNextPacketSize);
			if(FAILED(hr))
			{
				break;
			}

			if (nNextPacketSize == 0) continue;

			hr = m_pAudioCaptureClient->GetBuffer(&pData,&nNumFramesToRead,&dwFlags,NULL,NULL);
			if(FAILED(hr))
			{
				break;
			}

			if (0 != nNumFramesToRead)
			{
				std::cout<<"capture data "<<nNumFramesToRead * m_pwfx->nBlockAlign<<std::endl;
			}
			m_pAudioCaptureClient->ReleaseBuffer(nNumFramesToRead);
		}
		CoUninitialize();
	}

	static DWORD WINAPI PTHREAD_START_ROUTINE_CALLBACK( LPVOID lpThreadParameter);

protected:

	void Close()
	{
		if(m_hEventStop != NULL)
		{
			CloseHandle(m_hEventStop);
			m_hEventStop = NULL;
		}
		if(m_pAudioClient)
		{
			m_pAudioClient->Release();
			m_pAudioClient = NULL;
		}
		if(m_pwfx != NULL)
		{
			CoTaskMemFree(m_pwfx);
			m_pwfx = NULL;
		}
		if(m_hTimerWakeUp != NULL)
		{
			CancelWaitableTimer(m_hTimerWakeUp);
			CloseHandle(m_hTimerWakeUp);
			m_hTimerWakeUp = NULL;
		}
		if(m_hTask != NULL)
		{
			AvRevertMmThreadCharacteristics(m_hTask);
			m_hTask = NULL;
		}
		if(m_pAudioCaptureClient != NULL)
		{
			m_pAudioCaptureClient->Release();
			m_pAudioCaptureClient = NULL;
		}
	}

	BOOL AdjustFormatTo16Bits(WAVEFORMATEX *pwfx)
	{
		BOOL bRet(FALSE);

		if(pwfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT)
		{
			pwfx->wFormatTag = WAVE_FORMAT_PCM;
			pwfx->wBitsPerSample = 16;
			pwfx->nBlockAlign = pwfx->nChannels * pwfx->wBitsPerSample / 8;
			pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;
			bRet = TRUE;
		}
		else if(pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
		{
			PWAVEFORMATEXTENSIBLE pEx = reinterpret_cast<PWAVEFORMATEXTENSIBLE>(pwfx);
			if (IsEqualGUID(KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, pEx->SubFormat))
			{
				pEx->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
				pEx->Samples.wValidBitsPerSample = 16;
				pwfx->wBitsPerSample = 16;
				pwfx->nBlockAlign = pwfx->nChannels * pwfx->wBitsPerSample / 8;
				pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;

				bRet = TRUE;
			} 
		}

		return bRet;
    }


private:

	HANDLE m_hThread;
	HANDLE m_hTask;
	HANDLE m_hTimerWakeUp ;
	IAudioCaptureClient * m_pAudioCaptureClient;
	IAudioClient * m_pAudioClient; 
	WAVEFORMATEX * m_pwfx;
	HANDLE m_hEventStop;
	IMMDevice* m_pMMDevice;

};

DWORD CSoundCardAudioCapture::PTHREAD_START_ROUTINE_CALLBACK( LPVOID lpThreadParameter)
{
	CSoundCardAudioCapture* pCapture = (CSoundCardAudioCapture*) lpThreadParameter;
	pCapture->DoWork();
	return 0;
}


int main(int argc, char* argv[])
{
	CSoundCardAudioCapture cap;
	while(true)
	{
		cap.StartCapture();
		getchar();
		cap.StopCapture();
	}
	return 0;
}

