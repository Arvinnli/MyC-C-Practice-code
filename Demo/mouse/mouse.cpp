

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>

int main()
{
	HANDLE ConsoleWin;
	INPUT_RECORD eventMsg;
	DWORD Pointer ;


	ConsoleWin = GetStdHandle(STD_INPUT_HANDLE);//Get the console window

	while(1){
		ReadConsoleInput(ConsoleWin, &eventMsg, 1, &Pointer);//Read input msg
		if (eventMsg.EventType == MOUSE_EVENT && eventMsg.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			printf("Right button clicked.");
		}
		if (eventMsg.EventType == MOUSE_EVENT && eventMsg.Event.MouseEvent.dwEventFlags == RIGHTMOST_BUTTON_PRESSED) {
			printf("Left button double clicked.");
		}	
        if(eventMsg.EventType == MOUSE_EVENT){
            printf("jjyy\n");
        }
	}
    return 0;
}

