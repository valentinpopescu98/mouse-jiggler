#include "WinAPI.h"

int WinAPI::cursorX = 0;
int WinAPI::cursorY = 0;
std::atomic<bool> WinAPI::kbBtnPressed = false;

HHOOK WinAPI::hKbHook;
std::thread WinAPI::kbHookThread;

void WinAPI::getCursorPos() {
	POINT p;

	if (GetCursorPos(&p)) {
        cursorX = p.x;
		cursorY = p.y;
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

void WinAPI::startKbHook() {
    // start the hook in a separate thread to not block the program
    kbHookThread = std::thread([]() {
        hKbHook = SetWindowsHookEx(WH_KEYBOARD_LL, kbProc, nullptr, 0);
        if (!hKbHook) {
            std::cerr << "Failed to set keyboard hook. Error: " << GetLastError() << "\n";
        } else {
            std::cout << "Keyboard hook installed successfully.\n";
            
            MSG msg;
            while (GetMessage(&msg, nullptr, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    });

    if (kbHookThread.joinable()) {
        // detach the thread if it's running the loop
        kbHookThread.detach();
    }
}

void WinAPI::stopKbHook() {
    if (hKbHook) {
        UnhookWindowsHookEx(hKbHook);
        hKbHook = nullptr;
    }
}

LRESULT CALLBACK WinAPI::kbProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            std::cout << "Key pressed!\n";
            kbBtnPressed = true;
        }
    }
    return CallNextHookEx(hKbHook, nCode, wParam, lParam);
}
