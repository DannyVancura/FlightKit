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
#include "Engine.hpp"

class Data::Airplane {
public:
    // MARK: - Airplane info
    /// The airplane's callsign.
    char *callsign;
    char *name;

    // MARK: - Position Data
    double latitude;
    double longitude;
    double altitudeIndicatedAGL;
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
    std::array<Engine, 0> engines;

    // MARK: - Functions

    /**
     Returns the number of engines on this aircraft.

     @return Number of engines.
     */
    size_t numberOfEngines();
};

#endif /* Airplane_hpp */
