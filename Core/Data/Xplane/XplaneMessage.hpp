//
//  XplaneMessage.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/30/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef XplaneMessage_hpp
#define XplaneMessage_hpp

#define XP_STR_DIM 500

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Data.hpp"
#include "Message.hpp"

typedef enum : int {
    takeoff = 601,
    shortFinal = 602,
    longFinal = 603
} StartType;

class Data::Xplane::XplaneMessage: public Data::Message {
public:
    static XplaneMessage mouseClick(int x, int y);
    static XplaneMessage keyPress(char key);
    static XplaneMessage menu(int menu);
    static XplaneMessage sound(float frequency, float volume, char wavPath[XP_STR_DIM]);
    static XplaneMessage setData(float value, char dataRef[XP_STR_DIM]);
    static XplaneMessage fail(int system);
    static XplaneMessage recover(int system);
    static XplaneMessage placeAtAirport(char airport[4], StartType startType, int location, int backwards);
    static XplaneMessage loadAircraft(int plane, char planePath[150], char weapons[24][50]);
    XplaneMessage();
    ~XplaneMessage();
};

#endif /* XplaneMessage_hpp */
