#ifndef __AUDIO_H
#define __AUDIO_H
#include <Mmdeviceapi.h>
#include <Audioclient.h>
#include <Devicetopology.h>
#include <Endpointvolume.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <initguid.h>  
#include <vector>

// typedef struct _GUID {          
//     DWORD Data1;
//     WORD   Data2;
//     WORD   Data3;
//     BYTE  Data4[8];
// } GUID;

typedef struct _DevItem{
    std::string  strName;
    GUID    guid;
}DevItem;
















#endif //..end of file