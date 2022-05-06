#include "MiniEngine2D.h"

MiniEngine2D::MiniEngine2D()
{
}

MiniEngine2D::~MiniEngine2D()
{
}

int __cdecl MiniEngine2D::log(char const* const _Format, ...)
{
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	std::string _buffer = "[Line:%d Function:%s File:%s]";
	_buffer += _Format;
	_buffer += '\n';

	int result = DebugPrintlnA(_buffer.c_str(), __LINE__, __FUNCSIG__, __FILE__, _ArgList);

	__crt_va_end(_ArgList);
	return result;
}
