#pragma once

#ifdef BEEPHOOK_EXPORTS
#define BEEPHOOK_API __declspec(dllexport)
#else
#define BEEPHOOK_API __declspec(import)
#endif // BEEPHOOK_EXPORTS


#include <easyhook/easyhook.h>
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);
