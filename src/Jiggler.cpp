#include "Jiggler.h"

Jiggler::Jiggler() {
	// get initial cursor position
	WinAPI::getMousePos();
}

void Jiggler::rotateCursor(unsigned long long time, unsigned long long timeStep, int rad) {
	// get the current time
	startTime = std::chrono::steady_clock::now();
	// get the end time by adding given seconds to the start time
	endTime = startTime + std::chrono::seconds(time);

	// rotate mouse in circle for time
	while (std::chrono::steady_clock::now() < endTime) {
		// Check if a key has been pressed
		if (_getch()) {
			std::cout << "Key pressed to stop application...\n";
			_getch();
			return;
		}

		currentTime = std::chrono::steady_clock::now();
		//auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		//std::cout << elapsed_ns << std::endl;

		moveCursor(rad);

		// to prevent the loop from running too fast, add a small sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
	}

	std::cout << "Application finished after " << time << " seconds.\n";
	_getch();
}

void Jiggler::moveCursor(int rad) {
	double angle = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0;

	// Calculate x and y based on the angle
	WinAPI::mousePosX = static_cast<int>(WinAPI::mousePosX + rad * cos(angle));
	WinAPI::mousePosY = static_cast<int>(WinAPI::mousePosY + rad * sin(angle));

	// Persist new cursor position to Windows
	WinAPI::setMousePos(WinAPI::mousePosX, WinAPI::mousePosY);

	//std::cout << "Mouse Position: (" << WinAPI::mousePosX << ", " << WinAPI::mousePosY << ")\n";
}
