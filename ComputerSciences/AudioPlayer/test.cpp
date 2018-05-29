#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h> 
#include <conio.h>
#include <direct.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <iostream>

#pragma comment(lib,"Winmm.lib")

using namespace std;

static void _play(const char *name);
static void _pause(const char *name);
static void _stop(const char *name);
class State{
    public:
        State(){}
        virtual void play(const char* file)=0;
        virtual void pause(const char* file)=0;
        virtual void stop(const char* file)=0;
    private:
    protected:
};
class Player{
    public:
        Player(const char* file);
        ~Player();
        void play();
        void pause();
        void stop();
        void setState(State* state){
            mCurState = state;
        }
        void setFile(const char* file){
            mFile = file;
        }
        State* getCurState(){
            return mCurState;
        }
        State* getPlayingState(){
            return mPlayingState;
        }
        State* getPauseState(){
            return mPauseState;
        }
        State* getStopState(){
            return mStopState;
        }
        const char* getFile(){
            return mFile;
        }
    private:
        State* mCurState;
        State* mPlayingState;
        State* mPauseState;
        State* mStopState;
        const char* mFile;
    protected:
};
class PlayingState:public State{
    public:
        PlayingState(Player* player){
            mPlayer = player;
        }
        virtual void play(const char* name){
            cout << "Current state is playing" << endl;
        }
        virtual void pause(const char* name){
            _pause(name);  
            mPlayer->setState(mPlayer->getPauseState());
        }
        virtual void stop(const char* name){
            _stop(name); 
            mPlayer->setState(mPlayer->getStopState());
        }
    private:
        Player* mPlayer;
    protected:
};
class PauseState:public State{
    public:
        PauseState(Player* player){
            mPlayer = player;
        }
        virtual void play(const char* name){
            _play(name);
            mPlayer->setState(mPlayer->getPlayingState());
        }
        virtual void pause(const char* name){
            cout << "Cur state is Paused" << endl;
        }
        virtual void stop(const char* name){
            _stop(name);
            mPlayer->setState(mPlayer->getStopState());
        }
    private:
        Player* mPlayer;
    protected:
};
class StopState:public State{
    public:
        StopState(Player* player){
            mPlayer = player;
        }
        virtual void play(const char* name){
            _play(name);
            mPlayer->setState(mPlayer->getPlayingState());
        }
        virtual void pause(const char* name){
            cout << "Cur state is Stoped" << endl;
        }
        virtual void stop(const char* name){
            cout << "Cur state is Stoped" << endl;                
        }
    private:
        Player* mPlayer;
    protected:
};
Player::Player(const char* file){
    mPlayingState = new PlayingState(this);
    mPauseState = new PauseState(this);
    mStopState = new StopState(this);
    mCurState = mStopState;
    mFile = file;
}
Player::~Player(){
    delete (PlayingState*)mPlayingState;
    delete (PauseState*)mPauseState;
    delete (StopState*)mStopState;
    mPlayingState = NULL;
    mPauseState = NULL;
    mStopState = NULL;
}
void Player::play(){
    mCurState->play(mFile);
}
void Player::pause(){
    mCurState->pause(mFile);
}
void Player::stop(){
    mCurState->stop(mFile);
}

int main(int argc,char** argv){
    char buf[20] = {0};
   
    if(argc<2){
        printf("Missing parameters.");
        exit(1);
    }
    Player player(argv[1]);
    while(1){
        printf("play/pause/stop/quit\n");
        scanf("%s",buf);
        if(!strncmp(buf,"play",4)){
            player.play();
        }else if(!strncmp(buf,"pause",5)){
            player.pause();
        }else if(!strncmp(buf,"stop",4)){
            player.stop();
        }else if(!strncmp(buf,"quit",4)){
            break;
        }
        system("cls");
    }
    // getchar();
    system("cls");
    return 0;
}

void _play(const char* name)          //播放音乐  
{  
    char cmd[MAX_PATH] = {0};  
    // 定义发往MCI的命令，cmd指定命令存储的数组，后面参数跟printf()相同  
    wsprintf(cmd, "open %s", name);  
    // 发送命令。  
    // 一、存储命令的数组首地址，二、接受MCI返回的信息，三、接受数组的长度，四、没用，NULL  
    mciSendString(cmd,(char*)"", 0, NULL);  
    wsprintf(cmd, "play %s", name);  
    mciSendString(cmd, (char*)"", 0, NULL);  
}  

void _pause(const char *name)        // 暂停播放  
{  
    char cmd[MAX_PATH] = {0};  
    wsprintf(cmd, "pause %s", name);  
    mciSendString(cmd,(char*)"",0,NULL);  
}  

void _stop(const char *name)           
{  
    char cmd[MAX_PATH] = {0};   
    wsprintf(cmd, "stop %s", name);  
    mciSendString(cmd,(char*)"",0,NULL);   
    wsprintf(cmd, "close %s", name);  
    mciSendString(cmd,(char*)"",0,NULL);   
}  