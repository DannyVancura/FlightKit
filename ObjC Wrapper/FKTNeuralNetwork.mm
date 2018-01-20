//
//  FKTNeuralNetwork.m
//  FlightKit
//
//  Created by Daniel Vancura on 1/18/18.
//  Copyright © 2018 Daniel Vancura. All rights reserved.
//

#import "FKTNeuralNetwork.h"
#import "NeuralNetwork.hpp"
#import "OpenCLContext.hpp"
#import "OpenCLProgram.hpp"
#import "Sigmoid.cl.h"

@implementation FKTNeuralNetwork

const char *sigmoidCode = "\
kernel void sigmoid(global float *input, global float *output) {\
    size_t index = get_global_id(0);\
    output[index] = input[index] * input[index];\
}\
";

- (BOOL) testSigmoidFunction {
    ML::OpenCLContext *context = new ML::OpenCLContext();

    float values[5] = {0.3, 0.5, 0.2, 0.1, 0.5};
    float *results = (float *) malloc(5 * sizeof(float));

    ML::OpenCLProgram *program = new ML::OpenCLProgram(sigmoidCode);
    cl_kernel sigmoidKernel = context->compile(program, "sigmoid");
    cl_mem inputBuffer = context->addBuffer(sigmoidKernel, CL_MEM_READ_ONLY, sizeof(cl_float) * 5);
    cl_mem outputBuffer = context->addBuffer(sigmoidKernel, CL_MEM_WRITE_ONLY, sizeof(cl_float) * 5);

    context->write(inputBuffer, values, sizeof(float) * 5);

    clSetKernelArg(sigmoidKernel, 0, sizeof(cl_mem), &inputBuffer);
    clSetKernelArg(sigmoidKernel, 1, sizeof(cl_mem), &outputBuffer);

    size_t workgroupSize = context->maximumWorkgroupSize(sigmoidKernel);
    context->enqueueRun(sigmoidKernel, 5, workgroupSize);
    context->finish();
    context->read(outputBuffer, results, sizeof(float) * 5);

    clReleaseMemObject(inputBuffer);
    clReleaseMemObject(outputBuffer);
    delete program;
    delete context;

    BOOL result = true;
    for (int i = 0; i < 5; i++) {
        result &= ((results[i] - values[i] * values[i]) < FLT_EPSILON);
    }

    free(results);

    return result;
}

@end
