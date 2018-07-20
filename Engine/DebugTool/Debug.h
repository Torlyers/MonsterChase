#pragma once
#include<stdio.h>
#include<stdarg.h>
#include<windows.h>

//only work in debug mode

void PROFILE_LOG(const char * data, ...);



#ifdef NDEBUG

inline void DEBUG_LOCATION() {}
inline void DEBUG_SYSTEM() {}
inline void ASSERT(bool expression) {}
void DEBUG_LOG(const char * data, ...);

#else
//ASSERT
#if defined(_MSC_VER)
#define BREAK_IN_DEBUGGER() __debugbreak()
#elif defined(__GNUC__)
#define BREAK_IN_DEBUGGER() __builtin_trap()
#else
#error "Provide a implementation of BREAK_IN_DEBUGGER"
#endif
inline void ASSERT(bool expression) { if (!expression) BREAK_IN_DEBUGGER(); }


//DEBUG LOGGING

//SYSTEM
#ifdef WIN32 
inline void DEBUG_SYSTEM() { OutputDebugStringA("System: WIN32\n"); }
#else
inline void DEBUG_SYSTEM() { OutputDebugStringA("System: WIN64\n"); }
#endif //WIN32

//LOCATION
inline void DEBUG_LOCATION() { char output[256]; sprintf_s(output, "File: %s Line: %d\n", __FILE__, __LINE__); OutputDebugStringA(output); }


void DEBUG_LOG(const char * data, ...); 
#endif


