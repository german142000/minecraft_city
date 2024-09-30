#pragma once

class UI {
private:
	HWND ghWnd;
public:
	UI(HWND hWnd);
	HWND getHWND();
};
