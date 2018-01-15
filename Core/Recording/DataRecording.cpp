//
//  DataRecording.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/14/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#include "DataRecording.hpp"
#include "SQLPrepareStatement.h"
#include "SQLInsertAircraftStatement.h"

using namespace std;

DataRecording::DataRecording(char *fileName) {
    this->fileName = (char *) malloc(strlen(fileName));
    memcpy(this->fileName, fileName, strlen(fileName));
}

DataRecording::~DataRecording() {
    close();
    free(fileName);
}

void DataRecording::open() {
    if (handle) {
        return;
    }

    auto response = sqlite3_open(fileName, &handle);
    if (response) {
        perror("Failed to open SQLite database.\n");
        throw response;
    }
}

void DataRecording::close() {
    if (handle) {
        auto response = sqlite3_close(handle);
        if (response) {
            throw response;
        }

        handle = NULL;
    } else {
        return;
    }
}

void DataRecording::setupTables() {
    char *errMsg;
    auto result = sqlite3_exec(handle, SQL_PREPARE_STATEMENT, NULL, NULL, &errMsg);
    if (result) {
        perror(errMsg);
        throw result;
    }
}

void DataRecording::didEstablishConnection(Connection::FlightSimConnection *connection) {
    open();
    setupTables();
}

void DataRecording::didReceiveAirplaneData(Data::Airplane airplaneData) {
    auto statement = SQL_INSERT_AIRCRAFT_STATEMENT(airplaneData)();
    char *errMsg;
    auto result = sqlite3_exec(handle, statement.c_str(), NULL, NULL, &errMsg);
    if (result) {
        perror(errMsg);
        throw result;
    }
}

void DataRecording::didReceiveOtherAircraft(std::vector<Data::Airplane> otherAircraft) {

}
