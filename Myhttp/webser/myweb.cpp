/*************************************************************************
 * 
 * Copyright (c) 版权没有，翻版不究
 *
 * FILENAME:  myser.cpp
 *
 * PURPOSE :  HTTP 服务器程序, 向客户端提供请求的文件内容.
 *  
 * AUTHOR  :  
 * 
 **************************************************************************/

#include "myweb.h"
#include "ContentType.h"
#include "ArvinnFunc.h"
// GBK  
#ifdef __HEHEHHEHEHEHEHHEHEHHEHEHEHEHEHHEHEHEH
#define test_url    "http://10.0.142.124:9999/test.html"
"http://10.0.142.124:9999/starbuzz/index.html"
#endif 


int main(int argc,char** argv){
    
    WSADATA wsadata;
    SOCKET  serfd,clifd;
    int serverport = DEFAULT_PORT;
    struct sockaddr_in seraddr,cliaddr;
    int     addrlen = sizeof(cliaddr);
    int     ret ;

    cout << "ARVINN SIMPLE WEB START RUNNING.." << endl;

    //1.load the protocal stack
    if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
        cout << "Failed to load Winsock  stack " << endl;
        return USER_ERROR;
    }

    //2.create server socket 
    serfd = socket(AF_INET,SOCK_STREAM,0);
    if(serfd == INVALID_SOCKET){
        cout << "Create socket failed" << endl;
        return USER_ERROR;
    }
    
    //.set the server addr
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //3.bind the seraddr and socket
    ret = bind(serfd,(LPSOCKADDR)&seraddr,sizeof(seraddr));
    if(ret == SOCKET_ERROR){
        cout << "bind  failed! err_code:  " << WSAGetLastError() << endl;
        return USER_ERROR; 
    }

    //4.listen
    ret = listen(serfd,5);
    if(ret == SOCKET_ERROR){
        cout << "listen error , err_code :" << WSAGetLastError() << endl;
        return USER_ERROR;
    }

    //5.waiting for the client connect.
    while(1){
        clifd = accept(serfd,(struct sockaddr*)&cliaddr,&addrlen);
        print("CLIENT %s::%d connected!\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
        if(clifd == INVALID_SOCKET){
            cout << "accept Failed , err_code :" << WSAGetLastError() << endl;
            break;
        }
        DWORD threadID;
        CreateThread(NULL,0,HandleHttpRequest,(LPVOID)clifd,0,&threadID);

    }
    closesocket(serfd);
    return 0;
}




// Handle the http request:: 
// just support method::GET  2017-12-21
DWORD WINAPI HandleHttpRequest(LPVOID ptr){
    SOCKET clifd = (SOCKET)ptr;
    char recv_buf[BUF_LENGTH]; 
    char method[MIN_BUF];
    char url[MIN_BUF];
    char filetype[MIN_BUF];
    char path[_MAX_PATH];
    int  i, j,ret,count;

    ArvinnFunc::bzero(recv_buf,sizeof(recv_buf));
    ArvinnFunc::bzero(method,sizeof(method));
    ret = recv(clifd,recv_buf,sizeof(recv_buf),0);
    if(SOCKET_ERROR == ret ){
        cout << "recv Failed " << endl << "ErrorCode : "<< WSAGetLastError() << endl;
        return USER_ERROR;
    }
    print("recv_buf:%s\n",recv_buf);

    for(i=0;' '!=recv_buf[i]&&i<1023;i++){
        method[i] = recv_buf[i];
    }
    count = i;
    
    // if not the GET and HEAD , just return ,other method has not implemented
    if (stricmp(method, "GET") && stricmp(method, "HEAD"))
    {
        closesocket(clifd); //close socket end the connection 
        cout << "the method "<< method << "is not implemented "<< endl;
        return USER_ERROR;
    }
    print("method: %s\n", method);
    
    // 提取出第二个单词(url文件路径，空格结束)，
    // 这里只考虑静态请求(比如url中出现'?'表示非静态，需要调用CGI脚本，'?'后面的字符串表示参数，多个参数用'+'隔开
    // 例如：www.csr.com/cgi_bin/cgi?arg1+arg2 该方法有时也叫查询，早期常用于搜索)
    for(;count<BUF_LENGTH;count++){
        if(' '!=recv_buf[count])break;
    }
    ArvinnFunc::bzero(url,MIN_BUF);
    for(i=0;' '!=recv_buf[count]&&count<1023;i++,count++){
        if(recv_buf[count]==' ')break;
        url[i] = recv_buf[count];
    }
    print("url:%s\n",url);

    ArvinnFunc::bzero(path,sizeof(path));
    ArvinnFunc::bzero(filetype,sizeof(filetype));
    //get pwd and get the path of target file
    _getcwd(path,_MAX_PATH);
    strcat(path,url);
    print("path::%s\n",path);

    //get the filetype
    ContentType::gettype(url,filetype);
    print("filetype::%s\n",filetype);
    
    //open target file
    FILE* fp = fopen(path,"rb");
    if(NULL == fp){
        file_not_found(clifd,filetype);
        // 如果method是GET，则发送自定义的file not found页面
        if(0 == stricmp(method, "GET"))
            send_not_found(clifd);

        closesocket(clifd); //释放连接套接字，结束与该客户的通信
        print("file %s not found.\nclose ok.\n",url);
        print("***********************\n\n\n\n");
        return USER_ERROR;
    }


    // 求出文件长度，记得重置文件指针到文件头
    fseek(fp,0,SEEK_SET);
    fseek(fp,0,SEEK_END);
    long flen=ftell(fp);
    print("file %s length: %ld\n",url, flen);
    fseek(fp,0,SEEK_SET);

    // 发送200 OK HEAD
    file_ok(clifd,flen,filetype);

    // 如果是GET方法则发送请求的资源
    if(0 == stricmp(method, "GET"))
    {
        if(0 == send_file(clifd, fp)){
            print("file send ok.\n");         
        }else{
            print("file send fail.\n");
        }   
    }
    fclose(fp);

    closesocket(clifd); //释放连接套接字，结束与该客户的通信
    print("close ok.\n");
    print("***********************\n\n\n\n");

    return 0;
}

int send_file(SOCKET sAccept, FILE *resource)
{
    char send_buf[BUF_LENGTH];
    char byte;
    int ret;
    while (1)
    {
        // memset(send_buf,0,sizeof(send_buf));       //缓存清0
        ArvinnFunc::bzero(send_buf,sizeof(send_buf));
        // fgets(send_buf, sizeof(send_buf), resource);
        //使用fges  send(...,strlen()...)传送图片出错
        // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);  
        // 返回 nmemb 或者实际从文件流获取的字节数
        ret = fread(send_buf,1,sizeof(send_buf),resource);
        // print("ret::%d\n",ret);
        if(ret < 1){
            return 0;
        }
        //  print("send_buf: %s\n",send_buf);
        // cout <<"sendbuf:"<<send_buf << endl;
        if (SOCKET_ERROR == send(sAccept, send_buf, ret, 0))
        {
            print("send() Failed:%d\n",WSAGetLastError());
            return USER_ERROR;
        }
        if(feof(resource))
            return 0;
    }   
}

int file_ok(SOCKET sAccept, long flen,char* type)
{
    char send_buf[MIN_BUF]; 
    //  time_t timep;
    //  time(&timep);
    sprintf(send_buf, "HTTP/1.1 200 OK\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Connection: keep-alive\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    //  sprintf(send_buf, "Date: %s\r\n", ctime(&timep));
    //  send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, SERVER);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Content-Length: %ld\r\n", flen);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "Content-Type: %s\r\n",type);
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    return 0;
}


// 发送自定义的file_not_found页面
int send_not_found(SOCKET sAccept)
{
    char send_buf[MIN_BUF];
    sprintf(send_buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "<BODY><h1 align='center'>404</h1><br/><h1 align='center'>file not found.</h1>\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    sprintf(send_buf, "</BODY></HTML>\r\n");
    send(sAccept, send_buf, strlen(send_buf), 0);
    return 0;
}

int file_not_found(SOCKET clifd,char* type){
    char send_buf[MIN_BUF];
    sprintf(send_buf,"HTTP/1.1 404 NOT FOUND\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"Connection: keep-alive\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,SERVER);
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"Content-Type: %s\r\n",type);
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    return 0;
}
