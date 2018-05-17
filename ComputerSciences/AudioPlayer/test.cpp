#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h> 
#include <conio.h>
#include <direct.h>
#include <strings.h>
#include <string.h>
#include <string>
#pragma comment(lib,"Winmm.lib")

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
        Player();
        ~Player();
        void play();
        void pause();
        void stop();
        void setState(State* state){
            mCurState = state;
        }
        void setFile(const char* file){
            mFIle = file;
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
        string getFile(){
            return mFIle;
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
            _play(resume);
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
    mCurState->play();
}
void Player::pause(){
    mCurState->pause();
}
void Player::stop(){
    mCurState->stop();
}

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

void _play(const char* name)          //��������  
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
void _pause(const char *name)        // ��ͣ����  
{  
    char cmd[MAX_PATH] = {0};  
    wsprintf(cmd, "pause %s", name);  
    mciSendString(cmd,"",0,NULL);  
}  
  
// ֹͣ��ǰ����������curno��¼  
void _stop(const char *name)           
{  
    char cmd[MAX_PATH] = {0};   
    wsprintf(cmd, "stop %s", name);  
    mciSendString(cmd,"",0,NULL);   
    wsprintf(cmd, "close %s", name);  
    mciSendString(cmd,"",0,NULL);   
}  