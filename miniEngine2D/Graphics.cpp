#include<Windows.h>
#include"MiniEngine2D.h"
#include"Graphics.h"


bool full_screen_ = false;
HWND hwnd;
DWORD last_style;
RECT last_rect;


void RestoreFullScreen() {
    SetWindowLong(hwnd, GWL_STYLE, last_style); // �ָ����֮ǰ�Ĵ��ڷ��
    SetWindowPos(hwnd, NULL, last_rect.left, last_rect.top, last_rect.right - last_rect.left, last_rect.bottom - last_rect.top, NULL); // �ָ����֮ǰ�Ĵ���λ�úʹ�С
    full_screen_ = false;
}

void FullScreen() {
    last_style = GetWindowLong(hwnd, GWL_STYLE); //�洢�ϴεĴ��ڷ��
    GetWindowRect(hwnd, &last_rect);             //�洢�ϴεĴ���λ�úʹ�С
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);       // ��ȡ��󻯵Ĵ��ڴ�С
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP); // ȥ��������
    SetWindowPos(hwnd, NULL, 0, 0, w, h, SWP_FRAMECHANGED); // ����λ�úʹ�С
    full_screen_ = true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_LBUTTONDOWN:
        break;
    case WM_PAINT:
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);  //���ٴ���
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




