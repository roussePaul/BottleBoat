#ifndef SIMULINK_EXECUTION_LINKAGE_SPEC_H
#define SIMULINK_EXECUTION_LINKAGE_SPEC_H

/**
 * @file slexec_linkage_spec.h
 *
 * This header defines the symbol visibility control for simulink execution
 * and generated code.
 * 
 * Copyright 2012 The MathWorks, Inc.
 */

#if defined(RSIM_WITH_SL_SOLVER) && defined(__cplusplus)
  #define SLEXEC_C_EXPORT_FCN extern "C"  
#elif defined(RSIM_WITH_SL_SOLVER) && !defined(__cplusplus)
  #define SLEXEC_C_EXPORT_FCN extern    
#elif defined(BUILDING_SLEXEC_SIMBRIDGE) || defined(BUILDING_SLEXEC_PARALLEL)
  #include "package.h"
  #define SLEXEC_C_EXPORT_FCN extern "C" DLL_EXPORT_SYM
#elif defined(SLEXEC_C_API_CXX_TEST)
  #define SLEXEC_C_EXPORT_FCN extern "C" 
#elif defined(SLEXEC_C_API_C_TEST)
  #define SLEXEC_C_EXPORT_FCN extern 
#else
  #error Unrecognized use of simulink execution linkage spec 
#endif

#endif
