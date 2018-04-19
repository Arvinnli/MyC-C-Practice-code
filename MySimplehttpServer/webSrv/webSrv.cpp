// ComDBMon.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "winsock.h"
#include "mysql.h"
#pragma comment(lib,"libmySQL.lib") 
#pragma comment(lib,"WSock32.Lib") 

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		// exit(1);
	}
	printf("WebServer started...\r\nvisit http://127.0.0.1:808\r\n");
	SOCKET server_socket;		//服务器的socket
	SOCKET acc_socket;			//接收到的用户连接的socket
	int sock_size = sizeof(struct sockaddr_in);  
	struct sockaddr_in client_addr;			//客户连接信息
	struct sockaddr_in server_addr;			//客户连接信息

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {				//如果返回值为－1 则出错
		return -1;
	}
	/*
	* 填充服务器连接信息
	*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(808);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //本地地址
	memset(&(server_addr.sin_zero), '\0', 8);
	if (bind(server_socket, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) == -1) {       //绑定服务 如果出错 则返回－1
		printf("bind error!\n");
		return -1;
	}
	if (listen(server_socket, 10) == -1 ) {	//开始监听
		printf("listen error!\n");
	return -1;
	}
	if (server_socket == -1) {				//创建socket出错
		printf("Server exception!\n");
		// exit(2);
	}
	while(true) {
		acc_socket = accept(server_socket, (struct sockaddr *)&client_addr, &sock_size); //接收连接
		int numbytes;
		char buf[100];
		if ((numbytes=recv(acc_socket, buf, 99, 0)) == -1) {
		perror("recv");
		// exit(1);
		}
  		// printf("buf ... %s", buf);      //测试用
		char *reponse = 
			"HTTP/1.0 200 OK\r\n"\
			"Content-type: text/html\r\n"\
			"Content-length: 11\r\n\r\n"\
			"Hello World";
		send(acc_socket, reponse, strlen(reponse), 0);
	}
	return 0;
}

/*
// 查询
int _tmain(int argc, _TCHAR* argv[])
{
	MYSQL mysql;
	mysql_init (&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root",NULL,"test",3306,NULL,0)) {//mydb为你所创建的数据库，3306为端口号，可自行设定 
		printf("数据库连接失败"); 
		return FALSE;
	}

	char *ch_query;
	ch_query="select * from test";
	if(mysql_real_query(&mysql, ch_query,(UINT)strlen(ch_query))!=0){ 
		printf("数据库中表格出错"); 
	}
	MYSQL_RES *result;
	MYSQL_ROW row;
	if(!(result=mysql_use_result(&mysql))){ 
		printf("读取数据集失败"); 
	}
	int i=0;
	while(row=mysql_fetch_row(result)){
		printf("%s\r\n",row[0]);
		i++;
	}
	mysql_free_result(result);

	mysql_close(&mysql);

	return 0;
}
*/

