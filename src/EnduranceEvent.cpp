#include "EnduranceEvent.hpp"
#include "utils.hpp"
#include <iostream>
#include <GeographicLib/Geodesic.hpp>
#include <cmath>

using namespace GeographicLib;

void EnduranceEvent::start() {
    std::cout << "Starting Endurance Event\n";

    Timer timer;
    double distance = 0.0;
    int lapCount = 0;

    // Assuming start line creation logic is based on first data point
    double startLat, startLon, startOrientation;

    // Create a start line once the car is ready (based on initial data)
    const Geodesic& geod = Geodesic::WGS84();
    double lat1, lon1, lat2, lon2;
    bool startLineCreated = false;

    while (lapCount < 22) {
        // Incoming real-time data: [latitude, longitude, orientation, currenttime]
        double carLat, carLon, carOrientation, currentTime;

        // Example of real data input from the system:
        get_incoming_data(carLat, carLon, carOrientation, currentTime);

        if (!startLineCreated) {
            // Draw start line perpendicular to car orientation
            startLat = carLat;
            startLon = carLon;
            startOrientation = carOrientation;

            // Create start line based on orientation
            geod.Direct(startLat, startLon, startOrientation + 90, 2.5, lat1, lon1);
            geod.Direct(startLat, startLon, startOrientation - 90, 2.5, lat2, lon2);
            startLineCreated = true;
            timer.start();
        }

        // Check if the car crosses the start line
        bool crossedLine = crossed_start_line(carLat, carLon, lat1, lon1, lat2, lon2);
        if (crossedLine) {
            lapCount++;
            std::cout << "Lap " << lapCount << " completed at " << currentTime << " seconds.\n";
        }

        // Update the timer and refresh the display
        timer.update();
    }

    std::cout << "Endurance event completed after " << lapCount << " laps.\n";
}
