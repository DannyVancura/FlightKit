//
//  AppDelegate.swift
//  Demo
//
//  Created by Daniel Vancura on 12/29/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

import Cocoa
import FlightKit

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    private let connection = FKTConnection(ip: "127.0.0.1", receivingOn: 49123, sendingTo: 49000)

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        connection.start()
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        connection.stop()
    }


}

