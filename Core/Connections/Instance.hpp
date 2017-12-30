//
//  FlightSimConnection.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef FlightSimConnection_hpp
#define FlightSimConnection_hpp

#include <stdio.h>
#include "Connection.hpp"

class Connection::Instance {
public:
    Connection::Listener *listener;

    Instance(){}
    virtual int establishConnection() = 0;
    virtual void disconnect() = 0;
    virtual void sendData(unsigned char *data, size_t length) = 0;

    bool isServerConnectionEstablished();
};

#endif
