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
	HWND renderWindow; //Окно рендеринга OpenGL
	HWND UIWindow; //Окно рендеринга интерфейса

	//Объекты для работы UI, созданном на веб технологиях
	Awesomium::WebCore* core = 0;
	Awesomium::WebView* view = 0;

	//Класс UI для манипуляций с интерфейсом
	UI mainUI = NULL;


public:
	Engine(HINSTANCE hInstance); //Инициализирует движок

	bool createRender(); //Инициализирует окна рендеринга OpenGL и интерфейса, запускает главный цикл движка
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //Функция для обработки сообщений окон, функция должна поддерживать обработку обоих окон

	UI getUI(HWND ui, Awesomium::WebCore* core, Awesomium::WebView* view); //Получает экземпляр класса UI для текущего окна


};