#include <stdio.h>
#include <windows.h>



void mouse_click()  
{  
    SetCursorPos(200,250);  
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0); 
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  
}  

  

int main(int argc,char** argv){
    int i=0;
    POINT point;
    while(1){
        GetCursorPos(&point);
        
        Sleep(1000);
        SetCursorPos(point.x+1,point.y);

        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0); //
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //

        Sleep(1000);
        SetCursorPos(point.x,point.y);  
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0); //
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //
        // keybd_event('J', 0, 0, 0); //
        // Sleep(200);
        // keybd_event('J', 0, 2, 0); //
        // Sleep(1100);
        // putchar('\n');


    }

    return 0;
}