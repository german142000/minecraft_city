#pragma once

extern bool readUIThread; //����, ���������� �� ��� � ������ ������ �����  ���������� ������ ����� ����������������� ����������
extern bool readOpenGLThread; //����, ���������� �� ��� � ������ ������ �����  ���������� ������ ����� OpenGL

extern HWND UIhWnd;

class UI {
private:
	HWND ghWnd;
public:
	UI(HWND hWnd, HINSTANCE inst);
	HWND getHWND();
};


