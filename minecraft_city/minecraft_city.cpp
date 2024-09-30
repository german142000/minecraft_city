﻿#include <iostream>
#include <windows.h>
#include "glew/include/GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h" //Этот файл распространяется вне Windows SDK, поэтому его необходимо скачивать с сайта khronos.org
#include <vector>

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

#pragma comment(lib, "glew/lib/Release/Win32/glew32.lib")
#pragma comment(lib, "C:/Program Files (x86)/Awesomium Technologies LLC/Awesomium SDK/1.7.5.1/build/lib/awesomium.lib")

#include "ResourcePack.h"
#include "Texture.h"

using namespace std;

HDC phdc;

vector<ResourcePack> resourcePacks;
vector <Texture> textures;

Awesomium::WebCore* core = 0;
Awesomium::WebView* view = 0;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK bWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

    if (hWnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    const char* bclassName = "bOpenGLAppClass";
    const char* bwindowTitle = "bOpenGL";
    const int bscreenWidth = 800;
    const int bscreenHeight = 600;

    WNDCLASS bwc = {};
    bwc.lpfnWndProc = WndProc;
    bwc.hInstance = hInstance;
    bwc.lpszClassName = bclassName;
    bwc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    if (!RegisterClass(&bwc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND bhWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        bclassName,
        bwindowTitle,
        WS_VISIBLE | WS_CHILD,
        2,
        2,
        bscreenWidth,
        bscreenHeight,
        hWnd,
        NULL,
        hInstance,
        NULL);

    Awesomium::WebConfig config;
    core = Awesomium::WebCore::Initialize(config);

    Awesomium::WebPreferences prefs;
    Awesomium::WebSession* session = core->CreateWebSession(Awesomium::WSLit(""), prefs);

    view = core->CreateWebView(800, 600, session, Awesomium::WebViewType::kWebViewType_Window);
    view->set_parent_window(bhWnd);

    UINT myTimer = SetTimer(bhWnd, 0, 15, NULL);

    view->LoadURL(Awesomium::WebURL(Awesomium::WSLit("http://google.com/")));
    while (view->IsLoading())
    {
        Sleep(50);
        core->Update();
    }
    view->Focus();

    HDC hdc = GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (!pixelFormat) {
        CloseWindow(hWnd);
        MessageBox(NULL, "Failed to choose pixel format.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
        CloseWindow(hWnd);
        MessageBox(NULL, "Failed to set pixel format.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    HGLRC temphRC = wglCreateContext(hdc);
    if (!temphRC) {
        CloseWindow(hWnd);
        MessageBox(NULL, "Failed to create OpenGL rendering context.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    if (!wglMakeCurrent(hdc, temphRC)) {
        CloseWindow(hWnd);
        MessageBox(NULL, "Failed to activate OpenGL rendering context.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(temphRC);

    if (!wglCreateContextAttribsARB) {
        CloseWindow(hWnd);
        MessageBox(NULL, "wglCreateContextAttribsARB fail.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC hRC = wglCreateContextAttribsARB(hdc, 0, attribs);

    if (!hRC || !wglMakeCurrent(hdc, hRC)) {
        CloseWindow(hWnd);
        MessageBox(NULL, "Creating render context fail.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        CloseWindow(hWnd);
        MessageBox(NULL, (const char*)glewGetErrorString(err), "GLEW error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    phdc = GetDC(hWnd);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void closeApp() {
    view->Stop();
    //view->session()->Release();
    view->Destroy();
    core->Update();
    core->Shutdown();
    PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE:
        closeApp();
        return 0;
        break;
    case WM_DESTROY:
        closeApp();
        return 0;
        break;
    case WM_PAINT:
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SwapBuffers(phdc);
        return 0;
    }
    break;
    case WM_TIMER:
    {
        if (core){
            core->Update();
        }
    }
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}