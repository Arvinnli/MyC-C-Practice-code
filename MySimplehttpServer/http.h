#ifndef __HTTP_H
#define __HTTP_H



#include <iostream>
#include <Winsock2.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define DEFAULT_PORT        80
#define BUF_LENGTH          1024
#define MIN_BUF             128
#define USER_ERROR          -1
#define SERVER              "Server: csr_http1.1\r\n"

#ifdef TRACE_INFO_SUPPORT
    #define print(...) printf(__VA_ARGS__)
#else 
    #define print(...)  
#endif 

#pragma comment(lib , "ws2_32")

using namespace std;

// static void A_bzero(char* buf,int n);
int file_not_found(SOCKET sAccept);

int send_file(SOCKET sAccept, FILE *resource);

int send_not_found(SOCKET sAccept);
int file_ok(SOCKET sAccept, long flen,char* filename);


#endif  //end of file