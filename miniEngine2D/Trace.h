#pragma once
#include <Windows.h>
#include <string>

#define TRACE_TYPE_STDOUTPUT 0x0001
#define TRACE_TYPE_DBGVIEW 0x0002
#define TRACE_TYPE_FILE 0x0004

#define TRACE_TYPE (TRACE_TYPE_STDOUTPUT|TRACE_TYPE_DBGVIEW|TRACE_TYPE_FILE)

#define _MINI_TEXT(quote) L##quote
#define MINI_TEXT(quote) _MINI_TEXT(quote)

int __cdecl DebugPrintlnA(char const* const _Format, ...);
int __cdecl DebugPrintlnW(wchar_t const* const _Format, ...);

#define MACRO_LogA(_Format, ...) DebugPrintlnA("[Line:%d Function:%s File:%s]" _Format##"\n", __LINE__, __FUNCSIG__, __FILE__, __VA_ARGS__)
#define MACRO_LogW(_Format, ...) DebugPrintlnW(L"[Line:%d Function:%s File:%s]" _Format##"\n", __LINE__, MINI_TEXT(__FUNCSIG__), MINI_TEXT(__FILE__), __VA_ARGS__)

int __cdecl FunctionDebugPrintlnA(char const* const _Format, char const* const _Info, va_list _ArgList);
int __cdecl FunctionDebugPrintlnW(wchar_t const* const _Format, wchar_t const* const _Info, va_list _ArgList);

#ifdef UNICODE
#define MACRO_Log MACRO_LogW
#define FunctionDebugPrintln FunctionDebugPrintlnW
#else
#define MACRO_Log MACRO_LogA
#define FunctionDebugPrintln FunctionDebugPrintlnA
#endif
void test();
