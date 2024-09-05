#include "Jiggler.h"

void Jiggler::rotateCursor(unsigned long long time, unsigned long long timeStep, int rad) {
	// get the current time
	startTime = std::chrono::steady_clock::now();
	// get the end time by adding given seconds to the start time
	endTime = startTime + std::chrono::seconds(time);

	// rotate mouse in circle for time
	while (std::chrono::steady_clock::now() < endTime) {
		currentTime = std::chrono::steady_clock::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

		// check if a key has been pressed
		if (_kbhit()) {
			std::cout << "Key pressed to stop application...\n";
			std::cout << "Application finished after " << elapsedTime << " seconds.\n";
			_getch(); // consumes the already-detected keypress from _kbhit
			_getch(); // waits for a new keypress
			return;
		}

		WinAPI::getCursorPos();
		moveCursor(rad);

		// to prevent the loop from running too fast, add a small sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
	}

	std::cout << "Application finished after " << time << " seconds.\n";
	_getch();
}

void Jiggler::moveCursor(int rad) {
	double angle = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0;

	// calculate x and y based on the angle
	WinAPI::x = static_cast<int>(WinAPI::x + rad * cos(angle));
	WinAPI::y = static_cast<int>(WinAPI::y + rad * sin(angle));

	// persist new cursor position to Windows
	WinAPI::setCursorPos(WinAPI::x, WinAPI::y);
}
