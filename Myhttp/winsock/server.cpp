#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
 
#pragma comment(lib , "ws2_32")
 
#define PORT 80
// #define IP_ADDRESS "192.168.1.104"
#define IP_ADDRESS "10.0.142.124"
typedef unsigned short wchar;

void A_bzero(char* buf,int len){
    int i;
    for(i=0;i<len;i++){
        buf[i] = 0;
    }
}

DWORD WINAPI ClientThread(void* ptr){
    SOCKET sock = (SOCKET)ptr;
    char buf[1024];
    int ret,nleft,idx;
    while(1){
        ret = recv(sock,buf,1024,0);
        if(ret==0){
            break;
        }else if(ret == SOCKET_ERROR){
            cout << "recv failed"<< WSAGetLastError() <<endl;
            break;
        }
        buf[ret]=0;
        cout << "recv::" << buf <<endl;
        nleft = ret ;
        idx = 0;
        //send back
    }
}

int main(int argc,char** argv){
    
    WSADATA wsd;
    HANDLE hThread ;
    DWORD dwThread;
    SOCKET sListen,client_fd;
    int i=0;
    int addr_size;
    unsigned short port;
    struct sockaddr_in local,client;

    //init winsock
    if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
        cout<< "winsock init failed!" <<endl;
        return -1;
    }

    //create winsock
    sListen = socket(AF_INET,SOCK_STREAM,0);
    if(sListen == SOCKET_ERROR){
        cout << "create winsocket failed" << endl;
        return -1;
    }

    local.sin_family = AF_INET;
    local.sin_addr.S_un.S_addr = INADDR_ANY;
    local.sin_port = htons(PORT);

    //
    if(bind(sListen,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR){
        cout << "bind failed" <<endl;
        return -1;
    }

    //listen
    listen(sListen,8);
    while(1)
    {
        addr_size = sizeof(client);
        cout << "wait for client" <<endl;
        client_fd = accept(sListen,(struct sockaddr*)&client,&addr_size);
        if(client_fd == INVALID_SOCKET){
            cout << "accept failed! errcode::"<<WSAGetLastError()  <<endl;
            break;
            // return -1;
        }
        i++;
        cout << "cilent:: connect ip::" <<inet_ntoa(client.sin_addr)<< "port::"<<ntohs(client.sin_port)<<endl;
        hThread = CreateThread(NULL,0,ClientThread,(LPDWORD)client_fd,0,&dwThread);
    }
    if(sListen == INVALID_SOCKET)
    {
        closesocket(sListen);
        sListen = INVALID_SOCKET;
    }

    WSACleanup();
    return 0;
}
