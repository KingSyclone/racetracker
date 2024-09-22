#include "AccelerationEvent.hpp"
#include "utils.hpp"
#include <iostream>
#include <GeographicLib/Geodesic.hpp>

using namespace GeographicLib;

void AccelerationEvent::start() {
    std::cout << "Starting Acceleration Event\n";

    Timer timer;
    double totalDistance = 0.0;
    double zeroToSixtyTime = 0.0;

    double startLat, startLon, startOrientation;
    const Geodesic& geod = Geodesic::WGS84();
    bool startPositionSet = false;

    while (totalDistance < 75.0) {
        // Incoming real-time data: [latitude, longitude, orientation, currenttime]
        double carLat, carLon, carOrientation, currentTime;
        get_incoming_data(carLat, carLon, carOrientation, currentTime);

        if (!startPositionSet) {
            startLat = carLat;
            startLon = carLon;
            timer.start();
            startPositionSet = true;
        }

        // Calculate distance between last position and current position
        double distanceMoved;
        geod.Inverse(startLat, startLon, carLat, carLon, distanceMoved);
        totalDistance += distanceMoved;

        // Check speed (assuming speed is passed in real-time or calculated from data)
        double speed = get_car_speed();
        if (speed >= 60.0 && zeroToSixtyTime == 0.0) {
            zeroToSixtyTime = timer.elapsed();
            std::cout << "0-60 time: " << zeroToSixtyTime << " seconds.\n";
        }

        startLat = carLat;
        startLon = carLon;

        timer.update();
    }

    std::cout << "Acceleration event completed after 75 meters.\n";
}
