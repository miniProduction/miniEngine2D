#include "MiniEngine2D.h"
#include<Windows.h>
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
	////创建日志信息头
	//const char* _FormatInfo = "[Line:%d Function:%s File:%s]";
	//int size = _scprintf_l(_FormatInfo, NULL, __LINE__, __FUNCSIG__, __FILE__) + 1;
	//char* const _Buffer = new char[size]();
	//sprintf(_Buffer, _FormatInfo, __LINE__, __FUNCSIG__, __FILE__);
	//

	//va_list _ArgList;
	//__crt_va_start(_ArgList, _Format);
	//int result = FunctionDebugPrintlnA(_Format, _Buffer, _ArgList);
	//__crt_va_end(_ArgList);
	//
	//delete[] _Buffer;
	return result;
}

int __cdecl MiniEngine2D::log(wchar_t const* const _Format, ...)
{
	//创建日志信息头
	const wchar_t* _FormatInfo = L"[Line:%d Function:%s File:%s]";
	int size = _scwprintf_l(_FormatInfo, NULL, __LINE__, MINI_TEXT(__FUNCSIG__), MINI_TEXT(__FILE__)) + 1;
	wchar_t* const _Buffer = new wchar_t[size]();
	swprintf(_Buffer, _FormatInfo, __LINE__, MINI_TEXT(__FUNCSIG__), MINI_TEXT(__FILE__));

	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	int result = FunctionDebugPrintlnW(_Format, _Buffer, _ArgList);
	__crt_va_end(_ArgList);

	delete[] _Buffer;
	return result;
}
//{
//	//创建日志信息头
//	const wchar_t* _FormatInfo = L"[Line:%d Function:%s File:%s]";
//	int size = _scwprintf_l(_FormatInfo, NULL, __LINE__, MINI_TEXT(__FUNCSIG__), MINI_TEXT(__FILE__)) + 1;
//	wchar_t* const _Buffer = new wchar_t[size]();
//	swprintf(_Buffer, _FormatInfo, __LINE__, MINI_TEXT(__FUNCSIG__), MINI_TEXT(__FILE__));
//
//	va_list _ArgList;
//	__crt_va_start(_ArgList, _Format);
//	int result = FunctionDebugPrintlnW(_Format, _Buffer, _ArgList);
//	__crt_va_end(_ArgList);
//
//	delete[] _Buffer;
//	return result;
//}


void MiniEngine2D::showWindow()
{
    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASS wndcls;
    wndcls.cbClsExtra = 0;
    wndcls.cbWndExtra = 0;
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hInstance = hInstance;
    wndcls.lpfnWndProc = WndProc;
    wndcls.lpszClassName = L"miniEngine2D";
    wndcls.lpszMenuName = NULL;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndcls);
    hwnd = CreateWindow(L"miniEngine2D", L"miniEngine2D", WS_OVERLAPPEDWINDOW,
        0, 0, 1280, 720, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


}