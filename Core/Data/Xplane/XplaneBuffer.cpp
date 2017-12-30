//
//  XplaneBuffer.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneBuffer.hpp"

std::vector<float> Data::Xplane::XplaneBuffer::invalidOrValue(int index) {
    if (dataMap.find(index) != dataMap.end()) {
        return dataMap.at(index);
    } else {
        return std::vector<float>(8, VALUE_NOT_SENT);
    }
}

Data::Xplane::XplaneBuffer::XplaneBuffer(unsigned char *data, long length) {
    if (length >= 5) {
        prefix = (char *) malloc(5);
        memcpy(prefix, data, 5);
    }
    for (int i = 5; i < length; i += (sizeof(int) + 8 * sizeof(float))) {
        int index = 0;
        float values[8];

        memcpy(&index, data + i, sizeof(int));
        memcpy(values, data + i + sizeof(int), 8 * sizeof(float));
        std::vector<float> vector(8);
        for (int j = 0; j < 8; j++) {
            vector[j] = values[j];
        }
        dataMap.insert(std::pair<int, std::vector<float>>(index, vector));
    }
    airplane = new Airplane();
    airplane->indicatedAirspeed = invalidOrValue(VALUES_SPEEDS)[0];
    airplane->trueAirspeed = invalidOrValue(VALUES_SPEEDS)[2];
    airplane->trueGroundspeed = invalidOrValue(VALUES_SPEEDS)[3];
    airplane->latitude = invalidOrValue(VALUES_LAT_LON_ALT)[0];
    airplane->longitude = invalidOrValue(VALUES_LAT_LON_ALT)[1];
    airplane->altitudeTrueMSL = invalidOrValue(VALUES_LAT_LON_ALT)[2];
    airplane->altitudeTrueAGL = invalidOrValue(VALUES_LAT_LON_ALT)[3];
    airplane->altitudeIndicatedMSL = invalidOrValue(VALUES_LAT_LON_ALT)[5];
    airplane->headingTrue = invalidOrValue(VALUES_PIT_ROLL_HEAD)[2];
    airplane->headingMag = invalidOrValue(VALUES_PIT_ROLL_HEAD)[3];
    airplane->verticalVelocity = invalidOrValue(VALUES_MACH_SPEEDS_VERTICAL_VELOCITY_GLOADS)[2];
    airplane->pitch = invalidOrValue(VALUES_PIT_ROLL_HEAD)[0];
    airplane->roll = invalidOrValue(VALUES_PIT_ROLL_HEAD)[1];
}

void Data::Xplane::XplaneBuffer::debug() {
    printf("Prefix: %s\n", prefix);
    printf("Airplane heading: %f\n", airplane->headingTrue);
    printf("Airplane altitude: %f\n", airplane->altitudeTrueMSL);
    printf(" _______\n");
}
