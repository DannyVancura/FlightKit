//
//  Xplane.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneConnection.hpp"
#include "Listener.hpp"
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string>

Connection::Xplane::XplaneConnection::XplaneConnection() {

}

Connection::Xplane::XplaneConnection::XplaneConnection(int receivePort) {
    this->receivePort = receivePort;
}

Connection::Xplane::XplaneConnection::~XplaneConnection() {
    disconnect();
}

int Connection::Xplane::XplaneConnection::establishConnection() {
    socketInfo = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int optVal = 1;
    int optionResult = setsockopt(socketInfo, SOL_SOCKET, SO_REUSEADDR, &optVal ,sizeof(int));
    if (optionResult < 0) {
        perror("Failed to set options.");
        return optionResult;
    }

    if (socketInfo < 0) {
        perror("Failed to create socket.");
        return socketInfo;
    }

    memset((char *) &ownAddress, 0, sizeof(ownAddress));
    ownAddress.sin_family = AF_INET;
    ownAddress.sin_addr.s_addr = INADDR_ANY;
    ownAddress.sin_port = htons(receivePort);

    addrLen = sizeof(remoteAddress);

    int bindResult = bind(socketInfo, (struct sockaddr *) &ownAddress, sizeof(ownAddress));
    if (bindResult < 0) {
        perror("Failed to bind to socket.");
        return bindResult;
    }
    isActive = true;
    std::thread receiveThread(&Connection::Xplane::XplaneConnection::receiveData, this);

    receiveThread.detach();

    if (listener) {
        listener->didEstablishConnection(this);
    }

    return socketInfo;
}

void Connection::Xplane::XplaneConnection::receiveData() {
    while (isActive) {
        ssize_t bytesReceived = recvfrom(socketInfo, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &remoteAddress, &addrLen);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = 0;
        } else {
            perror("Failed to receive.");
        }
    }
}

void Connection::Xplane::XplaneConnection::disconnect() {
    isActive = false;
    close(socketInfo);
}
