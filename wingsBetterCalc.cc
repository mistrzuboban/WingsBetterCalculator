#include <cstdio>
#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>

using namespace std;


double paceToMetersPerSeconds(const string pace) {
    auto pos = pace.find_first_of(":");
    auto minutes = pace.substr(0, pos);
    auto seconds = pace.substr(pos+1);

    auto min = stoi(minutes);
    auto sec = stoi(seconds);
    return 1000.0/(60.0 * min + sec);
}

string metersPerSecondToPace(const double speed) {
    double kmPerMinute = speed * 60.0 / 1000.0;
    double minuteOnKm = 1.0 / kmPerMinute;

    int min = (int)minuteOnKm;
    int sec = (minuteOnKm - min) * 60.0;

    return to_string(min) + ":" + (sec<10 ? "0": "") + to_string(sec);
}


double calcCarAvgSpeed(const double distance, const double delay = 0) {
    if (distance == 0) return 0.0;

    int timeInSec = 1;

    if (distance <= 15000) {
        timeInSec = (distance / 15000.0) * 3600.0 + 1800;
    } else {
    if (distance <= 15000 + 16000) {
        timeInSec = ((distance - 15000) / 16000.0) * 3600.0 + 1 * 3600 + 1800;
    } else
    if (distance <= 15000 + 16000 + 17000) {
        timeInSec = ((distance - 15000 - 16000) / 17000.0) * 3600.0 + 2 * 3600 + 1800;
    } else
    if (distance <= 15000 + 16000 + 17000 + 20000) {
        timeInSec = ((distance - 15000 - 16000 - 17000) / 20000.0) * 3600.0 + 3 * 3600 + 1800;
    } else
        timeInSec = ((distance - 15000 - 16000 - 17000 - 20000) / 35000.0) * 3600.0 + 4 * 3600 + 1800;  
    }

    return distance / (timeInSec - delay);
}

int calcApproximateCarDistance(const double speedInMetersPerSecond) {
    int distance = 0;
    int increment = 10;
    while (calcCarAvgSpeed(distance) < speedInMetersPerSecond) {
        distance += increment;
    }
    return distance;
}



int main() {
    string pace = "5:04";
    int distance = 30000;
    double runnerSpeed = paceToMetersPerSeconds(pace);
    double avgCarSpeed = calcCarAvgSpeed(distance, 180);

    cout << "To run " << distance << " m car speed is " << avgCarSpeed << " m/s";
    cout << " runner needs pace " << metersPerSecondToPace(avgCarSpeed) << " min/km" << endl;

    cout << "Runner with pace " << pace << " min/km (" << runnerSpeed << " m/s)";
    cout << " will run " << calcApproximateCarDistance(runnerSpeed) << " m" << endl;

    return 0;
}