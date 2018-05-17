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

void play(const char* name)          //播放音乐  
{  
    char cmd[MAX_PATH] = {0};  
    // 定义发往MCI的命令，cmd指定命令存储的数组，后面参数跟printf()相同  
    wsprintf(cmd, "open %s", name);  
    // 发送命令。  
    // 一、存储命令的数组首地址，二、接受MCI返回的信息，三、接受数组的长度，四、没用，NULL  
    mciSendString(cmd, "", 0, NULL);  
    wsprintf(cmd, "play %s", name);  
    mciSendString(cmd, "", 0, NULL);  
}  

// 暂停当前曲，曲号由curno记录  
void pause(const char *name)        // 暂停播放  
{  
    char cmd[MAX_PATH] = {0};  
    wsprintf(cmd, "pause %s", name);  
    mciSendString(cmd,"",0,NULL);  
}  
  
// 停止当前曲，曲号由curno记录  
void stop(const char *name)           
{  
    char cmd[MAX_PATH] = {0};   
    wsprintf(cmd, "stop %s", name);  
    mciSendString(cmd,"",0,NULL);   
    wsprintf(cmd, "close %s", name);  
    mciSendString(cmd,"",0,NULL);   
}  