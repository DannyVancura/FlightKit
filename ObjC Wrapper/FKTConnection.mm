//
//  FKTConnection.m
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#import "FKTConnection.h"
#import "Instance.hpp"
#import "Listener.hpp"
#import "XplaneConnection.hpp"
#import "XplaneListener.hpp"
#import "XplaneMessage.hpp"

@implementation FKTConnection

Connection::Xplane::XplaneConnection *xplaneConnection;
Connection::Xplane::XplaneListener xplaneListener;

- (nonnull id) init {
    self = [self initWithIP: nil receivingOn:49001 sendingTo:49000];

    return self;
}

- (nonnull id) initReceivingOn:(NSInteger) inPort {
    self = [self initWithIP:nil receivingOn:inPort sendingTo:49000];

    return self;
}

- (nonnull id) initReceivingOn:(NSInteger) inPort sendingTo:(NSInteger) outPort {
    self = [self initWithIP:nil receivingOn:inPort sendingTo:outPort];

    return self;
}

- (nonnull id) initWithIP:(nullable NSString *)ip receivingOn:(NSInteger) inPort sendingTo:(NSInteger) outPort {
    self = [super init];
    if (self) {
        if (ip) {
            xplaneConnection = new Connection::Xplane::XplaneConnection(ip.UTF8String, (int) inPort, (int) outPort);
        } else {
            xplaneConnection = new Connection::Xplane::XplaneConnection((int) inPort, (int) outPort);
        }
        xplaneListener = Connection::Xplane::XplaneListener();
        xplaneListener.connectionCallback = ^void (Connection::Instance *instance) {

        };
        xplaneListener.airplaneDataCallback = ^void (Data::Airplane airplane) {

        };
        xplaneListener.otherAircraftDataCallback = ^void (std::vector<Data::Airplane> otherAircraft) {
            
        };
        xplaneConnection->listener = &xplaneListener;
    }
    return self;
}

- (bool) isConnected {
    return xplaneConnection->isServerConnectionEstablished();
}

- (void) start {
    xplaneConnection->establishConnection();
}

- (void) stop {
    xplaneConnection->disconnect();
}

@end
