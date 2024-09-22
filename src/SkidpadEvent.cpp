#include "SkidpadEvent.hpp"
#include "utils.hpp"
#include <iostream>
#include <GeographicLib/Geodesic.hpp>

using namespace GeographicLib;

void SkidpadEvent::start() {
    std::cout << "Starting Skidpad Event\n";

    Timer timer;
    int lapCount = 0;

    double startLat, startLon, startOrientation;
    const Geodesic& geod = Geodesic::WGS84();
    double lat1, lon1, lat2, lon2;
    bool startLineCreated = false;

    while (lapCount < 4) {
        // Incoming real-time data: [latitude, longitude, orientation, currenttime]
        double carLat, carLon, carOrientation, currentTime;
        get_incoming_data(carLat, carLon, carOrientation, currentTime);

        if (!startLineCreated) {
            startLat = carLat;
            startLon = carLon;
            startOrientation = carOrientation;

            geod.Direct(startLat, startLon, startOrientation + 90, 2.5, lat1, lon1);
            geod.Direct(startLat, startLon, startOrientation - 90, 2.5, lat2, lon2);
            startLineCreated = true;
            timer.start();
        }

        bool crossedLine = crossed_start_line(carLat, carLon, lat1, lon1, lat2, lon2);
        if (crossedLine) {
            lapCount++;
            std::cout << "Lap " << lapCount << " completed at " << currentTime << " seconds.\n";
        }

        timer.update();
    }

    std::cout << "Skidpad event completed after " << lapCount << " laps.\n";
}
