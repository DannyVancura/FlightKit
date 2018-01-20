//
//  OpenCLContext.cpp
//  FlightKit
//
//  Created by Daniel Vancura on 1/18/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#include "OpenCLContext.hpp"

#include <iostream>

ML::OpenCLContext::OpenCLContext() {
    queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, NULL);
    if (queue == NULL) {
        queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_CPU, NULL);
    }

    gpu = gcl_get_device_id_with_dispatch_queue(queue);

    cl_int err;
    context = clCreateContext(0, 1, &gpu, NULL, NULL, &err);
    if (err) {
        throw err;
    }

    commandQueue = clCreateCommandQueue(context, gpu, 0, &err);
    if (err) {
        throw err;
    }

#if DEBUG
    char name[128];
    clGetDeviceInfo(gpu, CL_DEVICE_NAME, 128, name, NULL);
    printf("Created dispatch queue with device %s.", name);
#endif
}

ML::OpenCLContext::~OpenCLContext() {
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);
    dispatch_release(queue);
    clReleaseDevice(gpu);
}

cl_kernel ML::OpenCLContext::compile(ML::OpenCLProgram *program, const char *kernelName) {
    const char *sourceCode = program->getSource();
    cl_int err;
    cl_program createdProgram = clCreateProgramWithSource(context, 1, &sourceCode, NULL, &err);
    if (err) {
        throw err;
    }

    err = clBuildProgram(createdProgram, 0, NULL, NULL, NULL, NULL);

    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];

        perror("Error: Failed to build program executable!\n");
        clGetProgramBuildInfo(createdProgram, gpu, CL_PROGRAM_BUILD_LOG, sizeof(buffer), (char *) buffer, &len);
        printf("%s\n", buffer);
        throw err;
    }

    cl_kernel kernel = clCreateKernel(createdProgram, kernelName, &err);
    if (err != CL_SUCCESS) {
        throw err;
    }

    program->program = createdProgram;
    program->kernels.insert(kernel);

    return kernel;
}

cl_mem ML::OpenCLContext::addBuffer(cl_kernel kernel, cl_mem_flags readWriteAccess, size_t size) {
    return clCreateBuffer(context, readWriteAccess, size, NULL, NULL);
}

void ML::OpenCLContext::write(cl_mem buffer, void *data, size_t size) {
    int err = clEnqueueWriteBuffer(commandQueue, buffer, CL_TRUE, 0, size, data, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        throw err;
    }
}

void ML::OpenCLContext::read(cl_mem buffer, void *output, size_t size) {
    int err = clEnqueueReadBuffer(commandQueue, buffer, CL_TRUE, 0, size, output, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        throw err;
    }
}

size_t ML::OpenCLContext::maximumWorkgroupSize(cl_kernel kernel) {
    size_t result;
    int err = clGetKernelWorkGroupInfo(kernel, gpu, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &result, NULL);
    if (err != CL_SUCCESS) {
        throw err;
    }
    return result;
}

void ML::OpenCLContext::enqueueRun(cl_kernel kernel, size_t globalSize, size_t localSize) {
    const size_t global = globalSize, local = std::min(localSize, globalSize);
    int err = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        throw err;
    }
}

void ML::OpenCLContext::finish() {
    clFinish(commandQueue);
}
