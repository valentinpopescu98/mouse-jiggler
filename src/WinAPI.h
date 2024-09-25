#pragma once
#include <Windows.h>
#include <iostream>

enum MouseBtn {
	LEFT,
	MIDDLE,
	RIGHT
};

class WinAPI {
	public:
		static void getCursorPos();
		static void setCursorPos(int x, int y);
		static void mousePress(MouseBtn button);

		static int x, y;
};
