
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#pragma comment(lib,'ws2_32.lib')

using namespace std;

// #define serIP "192.168.1.104"
#define serIP "10.0.142.124"
#define PORT  11111

static void A_bzero(char* buf,int n){
    int i;
    for(i=0;i<n;i++){
        buf[i] = 0;
    }
}

int main(int argc,char** argv){
    WSADATA wsd;
    SOCKET sclient;
    char buf[128];
    int ret ;
    struct sockaddr_in server;
    int clifd;
    unsigned short port;
    struct hostent* host = NULL;

    //add winsock dll
    if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
        cout << "winsock init failed" <<endl;
        return -1;
    }

    //create socket 
    clifd = socket(AF_INET,SOCK_STREAM,0);
    if(clifd == INVALID_SOCKET){
        cout << "create socket failed" <<endl;
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(serIP);

    if(server.sin_addr.s_addr == INADDR_NONE){
        host = gethostbyname(serIP); //域名
        if(host == NULL){
            cout << "gethostbyname failed" <<endl;
            return -1;
        }
        CopyMemory(&server.sin_addr,host->h_addr_list[0],host->h_length);
    }

    //connect the server
    if(connect(clifd,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR){
       cout << "connect failed" <<endl;
       return -1; 
    }

    //send msg to the server
    while(1){
        //get the stdin
        A_bzero(buf,128);
        gets(buf);
        ret = send(clifd,buf,strlen(buf)+1,0);
        if(ret == 0){
            break;
        }else if(ret == SOCKET_ERROR){
            cout << "recv faield ,err_Code::"<< WSAGetLastError()  <<endl;
            break;
        }
        cout << "send str :: " << buf <<endl;
    }

    return 0;
}