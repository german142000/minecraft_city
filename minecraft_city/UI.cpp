#include <windows.h>
#include "UI.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebViewListener.h>
#include <iostream>

#pragma comment(lib, "C:/Program Files (x86)/Awesomium Technologies LLC/Awesomium SDK/1.7.5.1/build/lib/awesomium.lib")

Awesomium::WebCore* core = 0;
Awesomium::WebView* view = 0;

HINSTANCE hinst;

LRESULT CALLBACK gWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

UI::UI(HWND hWnd, HINSTANCE inst) {
    const char* gclassName = "IntrfaceOpenGLAppClass";
    const char* gwindowTitle = "IntrfaceOpenGL";

    hinst = inst;

    WNDCLASS gwc = {0};
    gwc.lpfnWndProc = gWndProc;
    gwc.hInstance = inst;
    gwc.lpszClassName = gclassName;
    gwc.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));

    if (!RegisterClass(&gwc)) {
        MessageBox(NULL, std::to_string(GetLastError()).c_str(), "Graphics window Registration Failed!", MB_ICONEXCLAMATION | MB_OK);
    }

    LONG width = GetSystemMetrics(SM_CXSCREEN);
    LONG height = GetSystemMetrics(SM_CYSCREEN);

    this->ghWnd = CreateWindowEx(
        WS_EX_TOOLWINDOW | WS_EX_LAYERED,
        gclassName,
        gwindowTitle,
        WS_VISIBLE | WS_POPUP,
        0,
        0,
        width,
        height,
        NULL,
        NULL,
        inst,
        NULL
    );

    SetLayeredWindowAttributes(this->ghWnd, RGB(0, 255, 0), 0, LWA_COLORKEY);

    UIhWnd = this->ghWnd;

    Awesomium::WebConfig config;
    core = Awesomium::WebCore::Initialize(config);

    Awesomium::WebPreferences prefs;
    Awesomium::WebSession* session = core->CreateWebSession(Awesomium::WSLit(""), prefs);

    view = core->CreateWebView(width, height, session, Awesomium::WebViewType::kWebViewType_Window);
    view->set_parent_window(this->ghWnd);

    UINT myTimer = SetTimer(this->ghWnd, 0, 15, NULL);

    Awesomium::JSValue result = view->CreateGlobalJavascriptObject(Awesomium::WSLit("tunnel"));
    Awesomium::JSObject& tunnel = result.ToObject();
    tunnel.SetProperty(Awesomium::WSLit("exit"), Awesomium::WSLit("n"));

    //view->inj

    view->LoadURL(Awesomium::WebURL(Awesomium::WSLit("file:///F:/minecraft_city/test.html")));
    view->Focus();

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!readOpenGLThread) {
            readUIThread = true;
            if (this->getKeyValueFromTunnel("exit", tunnel) == L"y") {
                closeEngine = true;
                MessageBox(NULL, "Close", "Error!", MB_ICONEXCLAMATION | MB_OK);
            }
            readUIThread = false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND UI::getHWND() {
    return this->ghWnd;
}

wchar_t* UI::getKeyValueFromTunnel(std::string key, Awesomium::JSObject& tunnel) {
    return (wchar_t*)tunnel.GetProperty(Awesomium::WSLit(key.c_str())).ToString().data();
};

LRESULT CALLBACK gWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY: {
        //UnregisterClass("IntrfaceOpenGLAppClass", GetModuleHandle(NULL));
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