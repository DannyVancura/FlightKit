//
//  FKTConnection.m
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#import "FKTConnection.h"
#import "FlightSimConnection.hpp"
#import "FlightSimConnectionListener.hpp"
#import "XplaneConnection.hpp"
#import "XplaneListener.hpp"
#import "XplaneMessage.hpp"
#import "DataRecording.hpp"

@interface FKTConnection() {
    Connection::Xplane::XplaneConnection *xplaneConnection;
    Connection::Xplane::XplaneListener xplaneListener;
    DataRecording *recording;
}

@end

@implementation FKTConnection

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
        NSURL *docURL = [[NSFileManager defaultManager] URLForDirectory:NSDocumentDirectory
                                                               inDomain:NSUserDomainMask
                                                      appropriateForURL:nil
                                                                 create:true
                                                                  error:nil];
        docURL = [docURL URLByAppendingPathComponent:@"sql_data"];
        recording = new DataRecording((char *) [docURL.path UTF8String]);
        xplaneListener.connectionCallback = ^void (Connection::FlightSimConnection *instance) {
            recording->didEstablishConnection(instance);
        };
        xplaneListener.airplaneDataCallback = ^void (Data::Airplane airplane) {
            recording->didReceiveAirplaneData(airplane);
        };
        xplaneListener.otherAircraftDataCallback = ^void (std::vector<Data::Airplane> otherAircraft) {
            recording->didReceiveOtherAircraft(otherAircraft);
        };
        xplaneConnection->listener = &xplaneListener;
    }
    return self;
}

- (void)dealloc
{
    delete recording;
    delete xplaneConnection;
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
