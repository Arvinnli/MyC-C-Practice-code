#include "port.h"

#define BUFSIZE 1024


int main(int argc,char** argv){

    
    HANDLE hCom ;
    
    char inputData[BUFSIZE] = {0};
    char outputData[BUFSIZE] = {0};
    int sizeBuf = 6;
    int length ;

    if(argc<2){
        printf("missing parameters.\n");
        exit(1);
    }



    COMMTIMEOUTS timeouts;
    DCB dcb;
    //115200
    hCom = CreateFile(argv[1],GENERIC_READ|GENERIC_WRITE,0,NULL,
    OPEN_EXISTING,0,NULL);

    if(hCom==(HANDLE)-1){
        printf("Open port failed.\n");
        exit(1);
    }
    timeouts.ReadIntervalTimeout = 1000;
    timeouts.ReadTotalTimeoutMultiplier = 500;
    timeouts.ReadTotalTimeoutConstant = 5000;
    timeouts.WriteTotalTimeoutMultiplier = 500;
    timeouts.WriteTotalTimeoutConstant = 2000;

    if(!SetCommTimeouts(hCom,&timeouts)){
        printf("timeout error\n");
        exit(1);
    }

    if(!SetupComm(hCom,BUFSIZE,BUFSIZE)){
        printf("set port bufsize error\n");
        exit(1);
    }

    if(!GetCommState(hCom,&dcb)){
        printf("get port propeties failed\n");
        exit(1);
    }

    dcb.BaudRate = 115200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    if(!SetCommState(hCom,&dcb)){
        printf("set port propeties failed\n");
        exit(1);
    }

    if(ReadFile(hCom,inputData,sizeBuf,(LPDWORD)&length,NULL)==0)
    {
        printf("读取串口数据失败\n");
        exit(1);
    }
    printf("%s\n",inputData);
    /*关闭串口*/
    CloseHandle(hCom);


    return 0;
}








#undef BUFSIZE




