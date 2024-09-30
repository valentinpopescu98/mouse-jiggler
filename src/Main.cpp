#include <iostream>
#include <string>
#include <unordered_set>

#include "Jiggler.h"
#include "WinAPI.h"

#ifdef max
#undef max
#endif

template <typename T>T showPromptTakeInput(const char* promptMessage) {
    T number;

    while (true) {
        std::cout << promptMessage;
        std::cin >> number;

        // Check if the input was valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
            std::cerr << "Invalid input. Please enter a valid number.\n";
        } else {
            // Valid input; clear the remaining newline character from the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return number;
}

MouseBtn getMouseBtn() {
    std::unordered_set<std::string> validMouseBtns = {
        "l", "L", "left", "LEFT",
        "m", "M", "middle", "MIDDLE",
        "r", "R", "right", "RIGHT"
    };

    std::string mouseBtn;
    while (validMouseBtns.find(mouseBtn) == validMouseBtns.end()) {
        std::cout << "Which mouse input should the mouse execute (LEFT / MIDDLE / RIGHT)? ";
        std::getline(std::cin, mouseBtn);
    }

    if (mouseBtn == "l" || mouseBtn == "L" || mouseBtn == "left" || mouseBtn == "LEFT") {
        return MouseBtn::LEFT;
    } else if (mouseBtn == "m" || mouseBtn == "M" || mouseBtn == "middle" || mouseBtn == "MIDDLE") {
        return MouseBtn::MIDDLE;
    } else if (mouseBtn == "r" || mouseBtn == "R" || mouseBtn == "right" || mouseBtn == "RIGHT") {
        return MouseBtn::RIGHT;
    }
}

int main() {
    unsigned long long timeSecs;
    unsigned long long timeStepMs;
    unsigned int radLengthPix;
    MouseBtn mouseBtn;

    timeSecs = showPromptTakeInput<unsigned long long>("How much time should the application run (in seconds)? ");
    timeStepMs = showPromptTakeInput<unsigned long long>("How often should the cursor position update (in miliseconds)? ");
    radLengthPix = showPromptTakeInput<unsigned int>("How big should the radius of the circle around which the cursor will rotate (in pixels)? ");
    mouseBtn = getMouseBtn();
    std::cout << "\n";

    Jiggler jiggler;
    jiggler.rotateCursor(timeSecs, timeStepMs, radLengthPix, mouseBtn);

    return 0;
}
