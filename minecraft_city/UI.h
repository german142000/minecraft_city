#pragma once

extern bool readUIThread; //Флаг, означающий то что в данный момент общие  переменные читает поток пользовательского интерфейса
extern bool readOpenGLThread; //Флаг, означающий то что в данный момент общие  переменные читает поток OpenGL

extern HWND UIhWnd;

class UI {
private:
	HWND ghWnd;
public:
	UI(HWND hWnd, HINSTANCE inst);
	HWND getHWND();
};


