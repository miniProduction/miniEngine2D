#pragma once
#include <Windows.h>
#include <string>

#define TRACE_TYPE_STDOUTPUT 0x0001
#define TRACE_TYPE_DBGVIEW 0x0002
#define TRACE_TYPE_FILE 0x0004

#define TRACE_TYPE (TRACE_TYPE_STDOUTPUT|TRACE_TYPE_DBGVIEW|TRACE_TYPE_FILE)

#define MACRO_Log(_Format, ...) DebugPrintlnA("[Line:%d Function:%s File:%s]"##_Format##"\n",__LINE__,__FUNCSIG__,__FILE__,__VA_ARGS__)

int __cdecl DebugPrintlnA(char const* const _Format, ...);
