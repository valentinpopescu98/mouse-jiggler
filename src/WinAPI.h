#pragma once
#include <iostream>
#include <thread>
#include <atomic>

#include <Windows.h>

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
		static void startKbHook();
		static void stopKbHook();

		static int cursorX, cursorY;
		static std::atomic<bool> kbBtnPressed;
	private:
		static LRESULT CALLBACK kbProc(int nCode, WPARAM wParam, LPARAM lParam);

		static HHOOK hKbHook;
		static std::thread kbHookThread;
};
