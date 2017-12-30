//
//  XplaneMessage.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/30/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneMessage.hpp"

using namespace Data::Xplane;

XplaneMessage::XplaneMessage() {

}

XplaneMessage XplaneMessage::keyPress(char key) {
    XplaneMessage message = XplaneMessage();
    message.data = (char *) malloc(6);
    message.length = 6;
    char prefix[] = "CHAR0";
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, &key, 1);

    return message;
}

XplaneMessage XplaneMessage::menu(int menu) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "MENU0";
    std::string numString = std::to_string(menu);
    const char *cstring = numString.c_str();

    message.data = (char *) malloc(5 + numString.size());
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, cstring, numString.size());
    message.length = 5 + numString.size();

    return message;
}

XplaneMessage XplaneMessage::sound(float frequency, char *wavPath) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage XplaneMessage::setData(float value, char *dataRef) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage XplaneMessage::fail(int system) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage XplaneMessage::recover(int system) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage XplaneMessage::placeAtAirport(char *airport, int startType, int location, int backwards) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage XplaneMessage::loadAircraft(int plane, char planePath[50], char weapons[24][50]) {
    XplaneMessage message = XplaneMessage();
    return message;
}

XplaneMessage::~XplaneMessage() {
    free(data);
}
