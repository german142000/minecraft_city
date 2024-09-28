#include <iostream>
#include <windows.h>
#include "glew/include/GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h" //Этот файл распространяется вне Windows SDK, поэтому его необходимо скачивать с сайта khronos.org

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HMODULE hLib;
    void (*dpi)();
    hLib = LoadLibrary("User32.dll");
    (FARPROC&)dpi = GetProcAddress(hLib, "SetProcessDPIAware");
    dpi();

    const char* className = "OpenGLAppClass";
    const char* windowTitle = "OpenGL";
    const int screenWidth = 800;
    const int screenHeight = 600;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        className,
        windowTitle,
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        2,
        2,
        screenWidth,
        screenHeight,
        NULL,
        NULL,
        hInstance,
        NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}