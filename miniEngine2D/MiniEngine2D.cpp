#include "MiniEngine2D.h"
#include "Trace.h"
#include "Graphics.h"


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
	int result = FunctionDebugPrintlnA(_Format, _ArgList);
	__crt_va_end(_ArgList);
	return result;
}

int __cdecl MiniEngine2D::log(wchar_t const* const _Format, ...)
{
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	int result = FunctionDebugPrintlnW(_Format, _ArgList);
	__crt_va_end(_ArgList);
	return result;
}

int __cdecl MiniEngine2D::log(int obj)
{
	return log("%d", obj);
}

int __cdecl MiniEngine2D::log(float obj)
{
	return log("%f", obj);
}

int __cdecl MiniEngine2D::log(double obj)
{
	return log("%lf", obj);
}

int __cdecl MiniEngine2D::logDetail(char const* const _Format, ...)
{
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	int result = FunctionDebugPrintlnDetailA(_Format, _ArgList);
	__crt_va_end(_ArgList);
	return result;
}

int __cdecl MiniEngine2D::logDetail(wchar_t const* const _Format, ...)
{
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	int result = FunctionDebugPrintlnDetailW(_Format, _ArgList);
	__crt_va_end(_ArgList);
	return result;
}

void MiniEngine2D::exportLogToFile(const std::string logFilePath)
{
	::exportLogToFile(logFilePath);
}


void MiniEngine2D::showWindow()
{
	::showWindow();
}


void MiniEngine2D::update()
{
	::update();
}

void MiniEngine2D::clearScreen()
{
	::clearScreen();
}

void MiniEngine2D::drawPoint(int x, int y, const MiniColor&c)
{
	::drawPoint(x, y, c);
}

void MiniEngine2D::drawLine(int x0, int y0, int x1, int y1, const MiniColor&c)
{
	::drawLine(x0, y0, x1, y1, c);
}

void MiniEngine2D::drawRect(int x, int y, int width, int height, const MiniColor&c)
{
	::drawRect(x, y, width, height, c);
}

void MiniEngine2D::drawCircle(int x, int y, double r, const MiniColor&c)
{
	::drawCircle(x, y, r, c);
}

void MiniEngine2D::drawImage( int x, int y, const MiniImage& img)
{
	::drawImage( x, y, img);
}

void MiniEngine2D::setFont(const std::string& fontName, int size)
{
	::setFont(fontName, size);
}


MiniImage MiniEngine2D::makeFontToMiniImage(std::string str, int size)
{
	return ::makeFontToMiniImage(str, size);
}