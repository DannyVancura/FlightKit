//
//  Buffer.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#define MAX_NUMBER_OF_AIRCRAFT 64

#define VALUE_NOT_SENT -999

#define VALUES_SPEEDS 3
#define VALUES_MACH_SPEEDS_VERTICAL_VELOCITY_GLOADS 4
#define VALUES_ATMOSPHERE_WEATHER 5
#define VALUES_ATMOSPHERE_AIRCRAFT 6
#define VALUES_SYSTEM_PRESSURES 7
#define VALUES_CONTROL_INPUTS 8
#define VALUES_PIT_ROLL_HEAD 17
#define VALUES_MAG_COMPASS 19
#define VALUES_LAT_LON_ALT 20
#define VALUES_LOC_VELOCITY_DISTANCE_TRAVELED 21

#include "Data.hpp"
#include "Airplane.hpp"

#include <stdio.h>
#include <map>
#include <vector>

class Data::Xplane::XplaneBuffer {
private:
    char *prefix;
    std::map<int, std::vector<float>> dataMap;

    std::vector<float> invalidOrValue(int index);
public:
    XplaneBuffer(unsigned char *data, long length);
    Airplane *airplane;
    Airplane *otherAircraft[MAX_NUMBER_OF_AIRCRAFT];

    void debug();
};

#endif /* Buffer_hpp */
