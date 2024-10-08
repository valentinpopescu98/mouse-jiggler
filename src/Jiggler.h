#pragma once
#include <chrono>
#include <thread>
#include <conio.h>
#include <iostream>

#include "WinAPI.h"

class Jiggler {
	public:
		// time in seconds, time step in miliseconds, radius in pixels, mouse button to press
		void rotateCursor(unsigned long long time, unsigned long long timeStep, int rad, MouseBtn mouseBtn);
	private:
		// radius in pixels
		void moveCursor(int rad);

		std::chrono::steady_clock::time_point startTime, endTime, currentTime;
		unsigned long long elapsedTime;
};
