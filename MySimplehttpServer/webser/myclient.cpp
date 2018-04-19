#include <Winsock2.h>
#include <stdio.h>
#include<string.h>
#pragma comment(lib,"Ws2_32.lib")

#define  BUF_LENGTH 1024
#define USER_ERROR -1
#ifdef ___HEHEHEHEH
GET /s3/canvas.html HTTP/1.1\r\n
Host: 172.217.160.132:9999\r\n
User-Agent: SonyEricssonK700c/R2AE SEMC-Browser/4.0.3 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n
Accept-Language: zh,en;q=0.7,en-US;q=0.3\r\n
Accept-Encoding: gzip, deflate\r\n
Connection: keep-alive\r\n
Upgrade-Insecure-Requests: 1\r\n

GET / HTTP/1.1\r\n
Host: www.google.com\r\n
User-Agent: SonyEricssonK700c/R2AE SEMC-Browser/4.0.3 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n
Accept: text/vnd.wap.wml,application/vnd.wap.xhtml+xml,application/xhtml+xml, image/vnd.wap.wbmp, image/gif, image/jpg,image/jpeg, image/png, image/bmp, text/html,*/*;q=0.1\r\n
Accept-Language: en\r\n
Accept-Encoding: gzip, deflate\r\n
Connection: keep-alive\r\n
Upgrade-Insecure-Requests: 1\r\n


#endif

char google_buf[1024] = {
"GET / HTTP/1.1\r\n"
"Host: 172.217.160.132\r\n"
"User-Agent: SonyEricssonK700c/R2AE SEMC-Browser/4.0.3 Profile/MIDP-2.0 Configuration/CLDC-1.1\r\n"
"Accept: text/vnd.wap.wml,application/vnd.wap.xhtml+xml,application/xhtml+xml, image/vnd.wap.wbmp, image/gif, image/jpg,image/jpeg, image/png, image/bmp, text/html,*/*;q=0.1\r\n"
"Accept-Language: en\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Connection: keep-alive\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
};

int main()
{
    WSADATA wsData;
    SOCKET sClient;           //客户端套接字
    struct sockaddr_in ser;   //服务器进程地址
    char send_buf[BUF_LENGTH];  //发送缓存
    char recv_buf[BUF_LENGTH];  //接收缓存
    int iSend, iRecv;            //接收数据和发送数据长度

    //第一步：加载协议栈
    if (WSAStartup(MAKEWORD(2,2),&wsData)!=0)
    {
        printf("Failed to load Winsock.\n");
        return USER_ERROR;
    }

    //创建服务器地址
    ser.sin_family=AF_INET;
    ser.sin_port=htons(80);                  //服务器端口号
    ser.sin_addr.s_addr=inet_addr("172.217.160.132");        //服务器IP地址

    //第二步：创建流套接字,运输层采用TCP协议
    sClient=socket(AF_INET,SOCK_STREAM,0);
    if (sClient==INVALID_SOCKET)
    {
        printf("socket() Failed:%d\n",WSAGetLastError());
        return USER_ERROR;
    }

    //第三步：通过创建的套接字向相应的服务器发起连接请求
    if (connect(sClient,(struct sockaddr*)&ser,sizeof(ser))==INVALID_SOCKET)
    {
        printf("connet() Failed:%d\n",WSAGetLastError());
        return USER_ERROR;
    }
    else   //连接成功
    {     
        //第四步：通过套接字发数据
        printf("input data to send:\n");
        memset(send_buf,0,sizeof(send_buf));  //缓存清0
        gets(send_buf);
        iSend=send(sClient,google_buf,sizeof(google_buf),0);  //通过套接字发送数据给服务器
        if (iSend==SOCKET_ERROR)   //发送不成功
        {
            printf("send() Failed:%d\n",WSAGetLastError());
            return USER_ERROR;
        }
        else 
            printf("send success\n");  //发送成功

        printf("recv data from server: \n");
        while(1)
        {
            memset(recv_buf,0,sizeof(recv_buf));  //缓存清0
            iRecv=recv(sClient,recv_buf,sizeof(recv_buf),0);
            if(strcmp(recv_buf,"") == 0)    // 接收缓存为空则表示接受完毕，退出
                break;
            if (iRecv ==SOCKET_ERROR)   //接收错误
            {
                printf("recv() Failed:%d\n",WSAGetLastError());
                return USER_ERROR;
            }
            else    
                printf("%s\n",recv_buf);    // 打印接收缓存
        }

    }
        //第五步：释放该套接字，断开连接
    closesocket(sClient);
    WSACleanup();
    return 0;
}