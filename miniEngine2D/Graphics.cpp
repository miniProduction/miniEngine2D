#include<Windows.h>
#include"Graphics.h"


bool full_screen_ = false;
HWND hwnd;
DWORD last_style;
RECT last_rect;



void RestoreFullScreen() {
    SetWindowLong(hwnd, GWL_STYLE, last_style); // 恢复最大化之前的窗口风格
    SetWindowPos(hwnd, NULL, last_rect.left, last_rect.top, last_rect.right - last_rect.left, last_rect.bottom - last_rect.top, NULL); // 恢复最大化之前的窗口位置和大小
    full_screen_ = false;
}

void FullScreen() {
    last_style = GetWindowLong(hwnd, GWL_STYLE); //存储上次的窗口风格
    GetWindowRect(hwnd, &last_rect);             //存储上次的窗口位置和大小
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);       // 获取最大化的窗口大小
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP); // 去掉标题栏
    SetWindowPos(hwnd, NULL, 0, 0, w, h, SWP_FRAMECHANGED); // 设置位置和大小
    full_screen_ = true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_LBUTTONDOWN:
        break;
    case WM_PAINT:
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);  //销毁窗口
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        if (VK_ESCAPE == wParam) {
            if (full_screen_) {
                RestoreFullScreen();
            }
            else {
                FullScreen();
            }
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}



void showWindow()
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

