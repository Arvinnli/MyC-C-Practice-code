// ComDBMon.cpp : �������̨Ӧ�ó������ڵ㡣
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
	SOCKET server_socket;		//��������socket
	SOCKET acc_socket;			//���յ����û����ӵ�socket
	int sock_size = sizeof(struct sockaddr_in);  
	struct sockaddr_in client_addr;			//�ͻ�������Ϣ
	struct sockaddr_in server_addr;			//�ͻ�������Ϣ

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {				//�������ֵΪ��1 �����
		return -1;
	}
	/*
	* ��������������Ϣ
	*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(808);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //���ص�ַ
	memset(&(server_addr.sin_zero), '\0', 8);
	if (bind(server_socket, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) == -1) {       //�󶨷��� ������� �򷵻أ�1
		printf("bind error!\n");
		return -1;
	}
	if (listen(server_socket, 10) == -1 ) {	//��ʼ����
		printf("listen error!\n");
	return -1;
	}
	if (server_socket == -1) {				//����socket����
		printf("Server exception!\n");
		// exit(2);
	}
	while(true) {
		acc_socket = accept(server_socket, (struct sockaddr *)&client_addr, &sock_size); //��������
		int numbytes;
		char buf[100];
		if ((numbytes=recv(acc_socket, buf, 99, 0)) == -1) {
		perror("recv");
		// exit(1);
		}
  		// printf("buf ... %s", buf);      //������
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
// ��ѯ
int _tmain(int argc, _TCHAR* argv[])
{
	MYSQL mysql;
	mysql_init (&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root",NULL,"test",3306,NULL,0)) {//mydbΪ�������������ݿ⣬3306Ϊ�˿ںţ��������趨 
		printf("���ݿ�����ʧ��"); 
		return FALSE;
	}

	char *ch_query;
	ch_query="select * from test";
	if(mysql_real_query(&mysql, ch_query,(UINT)strlen(ch_query))!=0){ 
		printf("���ݿ��б�����"); 
	}
	MYSQL_RES *result;
	MYSQL_ROW row;
	if(!(result=mysql_use_result(&mysql))){ 
		printf("��ȡ���ݼ�ʧ��"); 
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

