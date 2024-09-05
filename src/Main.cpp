#include <iostream>
#include "Jiggler.h"

int main() {
    unsigned long long timeSecs;
    unsigned long long timeStepMs;
    unsigned int radLengthPix;

    std::cout << "How much time should the application run (in seconds)? ";
    std::cin >> timeSecs;

    std::cout << "How often should the cursor position update (in miliseconds)? ";
    std::cin >> timeStepMs;

    std::cout << "How big should the radius of the circle around which the cursor will rotate (in pixels)? ";
    std::cin >> radLengthPix;

    Jiggler jiggler;
    jiggler.rotateCursor(timeSecs, timeStepMs, radLengthPix);

    return 0;
}
