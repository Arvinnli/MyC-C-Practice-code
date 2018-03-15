#include "http.h"
#include "ArvinnFunc.h"
#include "ConetentType.h"
#ifdef __HEHE_HEHE
starbuzz
http://10.0.142.124:9999/starbuzz/index.html
#define __THE_BROWSSOR "WebServer started...\r\nvisit http://10.0.142.124:9999/test.html  \r\n"

#endif
DWORD WINAPI SimpleHTTPServer(LPVOID ptr);
int main(int argc,char** argv){

    WSADATA wsadata;
    SOCKET  serfd,clifd;
    int serverport = DEFAULT_PORT;
    struct sockaddr_in seraddr,cliaddr;
    int     addrlen = sizeof(cliaddr);
    int ret ;

    cout << "-----------------------------------------------------------------" << endl;
    cout << "Servr wating!" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    //1.load the protocal stack
    if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
        cout << "Failed to load Winsock" << endl;
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
        cout << "bind  failed! err_code:" << WSAGetLastError() << endl;
        return USER_ERROR; 
    }

    //4 listen
    ret = listen(serfd,5);
    if(ret == SOCKET_ERROR){
        cout << "listen error , err_code :" << WSAGetLastError() << endl;
        return USER_ERROR;
    }


    while(1){
        clifd = accept(serfd,(struct sockaddr*)&cliaddr,&addrlen);

        if(clifd == INVALID_SOCKET){
            cout << "accept Failed , err_code :" << WSAGetLastError() << endl;
            break;
        }
        DWORD threadID;
        
        CreateThread(NULL,0,SimpleHTTPServer,(LPVOID)clifd,0,&threadID);

    }


    return 0;
}



DWORD WINAPI SimpleHTTPServer(LPVOID lparam)
{
    SOCKET sAccept = (SOCKET)(LPVOID)lparam;
    char recv_buf[BUF_LENGTH]; 
    char method[MIN_BUF];
    char url[MIN_BUF];
    char path[_MAX_PATH];
    int i, j;
    // cout << "================================================= clifd :: "<< sAccept<<endl;
    // 缓存清0，每次操作前都要记得清缓存，养成习惯；
    // 不清空可能出现的现象：输出乱码、换台机器乱码还各不相同
    // 原因：不清空会输出遇到 '\0'字符为止，所以前面的不是'\0' 也会一起输出
    memset(recv_buf,0,sizeof(recv_buf));
    if (recv(sAccept,recv_buf,sizeof(recv_buf),0) == SOCKET_ERROR)   //接收错误
    {
        printf("recv() Failed:%d\n",WSAGetLastError());
        return USER_ERROR;
    }       
    else
        printf("recv data from client:%s\n",recv_buf); //接收成功，打印请求报文

    //处理接收数据
    i = 0; j = 0;
    // 取出第一个单词，一般为HEAD、GET、POST
    while (!(' ' == recv_buf[j]) && (i < sizeof(method) - 1))
    {
        method[i] = recv_buf[j];
        i++; j++;
    }
    method[i] = '\0';   // 结束符，这里也是初学者很容易忽视的地方

    // 如果不是GET或HEAD方法，则直接断开本次连接
    // 如果想做的规范些可以返回浏览器一个501未实现的报头和页面
    if (stricmp(method, "GET") && stricmp(method, "HEAD"))
    {
        closesocket(sAccept); //释放连接套接字，结束与该客户的通信
        printf("not get or head method.\nclose ok.\n");
        printf("***********************\n\n\n\n");
        return USER_ERROR;
    }
    printf("method: %s\n", method);

    // 提取出第二个单词(url文件路径，空格结束)，并把'/'改为windows下的路径分隔符'\'
    // 这里只考虑静态请求(比如url中出现'?'表示非静态，需要调用CGI脚本，'?'后面的字符串表示参数，多个参数用'+'隔开
    // 例如：www.csr.com/cgi_bin/cgi?arg1+arg2 该方法有时也叫查询，早期常用于搜索)
    i = 0;
    while ((' ' == recv_buf[j]) && (j < sizeof(recv_buf)))
        j++;
    while (!(' ' == recv_buf[j]) && (i < sizeof(recv_buf) - 1) && (j < sizeof(recv_buf)))
    {
        if (recv_buf[j] == '/')
            url[i] = '\\';
        else if(recv_buf[j] == ' ')
            break;
        else
            url[i] = recv_buf[j];
        i++; j++;
    }
    url[i] = '\0';
    printf("url: %s\n",url);

    // 将请求的url路径转换为本地路径
    _getcwd(path,_MAX_PATH);
    strcat(path,url);
    printf("path: %s\n",path);

    // 打开本地路径下的文件，网络传输中用r文本方式打开会出错
    FILE *resource = fopen(path,"rb");

    // 没有该文件则发送一个简单的404-file not found的html页面，并断开本次连接
    if(resource==NULL)
    {
        file_not_found(sAccept);
        // 如果method是GET，则发送自定义的file not found页面
        if(0 == stricmp(method, "GET"))
            send_not_found(sAccept);

        closesocket(sAccept); //释放连接套接字，结束与该客户的通信
        printf("file not found.\nclose ok.\n");
        printf("***********************\n\n\n\n");
        return USER_ERROR;
    }

    // 求出文件长度，记得重置文件指针到文件头
    fseek(resource,0,SEEK_SET);
    fseek(resource,0,SEEK_END);
    long flen=ftell(resource);
    printf("file length: %ld\n", flen);
    fseek(resource,0,SEEK_SET);

    // 发送200 OK HEAD
    file_ok(sAccept, flen,path);

    // 如果是GET方法则发送请求的资源
    if(0 == stricmp(method, "GET"))
    {
        if(0 == send_file(sAccept, resource))
            printf("file send ok.\n");
        else
            printf("file send fail.\n");
    }
    fclose(resource);

    closesocket(sAccept); //释放连接套接字，结束与该客户的通信
    printf("close ok.\n");
    printf("***********************\n\n\n\n");

    return 0;

}


int file_not_found(SOCKET clifd){
    char send_buf[MIN_BUF];
    sprintf(send_buf,"HTTP/1.1 404 NOT FOUND\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"Connection: keep-alive\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,SERVER);
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"Content-Type: text/html\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    sprintf(send_buf,"\r\n");
    send(clifd,send_buf,strlen(send_buf),0);
    return 0;
}


		// text/html					html page
		// text/plain					无格式文本
		// appliation/postscript		postscipt文档
		// image/gif					gif图
		// image/jpeg					jpeg图
        // text/css                     css文件
void GetFileType(char* filename,char* type){
    if(NULL!=strstr(filename,".css")){
        strcpy(type,"text/css");
    }else if(NULL!=strstr(filename,".html")){
        strcpy(type,"text/html");
    }else if(NULL!=strstr(filename,".gif")){
        strcpy(type,"image/gif");
    }else if(NULL!=strstr(filename,".jpg")){
        strcpy(type,"image/jpeg");
    }else if(NULL!=strstr(filename,".postscript")){
        strcpy(type,"appliation/postscript");
    }else{
        strcpy(type,"text/plain");
    }
}

// 发送200 ok报头
int file_ok(SOCKET sAccept, long flen,char* filename)
{
    char send_buf[MIN_BUF]; 
    char type[MIN_BUF];
    ArvinnFunc::bzero(type,MIN_BUF);
    // GetFileType(filename,type);
    ContentType::gettype(filename,type);
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

// 发送请求的资源
int send_file(SOCKET sAccept, FILE *resource)
{
    char send_buf[BUF_LENGTH];
    while (1)
    {
        memset(send_buf,0,sizeof(send_buf));       //缓存清0
        fgets(send_buf, sizeof(send_buf), resource);
    //  printf("send_buf: %s\n",send_buf);
        // cout <<"sendbuf:"<<send_buf << endl;
        if (SOCKET_ERROR == send(sAccept, send_buf, strlen(send_buf), 0))
        {
            printf("send() Failed:%d\n",WSAGetLastError());
            return USER_ERROR;
        }
        if(feof(resource))
            return 0;
    }   
}
