#  FlightKit

## Purpose

Open Source SDK for iOS, macOS, watchOS and tvOS to communicate with [X-Plane](http://www.x-plane.com) flight simulator via UDP interface. The SDK is written primarily
in C++11 to be kept mostly platform independent.

## Components

- `FKTConnection` - Objective-C wrapper to establish a connection to Xplane from any Apple OS platform.
- `XplaneConnection` - Main C++ component for establishing a network connection to Xplane.
- `DataRecording` - Stream listener for capturing flight data in a Sqlite database.

## Usage

X-Plane offers a simple UDP data stream interface. A reference of the data format can be found [here](http://www.nuclearprojects.com/xplane/xplaneref.html). To start sending
and receiving data in X-Plane, go to `Settings` --> `DataOutput` and check `Send network data output`. Enter an IP to send data to (the computer listening to the data
stream) as well as the port to send to. To start reading data as it comes in, open a `FKTConnection` via `- (nonnull id) initReceivingOn:(NSInteger) inPort`.

To be able to send data to X-Plane you will further have to make sure that the `Port we receive on` in `Settings` --> `Network` is set to `49000` or make sure that you call
`- (nonnull id) initReceivingOn:(NSInteger)inPort sendingTo: (NSInteger)outPort` with `outPort` set to the port next to `Port we receive on`.

To let *FlightKit* actively request aircraft data from X-Plane (recommended), you can use
`- (nonnull id) initWithIP:(nullable NSString *)ip receivingOn: (NSInteger)inPort sendingTo: (NSInteger)outPort`. The IP you enter will be the IP
of the computer running X-Plane, `inPort` the port set in `Data Output` and `outPort` the `Port we receive on` in `Network`.

Once *FlightKit* has connected to X-Plane, it will trigger a sound snippet in the flight simulator to indicate the connection.

## License

[MIT License](LICENSE.md)
