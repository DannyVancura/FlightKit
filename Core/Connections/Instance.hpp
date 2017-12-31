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
#include "Message.hpp"

class Connection::Instance {
public:
    Connection::Listener *listener;

    Instance(){}
    virtual int establishConnection() = 0;
    virtual void disconnect() = 0;
    virtual ssize_t sendMessage(Data::Message &message) = 0;

    bool isServerConnectionEstablished();
};

#endif
