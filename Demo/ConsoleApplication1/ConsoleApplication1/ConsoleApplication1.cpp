// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include <wingdi.h>
#include <iostream>
#include <AudioClient.h> //WSAPI
#include <AudioPolicy.h> //WSAPI
#include <comsvcs.h>
#include <combaseapi.h>
#include <MMDeviceAPI.h>
#include <endpointvolume.h>

using namespace std;

#ifdef __cplusplus
extern "C"{
#endif






int ax=0,ay=0,bx=0,by=0,height=0,dx=0,dy=0,timeout=0;
int redmin=0,greenmin=0,bluemin=0;
int redmax=0,greenmax=0,bluemax=0;
DWORD WINAPI timer(LPVOID ptr);
void fish(void);
void getRGB();
IAudioMeterInformation* getPMeterInfo();
float getVolume(void);

int main(int argc,char** argv){
    if(argc<8){
        cout<<"missing parematers" << endl;
        return 0;
    }
    ax = atoi(argv[1]);
    ay = atoi(argv[2]);
    bx = atoi(argv[3]);
    by = atoi(argv[4]);
    dx = atoi(argv[5]);
    dy = atoi(argv[6]);

    timeout = atoi(argv[7]);

    Sleep(3000);

    fish();

    // getRGB();
    return 0;
}
void fish(void){

    HDC hdc = ::GetDC(NULL);

    DWORD threadID;
    int flag=0;
    CreateThread(NULL,0,timer,&flag,0,&threadID);
    CURSORINFO hCur_0,hCur_tmp ;
    ZeroMemory(&hCur_0,sizeof(hCur_0));
    ZeroMemory(&hCur_tmp,sizeof(hCur_tmp));
    hCur_0.cbSize=sizeof(hCur_0);
    hCur_tmp.cbSize=sizeof(hCur_tmp);
    GetCursorInfo(&hCur_0);


    LOOP:
    hCur_0.cbSize=sizeof(hCur_0);
    GetCursorInfo(&hCur_0);
    

    flag = 1;


    keybd_event('1', 0, 0, 0); //
    Sleep(50);
    keybd_event('1', 0, 2, 0); //
    // cout  << __LINE__ << endl;
    for(int i=ax;i<bx;i=i+dx){
        for(int j=ay;j<by;j=j+dy){
			Sleep(10);
            if(flag == 2){
                flag = 1;
                goto LOOP;
            }
            SetCursorPos(i,j);
            ZeroMemory(&hCur_tmp,sizeof(hCur_tmp));
            hCur_tmp.cbSize=sizeof(hCur_tmp);
            GetCursorInfo(&hCur_tmp);


            if(hCur_0.hCursor!=hCur_tmp.hCursor){
                while(flag==1){
                    if(getVolume()>0){
                        flag = 2;
                    }
                    Sleep(100);
                    
                }
                Sleep(50);        
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0,0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0,0);
                Sleep(2000);
                goto LOOP;
            }
        }
    }
    goto LOOP;
}

DWORD WINAPI timer(LPVOID ptr){
    
    int* flag = (int*)ptr;
    int count = 0;
    
    while(1){
        Sleep(1000);
        count++;
        if(count == timeout){
            count = 0;
            switch(*flag){
                case 1:*flag = 2;break;
                case 2:*flag = 1;break;
            }
        }
    }
}


void getRGB(){
     POINT a,b;
    HDC hdc = ::GetDC(NULL);
    int rgb = 0,rgbtmp = 0;
    int R,G,B;
    while(1){
        Sleep(500);
        GetCursorPos(&a);
        rgb = GetPixel(hdc,a.x,a.y);
        if(rgb==rgbtmp)continue;
        rgbtmp = rgb;
        // cout << "curpos:" << a.x << "," << a.y << endl;

        printf("pixel:%.6x\n",rgb);
    }
    
    DeleteDC(hdc);
}

IAudioMeterInformation* getPMeterInfo(){
    HRESULT hr;
	static IMMDeviceEnumerator *pEnumerator = NULL;
	static IMMDevice *pDevice = NULL;
	static IAudioMeterInformation *pMeterInfo = NULL;



	CoInitialize(NULL);

	// Get enumerator for audio endpoint devices.
    if(pEnumerator==NULL){
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator),(void**)&pEnumerator);
	    if (FAILED(hr)) {
            cout << "CocreateInstance failed, ret:" << hr << endl;
            pEnumerator = NULL;
            return NULL;
        }
    }
	
    if(pDevice==NULL){
        hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        if(FAILED(hr)){
            cout << "IMMDeviceEnumerator::GetDefaultAudioEndpoint failed ret:" << hr << endl;
            pDevice = NULL;
            return NULL;
        }
    }

    if(pMeterInfo==NULL){
        hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
			CLSCTX_ALL, NULL, (void**)&pMeterInfo);
        if(FAILED(hr)){
            cout << "IMMDevice::Activate failed ret:" << hr << endl;
            pMeterInfo = NULL;
            return NULL;
        }
    }
    
	return pMeterInfo;
}

float getVolume(void){
    int ret;
    float volume;
    IAudioMeterInformation* pMeterInfo = getPMeterInfo();
    if(pMeterInfo==NULL)return -1;
    ret = pMeterInfo->GetPeakValue(&volume);
    if(FAILED(ret)){
        cout << "IAudioMeterInformation::GetPeakValue failed ret:" << ret << endl;
    }
    if(volume<0.01){
        return 0;
    }
    return volume;
}











#ifdef __cplusplus
}
#endif