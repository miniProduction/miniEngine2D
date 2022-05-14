#include<Windows.h>
#include"Graphics.h"

const int bits = 32; 
bool full_screen_ = false;
HWND hwnd;
DWORD last_style;
RECT last_rect;
HDC screen_hdc;
HDC hCompatibleDC;
HBITMAP hCompatibleBitmap;
HBITMAP hOldBitmap;
BITMAPINFO binfo;

Color BUFFER[SCREEN_HEIGHT * SCREEN_WIDTH];


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

/// <summary>
/// 初始化并显示窗口
/// </summary>
void showWindow()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            BUFFER[i * SCREEN_WIDTH + j].r = 0;
            BUFFER[i * SCREEN_WIDTH + j].g = 0;
            BUFFER[i * SCREEN_WIDTH + j].b = 0;

        }
    }

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

    ZeroMemory(&binfo, sizeof(BITMAPINFO));
    binfo.bmiHeader.biBitCount = bits;
    binfo.bmiHeader.biCompression = BI_RGB;
    binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
    binfo.bmiHeader.biPlanes = 1;
    binfo.bmiHeader.biSizeImage = 0;
    binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    binfo.bmiHeader.biWidth = SCREEN_WIDTH;

    screen_hdc = GetDC(hwnd);
    hCompatibleDC = CreateCompatibleDC(screen_hdc);
    hCompatibleBitmap = CreateCompatibleBitmap(screen_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
    hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hCompatibleBitmap);
}

void update()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    putBufferToScreen();
}

void putBufferToScreen()
{
    SetDIBits(screen_hdc, hCompatibleBitmap, 0, SCREEN_HEIGHT, BUFFER, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);
    BitBlt(screen_hdc, -1, -1, SCREEN_WIDTH, SCREEN_HEIGHT, hCompatibleDC, 0, 0, SRCCOPY);
}

void clearScreen()
{

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            //测试颜色:YANAGIZOME
            BUFFER[i * SCREEN_WIDTH + j].r = 145;
            BUFFER[i * SCREEN_WIDTH + j].g = 173;
            BUFFER[i * SCREEN_WIDTH + j].b = 112;

        }
    }
}