//
//  FKTConnection.h
//  FlightKit
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FKTConnection : NSObject

- (nonnull id) init:(NSInteger) port;

- (bool) isConnected;

- (void) start;

- (void) stop;

@end
