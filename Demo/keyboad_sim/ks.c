#include <stdio.h>
#include <windows.h>


//鼠标点击  
void click()  
{  
    //该函数把光标移到屏幕的指定位置  
    SetCursorPos(200,250);  
    //鼠标单击  
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0); //左键按下  
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //左键松开  
}  
//使用键盘输入要查询的关键词。  
void search()  
{  
    //键盘输入  
    keybd_event('J', 0, 0, 0); //按下  
    keybd_event('J', 0, 2, 0); //松开  
    Sleep(500);  
    keybd_event('A', 0, 0, 0); //按下  
    keybd_event('A', 0, 2, 0); //松开  
    Sleep(500);  
    keybd_event('V', 0, 0, 0); //按下  
    keybd_event('V', 0, 2, 0); //松开  
    Sleep(500);  
    keybd_event('A', 0, 0, 0); //按下  
    keybd_event('A', 0, 2, 0); //松开  
    Sleep(500);  
  
    //回车  
    keybd_event(0x0d, 0, 0, 0);  
    keybd_event(0x0d, 0, 2, 0);  
    Sleep(500);  
}  
  

int main(int argc,char** argv){
    int i=0;
    POINT point;
    while(1){
        GetCursorPos(&point);
        
        Sleep(1000);
        SetCursorPos(point.x+1,point.y);  
        Sleep(1000);
        SetCursorPos(point.x,point.y);  


    }

    return 0;
}