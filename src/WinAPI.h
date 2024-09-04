#pragma once
#include <Windows.h>
#include <iostream>

class WinAPI {
	public:
		static void getMousePos();
		static void setMousePos(int x, int y);

		static int mousePosX, mousePosY;
};
