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

void WinAPI::mousePress(MouseBtn button) {
    INPUT input[2] = { 0 };

    // Determine which mouse button to click
    switch (button) {
        case MouseBtn::LEFT:
            input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
            break;
        case MouseBtn::MIDDLE:
            input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            input[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            break;
        case MouseBtn::RIGHT:
            input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            break;
        default:
            std::cerr << "Invalid mouse button specified.\n";
            return;
    }

    // Send the input
    input[0].type = INPUT_MOUSE;
    input[1].type = INPUT_MOUSE;
    SendInput(2, input, sizeof(INPUT));
    if (SendInput(2, input, sizeof(INPUT)) != 2) {
        std::cerr << "Failed to send mouse input.\n";
    }
}
