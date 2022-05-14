#include "Trace.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <DbgHelp.h>
#pragma comment (lib, "Dbghelp.lib")

std::mutex mutexLogsA;
std::vector<std::string> logsA;

std::mutex mutexLogsW;
std::vector<std::wstring> logsW;


int __cdecl DebugPrintlnA(char const* const _Format, ...) {
	int _Result = 0;

	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);

	_Result = _vscprintf_l(_Format, NULL, _ArgList) + 1;
	char* const _Buffer = new char[_Result]();
	if (_Buffer != NULL) {
		_Result = _vsprintf_l(_Buffer, _Format, NULL, _ArgList);
		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogsA.lock();
			printf("%s", _Buffer);
			mutexLogsA.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringA(_Buffer);
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogsA.lock();
			logsA.push_back(_Buffer);
			mutexLogsA.unlock();
		}
	}

	delete[] _Buffer;
	__crt_va_end(_ArgList);

	return _Result;
}
int __cdecl DebugPrintlnW(wchar_t const* const _Format, ...) {
	int _Result = 0;

	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);

	_Result = _vscwprintf_l(_Format, NULL, _ArgList) + 1;
	wchar_t* const _Buffer = new wchar_t[_Result]();
	if (_Buffer != NULL) {
		_Result = _vswprintf_l(_Buffer, _Format, NULL, _ArgList);
		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogsW.lock();
			//wprintf(L"%s", _Buffer);
			int size = WideCharToMultiByte(CP_ACP, 0, _Buffer, -1, NULL, 0, NULL, FALSE);
			char* _BufferA = new char[size]();
			WideCharToMultiByte(CP_ACP, 0, _Buffer, -1, _BufferA, size, NULL, FALSE);
			printf("%s", _BufferA);
			delete[] _BufferA;
			mutexLogsW.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringW(_Buffer);
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogsW.lock();
			logsW.push_back(_Buffer);
			mutexLogsW.unlock();
		}

	}

	delete[] _Buffer;
	__crt_va_end(_ArgList);

	return _Result;
}

int __cdecl FunctionDebugPrintlnA(char const* const _Format, char const* const _Info, va_list _ArgList) {
	int _Result = 0;

	_Result = _vscprintf_l(_Format, NULL, _ArgList) + 1;
	char* const _Buffer = new char[_Result]();
	if (_Buffer != NULL) {
		_Result = _vsprintf_l(_Buffer, _Format, NULL, _ArgList);

		//拼接信息头
		std::string record = _Info;
		record += _Buffer;
		record += '\n';
		_Result = record.size();

		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogsA.lock();
			printf("%s", record.c_str());
			mutexLogsA.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringA(record.c_str());
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogsA.lock();
			logsA.push_back(record);
			mutexLogsA.unlock();
		}

		delete[] _Buffer;
	}

	return _Result;
}
int __cdecl FunctionDebugPrintlnW(wchar_t const* const _Format, wchar_t const* const _Info, va_list _ArgList){
	int _Result = 0;

	_Result = _vscwprintf_l(_Format, NULL, _ArgList) + 1;
	wchar_t* const _Buffer = new wchar_t[_Result]();
	if (_Buffer != NULL) {
		_Result = _vswprintf_l(_Buffer, _Format, NULL, _ArgList);

		//拼接信息头
		std::wstring record = _Info;
		record += _Buffer;
		record += L'\n';
		_Result = record.size();

		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogsW.lock();
			//wprintf(L"%s", record.c_str());
			int size = WideCharToMultiByte(CP_ACP, 0, record.c_str(), -1, NULL, 0, NULL, FALSE);
			char* _BufferA = new char[size]();
			WideCharToMultiByte(CP_ACP, 0, record.c_str(), -1, _BufferA, size, NULL, FALSE);
			printf("%s", _BufferA);
			delete[] _BufferA;

			mutexLogsW.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringW(record.c_str());
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogsW.lock();
			logsW.push_back(record);
			mutexLogsW.unlock();
		}

		delete[] _Buffer;
	}

	return _Result;
}

HANDLE hProcess = (HANDLE)-1;

int __cdecl FunctionDebugPrintlnA(char const* const _Format, va_list _ArgList) {
	SymInitialize(hProcess, NULL, TRUE);
	// 调用调试函数的堆栈示意图
	// FunctionDebugPrintlnA();
	// yourlog();
	// foo();
	// ...
	// 所以这里只关心栈次次顶[foo()]
#define MAX_STACK_FRAMES 3
	void* pStackAddress[MAX_STACK_FRAMES];
	if (CaptureStackBackTrace(0, MAX_STACK_FRAMES, pStackAddress, NULL) != MAX_STACK_FRAMES) {
		//堆栈获取失败
		return -1;
	}

	//通过上边示意图分析这里只读取第三层相关信息
	//SYMBOL_INFO_PACKAGE
	size_t address = size_t(pStackAddress[2]);
	DWORD64 displacementSym = 0;
	char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)]{ 0 };
	SYMBOL_INFO* pSymbol = (SYMBOL_INFO*)buffer;
	pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	pSymbol->MaxNameLen = MAX_SYM_NAME;
	DWORD displacementLine = 0;
	IMAGEHLP_LINE line;
	line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
	SymFromAddr(hProcess, address, &displacementSym, pSymbol);
	SymGetLineFromAddr(hProcess, address, &displacementLine, &line);
	
	//创建日志信息头
	const char* _FormatInfo = "[Line:%d Function:%s File:%s]";
	int size = _scprintf_l(_FormatInfo, NULL, line.LineNumber, pSymbol->Name, line.FileName) + 1;
	char* const _Info = new char[size]();
	sprintf(_Info, _FormatInfo, line.LineNumber, pSymbol->Name, line.FileName);

	int _Result = 0;
	_Result = _vscprintf_l(_Format, NULL, _ArgList) + 1;
	char* const _Buffer = new char[_Result]();
	if (_Buffer != NULL) {
		_Result = _vsprintf_l(_Buffer, _Format, NULL, _ArgList);

		//拼接信息头
		std::string record = _Info;
		record += _Buffer;
		record += '\n';
		_Result = record.size();

		if (TRACE_TYPE & TRACE_TYPE_STDOUTPUT) {
			mutexLogsA.lock();
			printf("%s", record.c_str());
			mutexLogsA.unlock();
		}

		if (TRACE_TYPE & TRACE_TYPE_DBGVIEW) {
			OutputDebugStringA(record.c_str());
		}

		if (TRACE_TYPE & TRACE_TYPE_FILE) {
			mutexLogsA.lock();
			logsA.push_back(record);
			mutexLogsA.unlock();
		}
	}

	delete[] _Info;
	delete[] _Buffer;
	return _Result;
}

void test() {

	HANDLE hProcess = (HANDLE)-1;
	SymInitialize(hProcess, NULL, TRUE);
#define MAX_STACK_FRAMES 12
	void* pStackAddress[MAX_STACK_FRAMES];

	WORD realStackFrames = CaptureStackBackTrace(0, MAX_STACK_FRAMES, pStackAddress, NULL);
	for (int i = 0; i < realStackFrames; ++i) {
		size_t address = size_t(pStackAddress[i]);
		DWORD64 displacementSym = 0;
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		SYMBOL_INFO* pSymbol = (SYMBOL_INFO*)buffer;
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;

		DWORD displacementLine = 0;
		IMAGEHLP_LINE line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

		SymFromAddr(hProcess, address, &displacementSym, pSymbol);
		SymGetLineFromAddr(hProcess, address, &displacementLine, &line);
		std::cout << pSymbol->Name << ' ';
		std::cout << line.FileName << ' ' <<line.LineNumber<< std::endl;
	}
}
