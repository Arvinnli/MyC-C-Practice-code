#include <stdio.h>
#include <windows.h>

int main(int argc,char** argv){

reset:
    keybd_event('1', 0, 0, 0); //
    Sleep(200);
    keybd_event('1', 0, 2, 0); //
    Sleep(1100);
    goto reset;
    return 0;
}