//
//  XplaneListener.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/28/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneListener.hpp"

void Connection::Xplane::XplaneListener::didEstablishConnection(Connection::Instance *connection) {
    connectionCallback(connection);
}

void Connection::Xplane::XplaneListener::didReceiveAirplaneData(Data::Airplane airplaneData) {
    airplaneDataCallback(airplaneData);
}

void Connection::Xplane::XplaneListener::didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft) {
    otherAircraftDataCallback(otherAircraft);
}
