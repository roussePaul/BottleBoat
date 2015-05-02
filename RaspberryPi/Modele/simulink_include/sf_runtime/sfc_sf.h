/* Copyright 2013 The MathWorks, Inc. */

#ifndef _sf_runtime_sfc_sf_h_
#define _sf_runtime_sfc_sf_h_

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifndef FORCE_S_FUNCTION_LEVEL_ONE
#define S_FUNCTION_LEVEL 2
#endif

#if S_FUNCTION_LEVEL==2
#define MDL_RTW
#define MDL_INITIALIZE_CONDITIONS
#define MDL_SET_WORK_WIDTHS  
#define MDL_DISABLE
#define MDL_ENABLE
#define MDL_START
#define MDL_EXT_MODE_EXEC
#define MDL_PROCESS_PARAMETERS
#define MDL_ZERO_CROSSINGS
#define MDL_DERIVATIVES
#define MDL_SIM_STATE
#endif

#include "mwmathutil.h"
#include "sf_runtime_spec.h"

#include "simstruc.h"

#include "mex.h"
#define real_T double
#define int_T int

    struct SfDebugInstanceStruct;
    typedef struct
    {
        unsigned int isEMLChart;
        void                            *chartInstance;
        char sFunctionName[mxMAXNAM];
        unsigned int chartInitialized;
        void (*sFunctionGateway)(void *chartInstance);
        void (*extModeExec)(void *chartInstance);
        void (*restoreLastMajorStepConfiguration)(void *chartInstance);
        void (*restoreBeforeLastMajorStepConfiguration)(void *chartInstance);
        void (*storeCurrentConfiguration)(void *chartInstance);
        void (*initializeChart)(void* chartInstance);
        void (*terminateChart)(void *chartInstance);
        void (*enableChart)(void *chartInstance);
        void (*disableChart)(void *chartInstance);
        const mxArray* (*getSimState)(SimStruct* S);
        const mxArray* (*getSimStateInfo)(void);
        void (*setSimState)(SimStruct* S, const mxArray *st);
        void (*zeroCrossings)(void *chartInstance);
        void (*outputs)(void *chartInstance);
        void (*derivatives)(void *chartInstance);
        void (*mdlRTW)(SimStruct *S);
        void (*mdlSetWorkWidths)(SimStruct *S);
        void (*mdlStart)(SimStruct *S);
        struct SfDebugInstanceStruct* debugInstance;
    } ChartInfoStruct;

    typedef struct
    {
        bool isJITEnabled;
        void * instanceInfo;
    } ChartRunTimeInfo;

    typedef void (*MdlMethodFcnPtr)(SimStruct* S);
    LIBMWSF_RUNTIME_API void callMdlMethodAndReportError(MdlMethodFcnPtr callee, SimStruct* S);

    LIBMWSF_RUNTIME_API unsigned int sf_rtw_info_uint_prop(const char* spec,
                                                           mxArray *infoStruct,
                                                           unsigned int chartFileNumber,
                                                           const char *uintPropName);
    LIBMWSF_RUNTIME_API void sf_update_buildInfo(const char* spec,
                                                 mxArray *infoStruct,
                                                 unsigned int chartFileNumber);
    LIBMWSF_RUNTIME_API unsigned int sf_is_chart_inlinable(const char* spec,
                                                           mxArray *infoStruct,
                                                           unsigned int chartFileNumber);
    LIBMWSF_RUNTIME_API void sf_mark_output_events_with_multiple_callers(SimStruct *S,
                                                     const char* spec,
                                                     mxArray *infoStruct,
                                                     unsigned int chartFileNumber,
                                                     unsigned numOutputFcnCalls);
    LIBMWSF_RUNTIME_API void sf_mark_chart_reusable_outputs(SimStruct *S,
                                        const char* spec,
                                        mxArray *infoStruct,
                                        unsigned int chartFileNumber,
                                        unsigned numOutputData);
    LIBMWSF_RUNTIME_API void sf_mark_chart_expressionable_inputs(SimStruct *S,
                                             const char* spec,
                                             mxArray *infoStruct,
                                             unsigned int chartFileNumber,
                                             unsigned numInputData);
    LIBMWSF_RUNTIME_API unsigned int sim_mode_is_rtw_gen(SimStruct *S);
    LIBMWSF_RUNTIME_API unsigned int sim_mode_is_external(SimStruct *S);
    LIBMWSF_RUNTIME_API unsigned int sim_mode_is_modelref_sim(SimStruct *S);

    LIBMWSF_RUNTIME_API DTypeId sf_get_fixpt_data_type_id(SimStruct *S,
                                             unsigned int nBits,
                                             bool isSigned,
                                             int exponent,
                                             double slope,
                                             double bias);
    LIBMWSF_RUNTIME_API DTypeId sf_get_enum_data_type_id(SimStruct *S,
                                            const char *enumTypeName);
    LIBMWSF_RUNTIME_API DTypeId sf_get_param_data_type_id(SimStruct *S,
                                             int idx);
    struct SfDebugInstanceStruct;
    LIBMWSF_RUNTIME_API unsigned int sf_mex_listen_for_ctrl_c(struct SfDebugInstanceStruct* debugInstance, SimStruct *S);
    LIBMWSF_RUNTIME_API unsigned int sf_mex_listen_for_ctrl_c_force(SimStruct *S);
    LIBMWSF_RUNTIME_API const mxArray *sf_mex_get_sfun_param(SimStruct *S, int_T paramIndex, int_T bStrict);
    LIBMWSF_RUNTIME_API void *sf_get_runtime_param_data(void *SVoid, int_T paramIndex);
    LIBMWSF_RUNTIME_API void sf_call_output_fcn_call(SimStruct *S,
                                        int eventIndex,
                                        const char *eventName,
                                        int checkForInitialization);
    LIBMWSF_RUNTIME_API mxArray *sf_load_rtw_optimization_info(const char *machineName,
                                                  const char *mainMachineName);
    LIBMWSF_RUNTIME_API void sf_clear_rtw_identifier(SimStruct *S);
    LIBMWSF_RUNTIME_API void sf_write_symbol_mapping(SimStruct *S,
                                 mxArray *infoStruct,
                                 unsigned int chartFileNumber);
    LIBMWSF_RUNTIME_API void sf_call_output_fcn_enable(SimStruct *S,
                                          int eventIndex,
                                          const char *eventName,
                                          int checkForInitialization);
    LIBMWSF_RUNTIME_API void sf_call_output_fcn_disable(SimStruct *S,
                                           int eventIndex,
                                           const char *eventName,
                                           int checkForInitialization);
    LIBMWSF_RUNTIME_API void sf_set_rtw_dwork_info(SimStruct *S, const char* spec, mxArray *infoStruct,unsigned chartFileNumber);
    LIBMWSF_RUNTIME_API mxArray* sf_get_dwork_info_from_mat_file(SimStruct *S,
                                             const char* spec,
                                             mxArray *infoStruct,
                                             unsigned chartFileNumber,
                                             const char* propName);
    LIBMWSF_RUNTIME_API void sf_set_encoded_dwork_info(SimStruct *S,
                                   const char *encodedDWorkInfo[],
                                   int len,
                                   int segSize);
    LIBMWSF_RUNTIME_API SimStruct* sf_get_subchart_simstruct(SimStruct *S, const char* blockName);
    LIBMWSF_RUNTIME_API mxArray* sf_get_sim_state_info(SimStruct *S);
    LIBMWSF_RUNTIME_API void sf_set_sim_state(SimStruct *S, const mxArray *st);

    typedef unsigned int (*GlobalMethodDispatcherFcnType)(SimStruct* s, const char* machineName, unsigned int bufLen, const char* specStr, int method, void* data);

    LIBMWSF_RUNTIME_API void sf_refresh_sfun_block_specialization(SimStruct *S);
    LIBMWSF_RUNTIME_API mxArray* sf_get_sfun_block_specialization(SimStruct *S, bool refresh);
    LIBMWSF_RUNTIME_API void call_sf_machine_global_method_dispatcher(SimStruct *S, int_T method, bool refreshSpec, GlobalMethodDispatcherFcnType fcnPtr);
    LIBMWSF_RUNTIME_API void loadSimStructFunctionPointers(SimStruct* S);
    LIBMWSF_RUNTIME_API int sf_get_output_port_reusable(SimStruct *S, int portNumber);
    LIBMWSF_RUNTIME_API double sf_get_time(SimStruct *S);

#define SF_SIM_RUNNING 0
#define SF_SIM_STOPPED 1
#define SF_SIM_PAUSED 2

#endif

