/* Copyright 2013 The MathWorks, Inc. */

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifndef SLCLIENTSERVERAPIBRIDGE_H
#define SLCLIENTSERVERAPIBRIDGE_H

#include "simulink_spec.h"

typedef struct _ssFcnCallArgInfo_tag {
    DimsInfo_T *dimsInfo;
    int_T      dataType;
    int_T      argumentType;
    int_T      complexSignal;
} _ssFcnCallArgInfo;

typedef struct _ssFcnCallStatusArgInfo_tag {
    boolean_T  returnStatus;
    int_T      dataType;
} _ssFcnCallStatusArgInfo;

typedef struct _ssFcnCallExecArgInfo_tag {
    void       *dataPtr;
    int_T      dataSize;
} _ssFcnCallExecArgInfo;

typedef struct _ssFcnCallExecArgs_tag {
    int_T                  numInArgs;
    int_T                  numOutArgs;
    _ssFcnCallExecArgInfo  *inArgs;
    _ssFcnCallExecArgInfo  *outArgs;
    _ssFcnCallExecArgInfo  *statusArg;
} _ssFcnCallExecArgs;

typedef struct _ssFcnCallArgs_tag {
    int_T                    numInArgs;
    int_T                    numOutArgs;
    _ssFcnCallStatusArgInfo  *statusArg;
    _ssFcnCallArgInfo        *inArgs;
    _ssFcnCallArgInfo        *outArgs;
} _ssFcnCallArgs;

typedef void (*ServerFunctionPtr)(SimStruct *S, int tid, _ssFcnCallExecArgs *args);

#endif

SIMULINK_EXPORT_EXTERN_C void slcsRegisterServerFunction(
    SimStruct* S, const char * fcnName, ServerFunctionPtr fcnPtr,
    _ssFcnCallArgs args);

SIMULINK_EXPORT_EXTERN_C void slcsRequestService(
    SimStruct* S, const char * fcnName, _ssFcnCallExecArgs args);
