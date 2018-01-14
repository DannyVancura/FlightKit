//
//  XplaneListener.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/28/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef XplaneListener_hpp
#define XplaneListener_hpp

#include <stdio.h>
#include "Connection.hpp"
#include "FlightSimConnectionListener.hpp"
#include <functional>
#include <vector>

class Connection::Xplane::XplaneListener: public Connection::FlightSimConnectionListener {
public:
    std::function<void(Connection::FlightSimConnection *connection)> connectionCallback = {};
    std::function<void(Data::Airplane airplaneData)> airplaneDataCallback = {};
    std::function<void(std::vector<Data::Airplane> otherAircraft)> otherAircraftDataCallback = {};

    void didEstablishConnection(Connection::FlightSimConnection *connection);
    void didReceiveAirplaneData(Data::Airplane airplaneData);
    void didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft);
};

#endif /* XplaneListener_hpp */
