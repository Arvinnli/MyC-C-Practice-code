

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>

int main()
{

LOOP:
    CURSORINFO hCur ;
    // ZeroMemory(&hCur,sizeof(hCur));
    hCur.cbSize=sizeof(hCur);
    GetCursorInfo(&hCur);
    std::cout << hCur.hCursor<< std::endl;
    Sleep(1000);
goto LOOP;
    return 0;
}
