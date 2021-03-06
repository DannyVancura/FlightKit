//
//  Airplane.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Airplane_hpp
#define Airplane_hpp

#include <stdio.h>
#include <array>
#include <vector>
#include "Engine.hpp"
#include "AirplaneControls.hpp"

class Data::Airplane {
public:
    // MARK: - Airplane info
    /// The airplane's callsign.
    char *callsign;
    char *name;

    // MARK: - Position Data
    double latitude;
    double longitude;
    double altitudeIndicatedMSL;
    double altitudeTrueAGL;
    double altitudeTrueMSL;

    // MARK: - Trajectory Data
    double indicatedAirspeed;
    double trueAirspeed;
    double trueGroundspeed;
    double magneticHeading;
    double trueHeading;
    double verticalVelocity;
    double pitch;
    double roll;
    double headingTrue;
    double headingMag;

    // MARK: - Engines
    std::vector<Engine> engines;

    // MARK: - Control input
    AirplaneControls controls;
};

#endif /* Airplane_hpp */
