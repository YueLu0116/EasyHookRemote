// EasyHookRemote.cpp : will be injected
//                      provide process Id

#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
    std::string value;
    while (true) {
        HANDLE currentThread = GetCurrentThread();
        std::cout << "Target.exe process id: ";
        std::cout << GetProcessIdOfThread(currentThread);
        std::cout << "\n";
        CloseHandle(currentThread);

        std::cout << "Press <enter> to Beep (E to exit): ";
        std::getline(std::cin, value);
        if (value == "E") {
            break;
        }
        Beep(500, 500);
    }
    return 0;
}


