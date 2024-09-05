#pragma once
#include <Windows.h>
#include <iostream>

class WinAPI {
	public:
		static void getCursorPos();
		static void setCursorPos(int x, int y);

		static int x, y;
};
