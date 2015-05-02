/* Copyright 2013 The MathWorks, Inc. */

#ifndef _sf_runtime_utils_h_
#define _sf_runtime_utils_h_

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#include "mex.h"
#include "sf_runtime_spec.h"

#if !defined(S_FUNCTION_NAME)
    #include "simstruct/simstruc.h"
#else
    #include "simstruc.h"
#endif

typedef enum
{
    SF_DOUBLE  = 0,
    SF_SINGLE,
    SF_INT8,
    SF_UINT8,
    SF_INT16,
    SF_UINT16,
    SF_INT32,
    SF_UINT32,
    SF_INT64,
    SF_UINT64,
    SF_CHAR,
    SF_BOOL,
    SF_MATLAB,
    SF_STRUCT,
    SF_UNKNOWN_ZZ,
    SF_STRING,
    SF_ENUM,
    SF_TOTAL_DATA_TYPES
} SfDataType;

typedef enum
{
    SF_ROW_MAJOR,
    SF_COLUMN_MAJOR
} SfIndexScheme;

#define MATLAB_CLASSES(X)      \
    X(LOGICAL,boolean_T,int)   \
    X(CHAR,char_T,int)         \
    X(DOUBLE,real_T,double)    \
    X(SINGLE,real32_T,double)               \
    X(INT8,int8_T,int)                      \
    X(UINT8,uint8_T,int)                    \
    X(INT16,int16_T,int)                    \
    X(UINT16,uint16_T,int)                  \
    X(INT32,int32_T,int)                    \
    X(UINT32,uint32_T,unsigned int)

typedef enum
{
#define DEFINE_ENUM(NAME,CTYPE,CTYPE2) ML_##NAME = mx##NAME##_CLASS,
    MATLAB_CLASSES(DEFINE_ENUM)
#undef DEFINE_ENUM
    ML_MX_ARRAY,
    ML_STRING,
    ML_VOID,
    ML_LAST_DATA_TYPE
} MatlabDataType;

#ifdef __cplusplus
#define MatlabWorkspaceType int
#define BASE_WORKSPACE   0
#define CALLER_WORKSPACE 1
#define GLOBAL_WORKSPACE 2
#define ALL_WORKSPACES   3
#else
typedef enum
{
    BASE_WORKSPACE,
    CALLER_WORKSPACE,
    GLOBAL_WORKSPACE,
    ALL_WORKSPACES
} MatlabWorkspaceType;
#endif

LIBMWSF_RUNTIME_API void sf_mex_set_error_status(SimStruct *S, const char *fmt, ...);
LIBMWSF_RUNTIME_API  bool mx_array_has_fi_type(const mxArray *mxArrayPtr);

LIBMWSF_RUNTIME_API const mxArray *sf_mex_get_ml_var_no_error(const char *variableName, MatlabWorkspaceType workspaceType);
LIBMWSF_RUNTIME_API const mxArray *sf_mex_get_ml_var(const char *variableName, MatlabWorkspaceType workspaceType);

LIBMWSF_RUNTIME_API void sf_mex_printf(const char *msg, ...);
LIBMWSF_RUNTIME_API bool sf_mex_mx_is_numeric(const mxArray *mxArrayPtr);

LIBMWSF_RUNTIME_API int sf_mex_call_matlab(int nlhs, mxArray* plhs[], int nrhs, mxArray* prhs[], const char* fcnName);

#endif
