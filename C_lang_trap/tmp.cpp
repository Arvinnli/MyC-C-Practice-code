
#include <sys/types.h>
#include <unistd.h> 
#include <iostream>
#include "conio.h"
#include <windows.h>
#include <setjmp.h>
#include <signal.h>  
#include <unistd.h>  
#include <sys/time.h>  
// size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
// #define __DISP_INPUT
#ifndef WIN32
namespace pwd{
    // #include "conio.h"
    void run(){
        int n = 0;
        while(1){

            char ch = getch();
            #ifdef __DISP_INPUT
            std::cout << ch ;
            Sleep(100);
            #else 
            std::cout << '*' ;
            #endif
            std::cout << (char)0x8 ;
            std::cout << '*' ;
            n++;
            if(n==6){
                break;
            }
        }
    }
}
#endif
namespace tmp1{
    jmp_buf buf;
    void handler(int sig){
        std::cout << "you press ctrl+c" << std::endl;
        longjmp(buf,1);
    }
    void run(){
        signal(SIGINT,handler);

        if(!setjmp(buf)){
            std::cout << "starting" << std::endl;
        }else{
            std::cout << "restarting" << std::endl;
        }
        while(1){
            // Sleep(100);
            std::cout << "Processing..." << std::endl;
        }
    }
}
namespace tmp{
    class Singleton;
    class Singleton{
        public:
            Singleton(){}
            static Singleton* getInstance();

        private:
            static Singleton* mPtr;
        protected:
    };
    Singleton* Singleton::mPtr = NULL;
    Singleton* Singleton::getInstance(){
        if(mPtr==NULL){
            mPtr=new Singleton();
        }
        return mPtr;
    }
    void run(){
        Singleton::getInstance();
    }
}

int main(int argc,char** argv){
    tmp::run();
    // pwd::run();
    return 0;
}



