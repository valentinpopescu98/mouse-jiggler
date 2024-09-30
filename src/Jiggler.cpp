#include "Jiggler.h"

void Jiggler::rotateCursor(unsigned long long time, unsigned long long timeStep, int rad, MouseBtn mouseBtn) {
	// get the current time
	startTime = std::chrono::steady_clock::now();
	// get the end time by adding given seconds to the start time
	endTime = startTime + std::chrono::seconds(time);

	// start global keyboard hook to enable user input while window is not focused
	WinAPI::startKbHook();

	// rotate mouse in circle for time
	while (std::chrono::steady_clock::now() < endTime) {
		currentTime = std::chrono::steady_clock::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

		// check if a key has been pressed
		if (WinAPI::kbBtnPressed) {
			std::cout << "Application is terminating...\n";
			std::cout << "Application finished after " << elapsedTime << " seconds.\n";

			WinAPI::stopKbHook();
			_getch(); // wait for a new keypress with the window focused (so the user can read the logs)
			return;
		}

		WinAPI::getCursorPos();
		moveCursor(rad);
		WinAPI::mousePress(mouseBtn);

		// to prevent the loop from running too fast, add a small sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
	}

	std::cout << "Application finished after " << time << " seconds.\n";
	WinAPI::stopKbHook();
	_getch(); // wait for a new keypress with the window focused (so the user can read the logs)
}

void Jiggler::moveCursor(int rad) {
	double angle = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0;

	// calculate x and y based on the angle
	WinAPI::cursorX = static_cast<int>(WinAPI::cursorX + rad * cos(angle));
	WinAPI::cursorY = static_cast<int>(WinAPI::cursorY + rad * sin(angle));

	// persist new cursor position to Windows
	WinAPI::setCursorPos(WinAPI::cursorX, WinAPI::cursorY);
}
