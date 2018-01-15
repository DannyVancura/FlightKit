//
//  AirplaneControls.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/14/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef AirplaneControls_hpp
#define AirplaneControls_hpp

#include <stdio.h>
#include "Data.hpp"

class Data::AirplaneControls {
public:
    // MARK: - Engine settings
    double commandedThrottle;
    double commandedMixture;
    double commandedProp;

    // MARK: - Control surfaces
    double commandedPitch;
    double commandedRoll;
    double commandedYaw;
    double commandedPitchTrim;
    double commandedRollTrim;
    double commandedYawTrim;
    double commandedFlaps;
};

#endif /* AirplaneControls_hpp */
