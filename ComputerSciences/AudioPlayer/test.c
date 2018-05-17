#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h> 
#include <conio.h>
#include <direct.h>
#include <strings.h>
#include <string.h>
#pragma comment(lib,"Winmm.lib")

// enum STATUS{
//     STATUS_STOP=0,

// };
static void play(const char *name);
static void pause(const char *name);
static void stop(const char *name);
typedef struct{
    void (*play)(const char*);
    void (*pause)(const char*);
    void (*stop)(const char*);
}State;
typedef struct {
    State* mState;
    
}PlayState;
int main(int argc,char** argv){
    char buf[20] = {0};
    if(argc<2){
        printf("Missing parameters.");
        exit(1);
    }
    while(1){
        printf("play/pause/stop/quit\n");
        scanf("%s",buf);
        if(!strncmp(buf,"play",4)){
            play(argv[1]);
        }else if(!strncmp(buf,"pause",5)){
            pause(argv[1]);
        }else if(!strncmp(buf,"stop",4)){
            stop(argv[1]);
        }else if(!strncmp(buf,"quit",4)){
            break;
        }
    }
    // getchar();
    system("cls");
    return 0;
}

void play(const char* name)          //��������  
{  
    char cmd[MAX_PATH] = {0};  
    // ���巢��MCI�����cmdָ������洢�����飬���������printf()��ͬ  
    wsprintf(cmd, "open %s", name);  
    // �������  
    // һ���洢����������׵�ַ����������MCI���ص���Ϣ��������������ĳ��ȣ��ġ�û�ã�NULL  
    mciSendString(cmd, "", 0, NULL);  
    wsprintf(cmd, "play %s", name);  
    mciSendString(cmd, "", 0, NULL);  
}  

// ��ͣ��ǰ����������curno��¼  
void pause(const char *name)        // ��ͣ����  
{  
    char cmd[MAX_PATH] = {0};  
    wsprintf(cmd, "pause %s", name);  
    mciSendString(cmd,"",0,NULL);  
}  
  
// ֹͣ��ǰ����������curno��¼  
void stop(const char *name)           
{  
    char cmd[MAX_PATH] = {0};   
    wsprintf(cmd, "stop %s", name);  
    mciSendString(cmd,"",0,NULL);   
    wsprintf(cmd, "close %s", name);  
    mciSendString(cmd,"",0,NULL);   
}  