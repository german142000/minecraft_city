#include <windows.h>
#include "UI.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebViewListener.h>

#pragma comment(lib, "C:/Program Files (x86)/Awesomium Technologies LLC/Awesomium SDK/1.7.5.1/build/lib/awesomium.lib")

Awesomium::WebCore* core = 0;
Awesomium::WebView* view = 0;

LRESULT CALLBACK gWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

UI::UI(HWND hWnd) {
    const char* gclassName = "IntrfaceOpenGLAppClass";
    const char* gwindowTitle = "IntrfaceOpenGL";
    const int gscreenWidth = 800;
    const int gscreenHeight = 600;

    WNDCLASS gwc = {};
    gwc.lpfnWndProc = gWndProc;
    gwc.hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
    gwc.lpszClassName = gclassName;
    gwc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    if (!RegisterClass(&gwc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    }

    this->ghWnd = CreateWindow(
        gclassName,
        gwindowTitle,
        WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        0, 0,
        800, 600,
        NULL,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);

    Awesomium::WebConfig config;
    core = Awesomium::WebCore::Initialize(config);

    Awesomium::WebPreferences prefs;
    Awesomium::WebSession* session = core->CreateWebSession(Awesomium::WSLit(""), prefs);

    view = core->CreateWebView(800, 600, session, Awesomium::WebViewType::kWebViewType_Window);
    view->set_parent_window(this->ghWnd);

    UINT myTimer = SetTimer(this->ghWnd, 0, 15, NULL);

    view->LoadURL(Awesomium::WebURL(Awesomium::WSLit("http://google.com/")));

    while (view->IsLoading())
    {
        Sleep(50);
        core->Update();
    }
    view->Focus();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND UI::getHWND() {
    return this->ghWnd;
}

LRESULT CALLBACK gWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY: {
        view->Stop();
        view->Destroy();
        core->Update();
        core->Shutdown();
    }
    break;
    case WM_TIMER:
    {
        if (core) {
            core->Update();
        }
    }
    break;
    case WM_SIZE:
    {
        if (view)
        {
            int nWidth = LOWORD(lParam);  // ширина рабочей области 
            int nHeight = HIWORD(lParam); // высота рабочей области 
            view->Resize(nWidth, nHeight);
        }
    }
    break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}