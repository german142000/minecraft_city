#pragma once

#pragma comment(lib, "glew/lib/Release/Win32/glew32.lib")
#pragma comment(lib, "C:/Program Files (x86)/Awesomium Technologies LLC/Awesomium SDK/1.7.5.1/build/lib/awesomium.lib")

#include <Windows.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebViewListener.h>

#include "UI.h"



class Engine {
private:
	HWND renderWindow; //���� ���������� OpenGL
	HWND UIWindow; //���� ���������� ����������

	//������� ��� ������ UI, ��������� �� ��� �����������
	Awesomium::WebCore* core = 0;
	Awesomium::WebView* view = 0;

	//����� UI ��� ����������� � �����������
	UI mainUI = NULL;


public:
	Engine(HINSTANCE hInstance); //�������������� ������

	bool createRender(); //�������������� ���� ���������� OpenGL � ����������, ��������� ������� ���� ������
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //������� ��� ��������� ��������� ����, ������� ������ ������������ ��������� ����� ����

	UI getUI(HWND ui, Awesomium::WebCore* core, Awesomium::WebView* view); //�������� ��������� ������ UI ��� �������� ����


};