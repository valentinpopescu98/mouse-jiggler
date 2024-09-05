#include "WinAPI.h"

int WinAPI::x;
int WinAPI::y;

void WinAPI::getCursorPos() {
	POINT p;

	if (GetCursorPos(&p)) {
		x = p.x;
		y = p.y;
	} else {
		std::cerr << "Failed to get cursor position.\n";
	}
}

void WinAPI::setCursorPos(int x, int y) {
	if (!SetCursorPos(x, y)) {
		std::cerr << "Failed to set cursor position.\n";
	}
}
