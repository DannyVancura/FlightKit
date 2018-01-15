//
//  SQLInsertAircraftStatement.h
//  FlightKit
//
//  Created by Daniel Vancura on 1/15/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef SQLInsertAircraftStatement_h
#define SQLInsertAircraftStatement_h

#include <stdio.h>
#include <chrono>
#include <string>

#define SQL_INSERT_AIRCRAFT_STATEMENT(aircraft) [=]()->string {\
    using namespace std::chrono;\
    long long ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();\
    char buffer[2048];\
    sprintf(buffer, "INSERT INTO RECORDING\
        (TIMESTAMP,\
        THROTTLE_SETTING,\
        MIXTURE_SETTING,\
        PROP_SETTING,\
        FLAP_SETTING,\
        ELEVATOR_SETTING,\
        AILERON_SETTING,\
        RUDDER_SETTING,\
        ELEVATOR_TRIM_SETTING,\
        AILERON_TRIM_SETTING,\
        RUDDER_TRIM_SETTING,\
        HEADING_COMPASS,\
        INDICATED_ALTITUDE,\
        INDICATED_AIRSPEED,\
        VERTICAL_VELOCITY,\
        LATITUDE,\
        LONGITUDE) VALUES (\
        %lli,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f,\
        %f\
        )",\
        ms,\
        aircraft.controls.commandedThrottle,\
        aircraft.controls.commandedMixture,\
        aircraft.controls.commandedProp,\
        aircraft.controls.commandedFlaps,\
        aircraft.controls.commandedPitch,\
        aircraft.controls.commandedRoll,\
        aircraft.controls.commandedYaw,\
        aircraft.controls.commandedPitchTrim,\
        aircraft.controls.commandedRollTrim,\
        aircraft.controls.commandedYawTrim,\
        aircraft.magneticHeading,\
        aircraft.altitudeIndicatedMSL,\
        aircraft.indicatedAirspeed,\
        aircraft.verticalVelocity,\
        aircraft.latitude,\
        aircraft.longitude\
        );\
    return string(buffer);\
}

#endif /* SQLInsertAircraftStatement_h */
