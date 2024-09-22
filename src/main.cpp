#include <iostream>
#include "EnduranceEvent.hpp"
#include "SkidpadEvent.hpp"
#include "AccelerationEvent.hpp"

int main() {
    std::cout << "Select an event:\n";
    std::cout << "1. Endurance\n";
    std::cout << "2. Skidpad\n";
    std::cout << "3. Acceleration\n";

    int eventChoice;
    std::cin >> eventChoice;

    switch (eventChoice) {
        case 1: {
            EnduranceEvent endurance;
            endurance.start();
            break;
        }
        case 2: {
            SkidpadEvent skidpad;
            skidpad.start();
            break;
        }
        case 3: {
            AccelerationEvent accel;
            accel.start();
            break;
        }
        default:
            std::cerr << "Invalid choice!\n";
            break;
    }

    return 0;
}
