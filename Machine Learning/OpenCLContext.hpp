//
//  OpenCLContext.hpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/18/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#ifndef OpenCLContext_hpp
#define OpenCLContext_hpp

#include "ML.hpp"
#include "OpenCLProgram.hpp"
#include <stdio.h>
#include <OpenCL/opencl.h>

class ML::OpenCLContext {
    cl_device_id gpu;
    cl_command_queue commandQueue;
    cl_context context;
public:
    dispatch_queue_t queue;

    OpenCLContext();
    ~OpenCLContext();

    cl_kernel compile(OpenCLProgram *program, const char *kernelName);
    cl_mem addBuffer(cl_kernel kernel, cl_mem_flags readWriteAccess, size_t size);
    void write(cl_mem buffer, void *data, size_t size);
    void read(cl_mem buffer, void *output, size_t size);
    size_t maximumWorkgroupSize(cl_kernel kernel);
    void enqueueRun(cl_kernel kernel, size_t globalSize, size_t localSize);
    void finish();
};

#endif /* OpenCLContext_hpp */
