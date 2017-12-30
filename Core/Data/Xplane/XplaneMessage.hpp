//
//  XplaneMessage.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/30/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef XplaneMessage_hpp
#define XplaneMessage_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Data.hpp"
#include "Message.hpp"

class Data::Xplane::XplaneMessage: public Data::Message {
public:
    static XplaneMessage mouseClick(int x, int y);
    static XplaneMessage keyPress(char key);
    static XplaneMessage menu(int menu);
    static XplaneMessage sound(float frequency, char *wavPath);
    static XplaneMessage setData(float value, char *dataRef);
    static XplaneMessage fail(int system);
    static XplaneMessage recover(int system);
    static XplaneMessage placeAtAirport(char *airport, int startType, int location, int backwards);
    static XplaneMessage loadAircraft(int plane, char planePath[50], char weapons[24][50]);
    XplaneMessage();
    ~XplaneMessage();
};

#endif /* XplaneMessage_hpp */
