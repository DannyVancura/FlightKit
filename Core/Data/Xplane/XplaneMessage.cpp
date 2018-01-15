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
    memcpy(message.data + 6, &key, 1);

    return message;
}

XplaneMessage XplaneMessage::menu(int menu) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "MENU0";
    std::string numString = std::to_string(menu);
    const char *cstring = numString.c_str();

    message.length = 5 + numString.length() + 1;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, cstring, numString.length());
    memset(message.data + message.length - 1, 0, 1);

    return message;
}

XplaneMessage XplaneMessage::sound(float frequency, float volume, char wavPath[XP_STR_DIM]) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "SOUN0";
    message.length = 5 + 2 * sizeof(float) + XP_STR_DIM;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, &frequency, sizeof(float));
    memcpy(message.data + 5 + sizeof(float), &volume, sizeof(float));
    memcpy(message.data + 5 + 2 * sizeof(float), wavPath, XP_STR_DIM);

    return message;
}

XplaneMessage XplaneMessage::setData(float value, char dataRef[XP_STR_DIM]) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "DREF0";
    message.length = 5 + sizeof(float) + XP_STR_DIM;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, &value, sizeof(float));
    memcpy(message.data + 5 + sizeof(float), dataRef, XP_STR_DIM);

    return message;
}

XplaneMessage XplaneMessage::fail(int system) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "FAIL0";
    std::string str = std::to_string(system);
    const char *cstring = str.c_str();
    message.length = 5 + str.length() + 1;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, cstring, str.length());
    memset(message.data + message.length - 1, 0, 1);

    return message;
}

XplaneMessage XplaneMessage::recover(int system) {
    XplaneMessage message = XplaneMessage();
    char prefix[] = "RECO0";
    std::string str = std::to_string(system);
    const char *cstring = str.c_str();
    message.length = 5 + str.length() + 1;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, prefix, 5);
    memcpy(message.data + 5, cstring, str.length());
    memset(message.data + message.length - 1, 0, 1);

    return message;
}

XplaneMessage XplaneMessage::placeAtAirport(char airport[4], StartType startType, int location, int backwards) {
    XplaneMessage message = XplaneMessage();
    message.length = 10 + 3 * sizeof(int);
    message.data = (char *) malloc(message.length);
    memcpy(message.data, "PAPT0", 5);
    memcpy(message.data + 5, airport, 4);
    memset(message.data + 9, 0, 1);
    memcpy(message.data + 10, &startType, sizeof(int));
    memcpy(message.data + 10 + sizeof(int), &location, sizeof(int));
    memcpy(message.data + 10 + 2 * sizeof(int), &backwards, sizeof(int));

    return message;
}

XplaneMessage XplaneMessage::loadAircraft(int plane, char planePath[150], char weapons[24][50]) {
    XplaneMessage message = XplaneMessage();
    message.length = sizeof(int) + 150 + 24 * 50;
    message.data = (char *) malloc(message.length);
    memcpy(message.data, "VEHN", 4);
    char delim = 17;
    memcpy(message.data + 4, &delim, 1);
    memcpy(message.data + 5, planePath, 150);
    memcpy(message.data + 155, weapons, 24*50);

    return message;
}

XplaneMessage XplaneMessage::selectData(std::vector<int> indices) {
    XplaneMessage message = XplaneMessage();
    message.length = 5 + indices.size() * sizeof(int);
    message.data = (char *) malloc(message.length);
    memcpy(message.data, "DSEL", 4);
    for (int i = 0; i < indices.size(); i++) {
        memcpy(message.data + 5 + i * sizeof(int), &indices.at(i), sizeof(int));
    }

    return message;
}

XplaneMessage::~XplaneMessage() {
    free(data);
}
