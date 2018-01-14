//
//  Xplane.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#include "XplaneConnection.hpp"
#include "FlightSimConnectionListener.hpp"
#include "XplaneBuffer.hpp"
#include "XplaneMessage.hpp"

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

Connection::Xplane::XplaneConnection::XplaneConnection(int receivePort, int sendPort):
receivePort(receivePort),
sendPort(sendPort) {}

Connection::Xplane::XplaneConnection::XplaneConnection(std::string ip, int receivePort, int sendPort):
receivePort(receivePort),
sendPort(sendPort) {
    const char *cstring = ip.c_str();
    memset((char *) &remoteAddress, 0, sizeof(remoteAddress));
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_addr.s_addr = inet_addr(cstring);
    remoteAddress.sin_port = htons(sendPort);

    activeConnectionAttempt = true;
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
    ownAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    ownAddress.sin_port = htons(receivePort);

    addrLen = sizeof(remoteAddress);

    int bindResult = bind(socketInfo, (struct sockaddr *) &ownAddress, sizeof(ownAddress));
    if (bindResult < 0) {
        perror("Failed to bind to socket.");
        return bindResult;
    }

    if (activeConnectionAttempt) {
        Data::Xplane::XplaneMessage message = Data::Xplane::XplaneMessage::fail(0);
        ssize_t bytesSent = sendMessage(message);

        if (bytesSent < 0) {
            perror("Failed to send first message");
            return (int) bytesSent;
        } else {
            if (listener) {
                listener->didEstablishConnection(this);
            }
        }
    }
    isActive = true;
    std::thread receiveThread(&Connection::Xplane::XplaneConnection::receiveData, this);

    receiveThread.detach();

    if (listener && !activeConnectionAttempt) {
        listener->didEstablishConnection(this);
    }

    return socketInfo;
}

void Connection::Xplane::XplaneConnection::receiveData() {
    static bool once = true;
    while (isActive) {
        ssize_t bytesReceived;
        if (activeConnectionAttempt) {
            bytesReceived = recv(socketInfo, buffer, BUFFER_SIZE, 0);
        } else {
            bytesReceived = recvfrom(socketInfo, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &remoteAddress, &addrLen);
        }
        if (bytesReceived > 0) {
            buffer[bytesReceived] = 0;
            Data::Xplane::XplaneBuffer rawData = Data::Xplane::XplaneBuffer(buffer, bytesReceived);
            listener->didReceiveAirplaneData(rawData.airplane);
            listener->didReceiveOtherAircraft(rawData.otherAircraft);
            rawData.debug();
            if (once) {
                once = false;
                // Play a beeping sound indicating that we are connected.
                Data::Xplane::XplaneMessage message = Data::Xplane::XplaneMessage::sound(1, 1, (char *) "Resources/sounds/alert/transonic.wav");
                sendMessage(message);
            }
        } else {
            perror("Failed to receive.");
        }
    }
}

void Connection::Xplane::XplaneConnection::disconnect() {
    isActive = false;
    close(socketInfo);
}

ssize_t Connection::Xplane::XplaneConnection::sendMessage(Data::Message &message) {
    remoteAddress.sin_port = htons(sendPort);
    ssize_t bytesSent = sendto(socketInfo, message.data, message.length, 0, (struct sockaddr *) &remoteAddress, sizeof(remoteAddress));

    if (bytesSent < 0) {
        perror("Failed sending");
    }
    return bytesSent;
}
