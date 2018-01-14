//
//  FlightSimConnectionListener.h
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef FlightSimConnectionListener_h
#define FlightSimConnectionListener_h

#include <stdio.h>
#include "Airplane.hpp"
#include "FlightSimConnection.hpp"

class Connection::FlightSimConnectionListener {
public:
    FlightSimConnectionListener(){}
    virtual void didEstablishConnection(Connection::FlightSimConnection *connection)=0;
    virtual void didReceiveAirplaneData(Data::Airplane airplaneData)=0;
    virtual void didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft)=0;
};

#endif /* FlightSimConnectionListener_h */
