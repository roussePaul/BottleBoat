/* Copyright 2013 The MathWorks, Inc. */

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifndef SL_SFCN_COV_BRIDGE_H
#define SL_SFCN_COV_BRIDGE_H

#include "tmwtypes.h"

#ifdef BUILDING_LIBMWSL_SFCN_COV_BRIDGE
  /* being included from simulink source code */
  # define LINKAGE_SPEC extern "C" DLL_EXPORT_SYM
  # include "package.h"
#else
  # ifdef S_FUNCTION_NAME
  /* Used with any s-function (user written) - normal sim, rtw (grt) */
    # define LINKAGE_SPEC extern
  # else
    # ifdef MDL_REF_SIM_TGT
    /* Used with any Model Ref SIM s-function */
      # define LINKAGE_SPEC extern
    # else
      /* Defaulting now to allow Stateflow to compile */
      # define LINKAGE_SPEC extern
    # endif
  # endif
#endif

#ifndef _SIMSTRUCT
# define _SIMSTRUCT
  typedef struct SimStruct_tag SimStruct;
#endif

typedef uint32_T covid_T;

LINKAGE_SPEC void slcovEnterSFunctionMethod(SimStruct* S, boolean_T isStart);
LINKAGE_SPEC void slcovExitSFunctionMethod(SimStruct* S, boolean_T isTerminate);
LINKAGE_SPEC void slcovUploadSFunctionCoverageData(covid_T covId);

#endif

