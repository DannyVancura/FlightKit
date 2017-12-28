//
//  Engine.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include "Data.hpp"

class Data::Engine {
public:
    // MARK: - Moving parts
    double rpmEngine;
    double rpmProp;
    double propPitch;

    // MARK: - Physical state
    double torque;
    double thrust;
    double mixture;
    double fuelFlow;

    // MARK: - Temperatures & Pressure
    double manifoldPressure;
    double interstageTurbineTemperature;
    double exhaustGasTemperature;
    double cylinderHeadTemperature;
    double oilPressure;
    double oilTemperature;
};

#endif /* Engine_hpp */
