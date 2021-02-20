// dllmain.cpp : 
// EasyHook is expecting to find an export named NativeInjectionEntryPoint within DLL.
// EasyHook will call this method once the DLL has successfully been injected.
// setting up the thread ACL to include ALL threads EXCEPT the injector thread.
// we will not be uninstalling the hook. Instead we will leave it running until 
// the target process exits.
#include "pch.h"
#include <string>
#include <iostream>
#include "BeepHook.h"

DWORD gFreqOffset = 0;
BOOL WINAPI myBeepHook(DWORD dwFreq, DWORD dwDuration)
{
    std::cout << "\n    BeepHook: ****All your beeps belong to us!\n\n";
    return Beep(dwFreq + gFreqOffset, dwDuration);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo) {


    std::cout << "\n\nNativeInjectionEntryPointt(REMOTE_ENTRY_INFO* inRemoteInfo)\n\n" <<
        "IIIII           jjj               tt                dd !!! \n"
        " III  nn nnn          eee    cccc tt      eee       dd !!! \n"
        " III  nnn  nn   jjj ee   e cc     tttt  ee   e  dddddd !!! \n"
        " III  nn   nn   jjj eeeee  cc     tt    eeeee  dd   dd     \n"
        "IIIII nn   nn   jjj  eeeee  ccccc  tttt  eeeee  dddddd !!! \n"
        "              jjjj                                         \n\n";

    // Your unmanaged and managed entry point will be called with the 
    // following structure after injection:
    std::cout << "Injected by process Id: " << inRemoteInfo->HostPID << "\n";
    std::cout << "Passed data size: " << inRemoteInfo->UserDataSize << "\n";
    if (inRemoteInfo->UserDataSize == sizeof(DWORD)) {
        gFreqOffset = *reinterpret_cast<DWORD*>(inRemoteInfo->UserData);
        std::cout << "Adjusting Beep frequency by: " << gFreqOffset << "\n";
    }

    // The same as local hook
    HOOK_TRACE_INFO hHook = { NULL };
    std::cout << "\n";
    std::cout << "Win32 Beep found at address: " << GetProcAddress(GetModuleHandleW(TEXT("kernel32")), "Beep") << "\n";

    NTSTATUS result = LhInstallHook(
        GetProcAddress(GetModuleHandleW(TEXT("kernel32")), "Beep"),
        myBeepHook,
        NULL,
        &hHook
    );

    if (FAILED(result))
    {
        std::wstring s(RtlGetLastErrorString());
        std::wcout << "Failed to install hook: ";
        std::wcout << s;
    }
    else
    {
        std::cout << "Hook 'myBeepHook installed successfully.";
    }

    // If the threadId in the ACL is set to 0,
    // then internally EasyHook uses GetCurrentThreadId()
    ULONG ACLEntries[1] = { 0 };

    // Disable the hook for the provided threadIds, enable for all others
    LhSetExclusiveACL(ACLEntries, 1, &hHook);

    return;
}