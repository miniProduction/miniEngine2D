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
