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
    // ������0��ÿ�β���ǰ��Ҫ�ǵ��建�棬����ϰ�ߣ�
    // ����տ��ܳ��ֵ�����������롢��̨�������뻹������ͬ
    // ԭ�򣺲���ջ�������� '\0'�ַ�Ϊֹ������ǰ��Ĳ���'\0' Ҳ��һ�����
    memset(recv_buf,0,sizeof(recv_buf));
    if (recv(sAccept,recv_buf,sizeof(recv_buf),0) == SOCKET_ERROR)   //���մ���
    {
        printf("recv() Failed:%d\n",WSAGetLastError());
        return USER_ERROR;
    }       
    else
        printf("recv data from client:%s\n",recv_buf); //���ճɹ�����ӡ������

    //�����������
    i = 0; j = 0;
    // ȡ����һ�����ʣ�һ��ΪHEAD��GET��POST
    while (!(' ' == recv_buf[j]) && (i < sizeof(method) - 1))
    {
        method[i] = recv_buf[j];
        i++; j++;
    }
    method[i] = '\0';   // ������������Ҳ�ǳ�ѧ�ߺ����׺��ӵĵط�

    // �������GET��HEAD��������ֱ�ӶϿ���������
    // ��������Ĺ淶Щ���Է��������һ��501δʵ�ֵı�ͷ��ҳ��
    if (stricmp(method, "GET") && stricmp(method, "HEAD"))
    {
        closesocket(sAccept); //�ͷ������׽��֣�������ÿͻ���ͨ��
        printf("not get or head method.\nclose ok.\n");
        printf("***********************\n\n\n\n");
        return USER_ERROR;
    }
    printf("method: %s\n", method);

    // ��ȡ���ڶ�������(url�ļ�·�����ո����)������'/'��Ϊwindows�µ�·���ָ���'\'
    // ����ֻ���Ǿ�̬����(����url�г���'?'��ʾ�Ǿ�̬����Ҫ����CGI�ű���'?'������ַ�����ʾ���������������'+'����
    // ���磺www.csr.com/cgi_bin/cgi?arg1+arg2 �÷�����ʱҲ�в�ѯ�����ڳ���������)
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

    // �������url·��ת��Ϊ����·��
    _getcwd(path,_MAX_PATH);
    strcat(path,url);
    printf("path: %s\n",path);

    // �򿪱���·���µ��ļ������紫������r�ı���ʽ�򿪻����
    FILE *resource = fopen(path,"rb");

    // û�и��ļ�����һ���򵥵�404-file not found��htmlҳ�棬���Ͽ���������
    if(resource==NULL)
    {
        file_not_found(sAccept);
        // ���method��GET�������Զ����file not foundҳ��
        if(0 == stricmp(method, "GET"))
            send_not_found(sAccept);

        closesocket(sAccept); //�ͷ������׽��֣�������ÿͻ���ͨ��
        printf("file not found.\nclose ok.\n");
        printf("***********************\n\n\n\n");
        return USER_ERROR;
    }

    // ����ļ����ȣ��ǵ������ļ�ָ�뵽�ļ�ͷ
    fseek(resource,0,SEEK_SET);
    fseek(resource,0,SEEK_END);
    long flen=ftell(resource);
    printf("file length: %ld\n", flen);
    fseek(resource,0,SEEK_SET);

    // ����200 OK HEAD
    file_ok(sAccept, flen,path);

    // �����GET���������������Դ
    if(0 == stricmp(method, "GET"))
    {
        if(0 == send_file(sAccept, resource))
            printf("file send ok.\n");
        else
            printf("file send fail.\n");
    }
    fclose(resource);

    closesocket(sAccept); //�ͷ������׽��֣�������ÿͻ���ͨ��
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
		// text/plain					�޸�ʽ�ı�
		// appliation/postscript		postscipt�ĵ�
		// image/gif					gifͼ
		// image/jpeg					jpegͼ
        // text/css                     css�ļ�
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

// ����200 ok��ͷ
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
// �����Զ����file_not_foundҳ��
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

// �����������Դ
int send_file(SOCKET sAccept, FILE *resource)
{
    char send_buf[BUF_LENGTH];
    while (1)
    {
        memset(send_buf,0,sizeof(send_buf));       //������0
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
