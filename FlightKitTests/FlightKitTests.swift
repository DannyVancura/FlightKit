//
//  FlightKitTests.swift
//  FlightKitTests
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

import XCTest
@testable import FlightKit

class FlightKitTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testRunning() {
        let mockServer = FKTConnection(ip: "127.0.0.1", receivingOn: 49001, sendingTo: 49123)
        let connection = FKTConnection(receivingOn: 49123, sendingTo: 49000)

        XCTAssertFalse(connection.isConnected())
        connection.start()

        let expect = expectation(description: "Waiting")

        DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
            mockServer.start()
        }

        DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
            XCTAssertTrue(connection.isConnected())
            connection.stop()
            mockServer.stop()
            expect.fulfill()
        }

        wait(for: [expect], timeout: 4)
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
    
}
