//
//  FKTConnection.h
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FKTConnection : NSObject

@property (readwrite) BOOL isRecording;

/**
 Receives messages on the given port. It's not possible with this initializer to send messages before receiving the first message.
 Messages are sent to 49000 which is the default port of Xplane to receive messages on.

 Can be used if:

 - Xplane is set to receive messages on the default 49000 port.

 - Xplane is set to send messages to `inPort`.

 @param inPort Port of Xplane that is set to send UDP messages.
 @return Self.
 */
- (nonnull id) initReceivingOn:(NSInteger) inPort;

/**
 Receives messages from and receives messages on the given ports. It's not possible with this initializer to send messages before
 receiving the first message.

 Can be used if:

 - Xplane is set to receive messages on the `outPort` port.

 - Xplane is set to send messages to `inPort`.

 @param inPort Port of Xplane that is set to send UDP messages.
 @param outPort Port of Xplane that is set to receive UDP messages.
 @return Self.
 */
- (nonnull id) initReceivingOn:(NSInteger)inPort sendingTo: (NSInteger)outPort;

/**
 Receives messages from and receives messages on the given ports on the computer with the given IP.

 Can be used if:

 - Xplane is running on a computer with the given IP.

 - Xplane is set to receive messages on the `outPort` port.

 - Xplane is set to send messages to `inPort`.

 @param ip IP of the computer running Xplane.
 @param inPort Port of Xplane that is set to send UDP messages.
 @param outPort Port of Xplane that is set to receive UDP messages.
 @return Self.
 */
- (nonnull id) initWithIP:(nullable NSString *)ip receivingOn: (NSInteger)inPort sendingTo: (NSInteger)outPort;

- (bool) isConnected;

- (void) start;

- (void) stop;

@end
