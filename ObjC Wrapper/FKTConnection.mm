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

Connection::Xplane::XplaneConnection xplaneConnection;
Connection::Xplane::XplaneListener xplaneListener;

- (instancetype)init
{
    self = [super init];
    if (self) {
        xplaneConnection = Connection::Xplane::XplaneConnection(49000);
        xplaneListener = Connection::Xplane::XplaneListener();
        xplaneListener.connectionCallback = ^void (Connection::Instance *instance) {
            NSLog(@"Did connect.");
        };
        xplaneListener.airplaneDataCallback = ^void (Data::Airplane airplane) {
            NSLog(@"Did receive airplane.");
        };
        xplaneListener.otherAircraftDataCallback = ^void (Data::Airplane aircraft[]) {
            NSLog(@"Did receive other aircraft");
        };
        xplaneConnection.listener = &xplaneListener;
    }
    return self;
}

- (void) start {
    xplaneConnection.establishConnection();
}

- (void) stop {
    xplaneConnection.disconnect();
}

@end
