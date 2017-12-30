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

#include "Data.hpp"
#include "Airplane.hpp"

#include <stdio.h>
#include <map>
#include <vector>

class Data::Xplane::XplaneBuffer {
private:
    char *prefix;
    std::map<int, std::vector<float>> dataMap;
public:
    XplaneBuffer(unsigned char *data, long length);
    Airplane *airplane;
    Airplane *otherAircraft[MAX_NUMBER_OF_AIRCRAFT];

    void debug();
};

#endif /* Buffer_hpp */
