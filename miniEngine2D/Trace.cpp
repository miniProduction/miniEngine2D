#include "Trace.h"

#include <Windows.h>
#include <cstdio>
#include <vector>
#include <string>
#include <mutex>

std::mutex mutexLogs;
std::vector<std::string> logs;


int __cdecl DebugPrintlnA(char const* const _Format, ...) {
	int _Result = 0;
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);

	_Result = _vscprintf_l(_Format, NULL, _ArgList) + 1;
	char* const _Buffer = new char[_Result]();
	if (_Buffer != NULL) {
		_Result = _vsprintf_l(_Buffer, _Format, NULL, _ArgList);
		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogs.lock();
			printf("%s", _Buffer);
			mutexLogs.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringA(_Buffer);
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogs.lock();
			logs.push_back(_Buffer);
			mutexLogs.unlock();
		}

		delete[] _Buffer;
	}

	__crt_va_end(_ArgList);

	return _Result;
}