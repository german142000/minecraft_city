#pragma once

class UI {
private:
	HWND ghWnd;
public:
	UI(HWND uihWnd);
	bool setUIScreen();
};


