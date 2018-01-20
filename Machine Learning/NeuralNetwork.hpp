//
//  NeuralNetwork.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/15/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef CNN_hpp
#define CNN_hpp

#include "ML.hpp"
#include <stdio.h>
#include <OpenCL/opencl.h>

class ML::NeuralNetwork {
    int m;
    int n;

    NeuralNetwork(int m, int n);
};

#endif /* CNN_hpp */
