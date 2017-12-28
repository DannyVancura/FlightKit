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

#include <stdio.h>
#include "Data.hpp"
#include "Airplane.hpp"

class Data::Xplane::Buffer {
public:
    Buffer(unsigned char *data);
    Airplane airplane;
    Airplane otherAircraft[MAX_NUMBER_OF_AIRCRAFT];

};

#endif /* Buffer_hpp */
