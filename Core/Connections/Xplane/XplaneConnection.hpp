//
//  Xplane.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#ifndef Xplane_hpp
#define Xplane_hpp

#include <stdio.h>
#include <netinet/in.h>
#include "Instance.hpp"
#include <thread>

#define BUFFER_SIZE 65536

class Connection::Xplane::XplaneConnection : public Connection::Instance {
private:
    int socketInfo;
    struct sockaddr_in ownAddress;
    struct sockaddr_in remoteAddress;
    socklen_t addrLen;
    bool isActive = false;

    unsigned char buffer[BUFFER_SIZE];

    void receiveData();

public:
    int receivePort = 49001;
    Connection::Listener *listener;

    XplaneConnection();
    XplaneConnection(int receivePort);
    ~XplaneConnection();
    int establishConnection();
    void disconnect();
    void sendData(unsigned char *data, size_t length);

    inline bool isServerConnectionEstablished() {
        return remoteAddress.sin_addr.s_addr != 0;
    }

    Connection::Xplane::XplaneConnection & operator= (const Connection::Xplane::XplaneConnection &other) {
        if (this != &other) {
            socketInfo = other.socketInfo;
            ownAddress = other.ownAddress;
            remoteAddress = other.remoteAddress;
            addrLen = other.addrLen;
            memcpy(&buffer, &other.buffer, BUFFER_SIZE);
            receivePort = other.receivePort;
        }
        return *this;
    }
};

#endif /* Xplane_hpp */
