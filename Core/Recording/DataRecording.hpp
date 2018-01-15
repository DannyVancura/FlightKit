//
//  DataRecording.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/14/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef DataRecording_hpp
#define DataRecording_hpp

#include <stdio.h>
#include <sqlite3.h>
#include "FlightSimConnectionListener.hpp"

class DataRecording: public Connection::FlightSimConnectionListener {
    sqlite3 *handle;

public:
    char *fileName;

    DataRecording(char *fileName);
    ~DataRecording();

    void open();
    void close();

    void setupTables();

    void didEstablishConnection(Connection::FlightSimConnection *connection);
    void didReceiveAirplaneData(Data::Airplane airplaneData);
    void didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft);
};

#endif /* DataRecording_hpp */
