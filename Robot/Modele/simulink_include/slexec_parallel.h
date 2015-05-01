#ifndef SIMULINK_EXECUTION_PARALLEL_H
#define SIMULINK_EXECUTION_PARALLEL_H

/**
 * @file slexec_parallel.h
 *
 * This header is the exported interface to the simulink/execution/parallel. 
 * It is used by the Rapid Accelerator targets.
 *
 * 
 * Copyright 2008-2012 The MathWorks, Inc.
 */


#include "tmwtypes.h"
#include "simstruc.h"
#include "slexec_linkage_spec.h"

typedef void (*ParallelForTaskFunction)(int);

typedef enum {
    PARALLEL_EXECUTION_AUTO = -1,
    PARALLEL_EXECUTION_OFF = 0,
    PARALLEL_EXECUTION_ON = 1
} ParallelExecutionMode;

typedef struct ParallelExecutionOptions_tag {
    int numberOfNodes;
    ParallelExecutionMode parallelExecutionMode;
    int numberOfThreads;
    int numberOfStepsToAnalyze;
    boolean_T enableTiming;
    const char* timingOutputFilename;
    const char* nodeExecutionModesFilename;
} ParallelExecutionOptions;


SLEXEC_C_EXPORT_FCN void initialize_parallel_execution(
    ParallelExecutionOptions options);

SLEXEC_C_EXPORT_FCN void analyze_parallel_execution();

SLEXEC_C_EXPORT_FCN void parallel_for(int loopSize, 
                                      ParallelForTaskFunction taskFunction, 
                                      int nodeIndex);

#endif
