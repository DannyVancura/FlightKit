//
//  FlightKit__macOS_Tests.swift
//  FlightKit (macOS)Tests
//
//  Created by Daniel Vancura on 12/27/17.
//  Copyright © 2017 Daniel Vancura. All rights reserved.
//

import XCTest
@testable import FlightKit

class FlightKit__macOS_Tests: XCTestCase {
    
    func testSigmoidKernel() {
        let network = FKTNeuralNetwork()
        XCTAssertTrue(network.testSigmoidFunction())
    }
    
}
