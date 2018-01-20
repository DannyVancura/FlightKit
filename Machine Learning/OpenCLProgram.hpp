//
//  OpenCLProgram.hpp
//  FlightKit (macOS)
//
//  Created by Daniel Vancura on 1/19/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef OpenCLProgram_hpp
#define OpenCLProgram_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include "ML.hpp"
#include <OpenCL/opencl.h>

class ML::OpenCLProgram {
friend class OpenCLContext;
private:
    std::string sourceCode;
    cl_program program;
    std::set<cl_kernel> kernels;
public:
    OpenCLProgram(const char *sourceCode);
    ~OpenCLProgram();

    const char *getSource();
};

#endif /* OpenCLProgram_hpp */
