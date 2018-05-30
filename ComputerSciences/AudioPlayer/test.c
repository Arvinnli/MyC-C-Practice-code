#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h> 
#include <conio.h>
#include <direct.h>
#include <strings.h>
#include <string.h>


typedef struct{
    int size;
    int a[0];
}buffer;
int main(int argc,char** argv){

    int i;
    buffer buf = {0};
    buf.size = 100;

    buf.a = malloc(buf.size);
    for(i=0;i<buf.size;i++){
        buf.a[i] = i;
    }

    free(buf.a);
    buf.size = 0;

    

    return 0;
}