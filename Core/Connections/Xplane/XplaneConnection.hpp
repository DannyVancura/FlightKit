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
#include <string>

#define BUFFER_SIZE 65536

class Connection::Xplane::XplaneConnection : public Connection::Instance {
private:
    int socketInfo;
    struct sockaddr_in ownAddress;
    struct sockaddr_in remoteAddress;
    socklen_t addrLen;
    bool isActive = false;
    bool activeConnectionAttempt = false;

    unsigned char buffer[BUFFER_SIZE];

    void receiveData();

public:
    int sendPort;
    int receivePort;
    Connection::Listener *listener;

    XplaneConnection(int receivePort = 49001, int sendPort = 49000);
    XplaneConnection(std::string ip, int receivePort = 49001, int sendPort = 49000);
    ~XplaneConnection();
    int establishConnection();
    void disconnect();
    ssize_t sendMessage(Data::Message &message);

    inline bool isServerConnectionEstablished() {
        return remoteAddress.sin_addr.s_addr != 0;
    }
};

#endif /* Xplane_hpp */
