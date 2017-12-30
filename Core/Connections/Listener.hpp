//
//  Listener.h
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Listener_h
#define Listener_h

#include <stdio.h>
#include "Airplane.hpp"
#include "Instance.hpp"

class Connection::Listener {
public:
    Listener(){}
    virtual void didEstablishConnection(Connection::Instance *connection)=0;
    virtual void didReceiveAirplaneData(Data::Airplane airplaneData)=0;
    virtual void didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft)=0;
};

#endif /* Listener_h */
