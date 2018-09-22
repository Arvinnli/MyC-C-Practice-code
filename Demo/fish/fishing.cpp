

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include <AudioClient.h> //WSAPI
#include <AudioPolicy.h> //WSAPI



#include <comsvcs.h>
#include <combaseapi.h>
#include <MMDeviceAPI.h>
#include <endpointvolume.h>
using namespace std;

#define MAX_AUDIO_FRAME_SIZE 192000

#define SAFE_RELEASE(punk)  \
if ((NULL != punk))\
{\
    (punk)->Release();\
    (punk) = NULL;\
}
// #define __uuidof(Class)   _UuidTraits<Class>::Guid() 

#ifdef __ARVINN_DBG
#define DBG_LINE(format,...)                \
do{                                         \
    printf("DBG:L%d"format"\n",__LINE__,##__VA_ARGS__);             \
}while(0)
#endif
#ifdef __JJYY


IMMDeviceEnumerator *pDeviceEnumerator;
int CCoreAudioInit(void){
	HRESULT hret;
	hret = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_ALL,
	__uuidof(IMMDeviceEnumerator),(void**)&pDeviceEnumerator);
	if(FAILED(hret)){
		return 0;
	}
	hret = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender,eMultimedia,&pDevice);
	if(FAILED(hret)){
		return 0;
	}
	hr = pDevice->Activate(__uuidof(IAudioMeterInformation),CLSCTX_ALL,NULL,(void**)&pMeterInfo);
	if(FAILED(hret)){
		return 0;
	}
	return 1;
	
}
float CCoreAudio_GetVolume(){
	HRESULT hret ;
	float volume = 0;
	hret = pMeterInfo->GetPeakValue(&volume);
	if(volume<0.01){
		return 0;
	}
	if(FAILED(hret)){
		return 0;
	}
	return volume;
}
// IMMDevice::Activate
#endif
#define EXIT_ON_ERROR(hr)  \
              if (FAILED(hr)) { return -1; }
int main(int argc, char *argv[]){
	HRESULT hr;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IAudioMeterInformation *pMeterInfo = NULL;



    CoInitialize(NULL);

    // Get enumerator for audio endpoint devices.
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                          NULL, CLSCTX_INPROC_SERVER,
                          __uuidof(IMMDeviceEnumerator),
                          (void**)&pEnumerator);
    EXIT_ON_ERROR(hr)

    // Get peak meter for default audio-rendering device.
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    EXIT_ON_ERROR(hr)

    hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
                           CLSCTX_ALL, NULL, (void**)&pMeterInfo);
    EXIT_ON_ERROR(hr)
	
    return 0;
}