/*************************************************************************
 * 
 * Copyright  (c) 版权没有，翻版不究
 *
 * FILENAME:  myser.cpp
 *
 * PURPOSE :  HTTP 服务器程序, 向客户端提供请求的文件内容.
 *  
 * AUTHOR  :  
 * 
 **************************************************************************/
#ifndef __MYWEB_H
#define __MYWEB_H

#include <iostream>
#include <Winsock2.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#pragma comment(lib , "ws2_32")

using namespace std;

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











DWORD WINAPI HandleHttpRequest(LPVOID ptr);
int file_not_found(SOCKET clifd,char* type);
// void GetFileType(char* filename,char* type);
int send_not_found(SOCKET sAccept);
int file_ok(SOCKET sAccept, long flen,char* type);
int send_file(SOCKET sAccept, FILE *resource);





#endif //end of file




#if 0
/*
recv data from client:GET /starbuzz/index.html HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1


method: GET
url: \starbuzz\index.html
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\index.html
file length: 4810
file send ok.
close ok.
***********************



recv data from client:GET /starbuzz/images/headerLogo.gif HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: */*
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://10.0.142.124:9999/starbuzz/index.html
Connection: keep-alive


method: GET
url: \starbuzz\images\headerLogo.gif
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\images\headerLogo.gif
recv data from client:GET /starbuzz/starbuzz.css HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: text/css,*/*;q=0.1
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://10.0.142.124:9999/starbuzz/index.html
Connection: keep-alive


method: GET
url: \starbuzz\starbuzz.css
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\starbuzz.css
recv data from client:GET /starbuzz/images/headerSlogan.gif HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: */*
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://10.0.142.124:9999/starbuzz/index.html
Connection: keep-alive


method: GET
url: \starbuzz\images\headerSlogan.gif
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\images\headerSlogan.gif
recv data from client:GET /starbuzz/images/bag.gif HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: */*
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://10.0.142.124:9999/starbuzz/index.html
Connection: keep-alive


method: GET
url: \starbuzz\images\bag.gif
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\images\bag.gif
file length: 7870
file length: 2579
file length: 3448
file send ok.
close ok.
***********************



file send ok.
close ok.
***********************



file send ok.
file length: 17459
recv data from client:GET /starbuzz/images/background.gif HTTP/1.1
Host: 10.0.142.124:9999
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0
Accept: */*
Accept-Language: zh,en;q=0.7,en-US;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://10.0.142.124:9999/starbuzz/starbuzz.css
Connection: keep-alive


file send ok.
method: GET
url: \starbuzz\images\background.gif
path: E:\Arvinn_doc\cfile\C_file\Myhttp\starbuzz\images\background.gif
close ok.
***********************



file length: 10732
close ok.
***********************



file send ok.
close ok.
***********************

*/
#endif