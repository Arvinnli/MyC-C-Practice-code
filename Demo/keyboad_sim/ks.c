#include <stdio.h>
#include <windows.h>


//�����  
void click()  
{  
    //�ú����ѹ���Ƶ���Ļ��ָ��λ��  
    SetCursorPos(200,250);  
    //��굥��  
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0,0); //�������  
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //����ɿ�  
}  
//ʹ�ü�������Ҫ��ѯ�Ĺؼ��ʡ�  
void search()  
{  
    //��������  
    keybd_event('J', 0, 0, 0); //����  
    keybd_event('J', 0, 2, 0); //�ɿ�  
    Sleep(500);  
    keybd_event('A', 0, 0, 0); //����  
    keybd_event('A', 0, 2, 0); //�ɿ�  
    Sleep(500);  
    keybd_event('V', 0, 0, 0); //����  
    keybd_event('V', 0, 2, 0); //�ɿ�  
    Sleep(500);  
    keybd_event('A', 0, 0, 0); //����  
    keybd_event('A', 0, 2, 0); //�ɿ�  
    Sleep(500);  
  
    //�س�  
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