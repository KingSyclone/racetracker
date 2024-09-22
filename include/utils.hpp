#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void start();
    void update();
    double elapsed() const;
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};

void get_incoming_data(double &lat, double &lon, double &orientation, double &currentTime);
bool crossed_start_line(double carLat, double carLon, double lineLat1, double lineLon1, double lineLat2, double lineLon2);
double get_car_speed();
