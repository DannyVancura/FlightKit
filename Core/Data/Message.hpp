//
//  Message.h
//  FlightKit
//
//  Created by Daniel Vancura on 12/30/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Message_h
#define Message_h

#import "Data.hpp"

class Data::Message {
public:
    char *data;
    size_t length;
};

#endif /* Message_h */
