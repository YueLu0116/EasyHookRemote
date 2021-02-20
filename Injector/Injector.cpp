// Injector.cpp : be responsible for injecting a DLL into the target application.
//

#include <iostream>
#include <string>
#include <tchar.h>
#include <cstring>
#include <easyhook/easyhook.h>
#include <windows.h>

int wmain(int argc, _TCHAR* argv[])
{
    DWORD processId;
    std::wcout << "Enter the target process Id: ";
    std::cin >> processId;

    DWORD freqOffset = 0;
    std::cout << "Enter a frequency offset in hertz (e.g. 800): ";
    std::cin >> freqOffset;

    // vc++ won't tolerate string literal assignment to pointer to non-const char anymore.
    // wrong: WCHAR* dllToInject = L"..\\Debug\\BeepHook.dll";    // Maybe changed
    WCHAR dllToInject[] = L"..\\Release\\BeepHook.dll";
    wprintf(L"Attemping to inject: %s\n\n", dllToInject);


    // Injects a library into the target process.
    NTSTATUS nt = RhInjectLibrary(
        processId,
        0,
        EASYHOOK_INJECT_DEFAULT,
        dllToInject,
        NULL,
        &freqOffset,
        sizeof(DWORD));

    if (nt != 0) {
        printf("RhInjectLibrary failed with error code = %d\n", nt);
        PWCHAR err = RtlGetLastErrorString();
        std::wcout << err << "\n";
    }
    else {
        std::wcout << L"Library injected successfully.\n";
    }

    std::wcout << "Press enter to exit";
    std::wstring input;
    std::getline(std::wcin, input);
    std::getline(std::wcin, input);
    return 0;
}

