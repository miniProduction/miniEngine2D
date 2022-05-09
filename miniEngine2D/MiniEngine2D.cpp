#include "MiniEngine2D.h"
#include<Windows.h>






MiniEngine2D::MiniEngine2D()
{

}

MiniEngine2D::~MiniEngine2D()
{
}
int __cdecl MiniEngine2D::log(char const* const _Format, ...)
{
	//创建日志信息头
	const char* _FormatInfo = "[Line:%d Function:%s File:%s]";
	int size = _scprintf_l(_FormatInfo, NULL, __LINE__, __FUNCSIG__, __FILE__) + 1;
	char* const _Buffer = new char[size]();
	sprintf(_Buffer, _FormatInfo, __LINE__, __FUNCSIG__, __FILE__);
	

	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	int result = FunctionDebugPrintlnA(_Format, _Buffer, _ArgList);
	__crt_va_end(_ArgList);
	
	delete[] _Buffer;
	return result;
}
