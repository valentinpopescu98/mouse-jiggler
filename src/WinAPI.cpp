#include "WinAPI.h"

int WinAPI::mousePosX;
int WinAPI::mousePosY;

void WinAPI::getMousePos() {
	POINT p;

	if (GetCursorPos(&p)) {
		mousePosX = p.x;
		mousePosY = p.y;
	} else {
		std::cerr << "Failed to get mouse position.\n";
	}
}

void WinAPI::setMousePos(int x, int y) {
	if (!SetCursorPos(x, y)) {
		std::cerr << "Failed to set mouse position.\n";
	}
}
