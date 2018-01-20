//
//  OpenCLProgram.cpp
//  FlightKit (macOS)
//
//  Created by Daniel Vancura on 1/19/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#include "OpenCLProgram.hpp"
#include <fstream>
#include <streambuf>

ML::OpenCLProgram::OpenCLProgram(const char *sourceCode):
sourceCode(sourceCode){
}

ML::OpenCLProgram::~OpenCLProgram() {
    clReleaseProgram(program);
    for (cl_kernel kernel : kernels) {
        clReleaseKernel(kernel);
    }
}

const char *ML::OpenCLProgram::getSource() {
    return sourceCode.c_str();
}
