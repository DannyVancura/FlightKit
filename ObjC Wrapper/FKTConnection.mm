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

@implementation FKTConnection

Connection::Xplane::XplaneConnection *xplaneConnection;
Connection::Xplane::XplaneListener xplaneListener;

- (nonnull id) init {
    self = [self init: [@49001 integerValue]];

    return self;
}

- (nonnull id) init:(NSInteger) port {
    self = [super init];
    if (self) {
        xplaneConnection = new Connection::Xplane::XplaneConnection((int) port);
        xplaneListener = Connection::Xplane::XplaneListener();
        xplaneListener.connectionCallback = ^void (Connection::Instance *instance) {

        };
        xplaneListener.airplaneDataCallback = ^void (Data::Airplane *airplane) {

        };
        xplaneListener.otherAircraftDataCallback = ^void (Data::Airplane *aircraft[]) {
            
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
