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
#include "Listener.hpp"
#include <functional>
#include <vector>

class Connection::Xplane::XplaneListener: public Connection::Listener {
public:
    std::function<void(Connection::Instance *instance)> connectionCallback = {};
    std::function<void(Data::Airplane airplaneData)> airplaneDataCallback = {};
    std::function<void(std::vector<Data::Airplane> otherAircraft)> otherAircraftDataCallback = {};

    void didEstablishConnection(Connection::Instance *connection);
    void didReceiveAirplaneData(Data::Airplane airplaneData);
    void didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft);
};

#endif /* XplaneListener_hpp */
