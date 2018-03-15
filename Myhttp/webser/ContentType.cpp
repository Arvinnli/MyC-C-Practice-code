#include "ContentType.h"
#include "ArvinnFunc.h"
using namespace std;
char* ContentType::getpostfix(char* path,char* postfix){
    
    int i,flag=0;
    if(path==NULL||postfix == NULL){
        return NULL;
    }
    for(i=0;path[i];i++){
        if(path[i] == '.'){
            flag = i;
        }
    } 
    strcpy(postfix,path+flag);  
    return  path+flag;
}
char* ContentType::getfilename(char* path,char* filename){
    
    int i,flag=0;
    if(path==NULL||filename == NULL){
        return NULL;
    }
    for(i=0;path[i];i++){
        if(path[i] == '/'||path[i] == '\\'){
            flag = i;
        }
    }
    strcpy(filename,path+flag);    
    return path+flag;
}
char* ContentType::gettype(char* filename,char* type){
    int i;
    char buf[128];
     if(filename==NULL||type == NULL){
        return NULL;
    }
    ArvinnFunc::bzero(buf,128);
    getpostfix(filename,buf);

    for(i=0;mimetable[i].postfix != NULL;i++){
        if(strcmp(mimetable[i].postfix,buf)==0){
            strcpy(type,mimetable[i].type);
            return (char*)mimetable[i].type;
        }
    }
    // if(mimetable[i].postfix==NULl){
    //     strcpy(type,"mimetable[i].type");
    // }
    return NULL;
}