#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "TableDrawer/TableDrawer.h"

const SIZE MIN_WINDOW_SIZE = SIZE{400, 300};
const SIZE FIRST_WINDOW_SIZE = SIZE{800, 600};
const COLORREF BACKGROUND_COLOR = RGB(255, 255, 255);

static TableDrawer tableDrawer = TableDrawer(6);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    tableDrawer.strings.emplace_back(L"1");
    tableDrawer.strings.emplace_back(L"222222 222 2222");
    tableDrawer.strings.emplace_back(L"33333333333333333333333333333");
    tableDrawer.strings.emplace_back(L"444444444 44444444444 44444 444 444 4444444");
    tableDrawer.strings.emplace_back(L"5");
    tableDrawer.strings.emplace_back(L"66666");
    tableDrawer.strings.emplace_back(L"77 777777 7777 777 777 7 7777");
    tableDrawer.strings.emplace_back(L"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22");
    tableDrawer.strings.emplace_back(L"8888");
    tableDrawer.strings.emplace_back(L"9");
    tableDrawer.strings.emplace_back(L"000000000000000000000000000000000000000000000000000000");

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    const wchar_t WINDOW_CLASS[] = L"MAIN_WINDOW_CLASS";
    const wchar_t WINDOW_TITLE[] = L"Table ^_^";

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(BACKGROUND_COLOR);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = WINDOW_CLASS;
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
            // Optional window styles.
            0x0,
            // Window class
            WINDOW_CLASS,
            // Window text
            WINDOW_TITLE,
            // Window style
            WS_OVERLAPPEDWINDOW,
            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, FIRST_WINDOW_SIZE.cx, FIRST_WINDOW_SIZE.cy,
            // Parent window
            nullptr,
            // Menu
            nullptr,
            // Instance handle
            hInstance,
            // Additional application data
            nullptr
    );

    if (hwnd == nullptr) {
        MessageBoxW(nullptr, L"Error creating window", L"Attention", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            RECT rcClientRect;
            GetClientRect(hwnd, &rcClientRect);

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Gdiplus::Graphics graphics = Gdiplus::Graphics(hdc);

            LONG edgesOffset = 10;
            LONG tableWidth = rcClientRect.right - rcClientRect.left - edgesOffset*2;
            LONG tableHeight = rcClientRect.bottom - rcClientRect.top - edgesOffset*2;
            Gdiplus::RectF clientRectF(edgesOffset, edgesOffset, tableWidth, tableHeight);
            tableDrawer.draw(&graphics, clientRectF);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = MIN_WINDOW_SIZE.cx;
            lpMMI->ptMinTrackSize.y = MIN_WINDOW_SIZE.cy;
            break;
        }
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;
}

