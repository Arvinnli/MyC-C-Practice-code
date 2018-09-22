#include <windows.h>
#include <iostream>
#include <tlhelp32.h>

using namespace std;
int GetProcessCount(const TCHAR *szExeName)
{
    TCHAR sztarget[MAX_PATH];
    lstrcpy(sztarget, szExeName);
    CharLowerBuff(sztarget, MAX_PATH);

    int count = 0;
    PROCESSENTRY32 my;
    HANDLE l = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if ((l) != INVALID_HANDLE_VALUE )
    {
        my.dwSize = sizeof(my);
        if (Process32First(l, &my))
        {
            do
            {
                CharLowerBuff(my.szExeFile, MAX_PATH);
                if (lstrcmp(sztarget, my.szExeFile) == 0)
                {
                    count++;
                }
            } while (Process32Next(l, &my));
        }
        CloseHandle(l);
    }

    return count;
}

int main(int argc, char *argv[])
{
#ifdef UNICODE
    if (GetProcessCount(L"abcdef.exe") > 0)
#else
    if (GetProcessCount("PotPlayerMini.exe") > 0)
#endif
    {
        cout << "Running!.." << endl;
    }
    else
    {
        cout << "Not Running!.." << endl;
    }
    return 0;
}