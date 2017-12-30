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

    private let connection = FKTConnection(49123)

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        connection.start()
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        connection.stop()
    }


}

