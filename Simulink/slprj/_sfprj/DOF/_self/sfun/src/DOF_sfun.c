/* Include files */

#include "DOF_sfun.h"
#include "DOF_sfun_debug_macros.h"
#include "c1_DOF.h"
#include "c2_DOF.h"
#include "c3_DOF.h"
#include "c4_DOF.h"
#include "c5_DOF.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _DOFMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void DOF_initializer(void)
{
}

void DOF_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_DOF_method_dispatcher(SimStruct *simstructPtr, unsigned int
  chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_DOF_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_DOF_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_DOF_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_DOF_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_DOF_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_DOF_process_check_sum_call( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2358429499U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1903681987U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2160741382U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3561016193U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2085501899U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(983571124U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3444439919U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3449890858U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_DOF_get_check_sum(mxArray *plhs[]);
          sf_c1_DOF_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_DOF_get_check_sum(mxArray *plhs[]);
          sf_c2_DOF_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_DOF_get_check_sum(mxArray *plhs[]);
          sf_c3_DOF_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_DOF_get_check_sum(mxArray *plhs[]);
          sf_c4_DOF_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_DOF_get_check_sum(mxArray *plhs[]);
          sf_c5_DOF_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2083502392U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1110276785U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3258378658U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3926592909U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(714648136U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1457393705U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2945398962U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4271924963U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_DOF_autoinheritance_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "2zyvqMiALdODipGgoiiQDB") == 0) {
          extern mxArray *sf_c1_DOF_get_autoinheritance_info(void);
          plhs[0] = sf_c1_DOF_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "5DMIhId5UCkV3jzf3Rqy2C") == 0) {
          extern mxArray *sf_c2_DOF_get_autoinheritance_info(void);
          plhs[0] = sf_c2_DOF_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "Bq5N97Xnei6s9VUYKOGHCF") == 0) {
          extern mxArray *sf_c3_DOF_get_autoinheritance_info(void);
          plhs[0] = sf_c3_DOF_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "YqpTy7iecWrFrvY7YCCsvB") == 0) {
          extern mxArray *sf_c4_DOF_get_autoinheritance_info(void);
          plhs[0] = sf_c4_DOF_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "MWX0ymzAuk2M1ODbiUTmpE") == 0) {
          extern mxArray *sf_c5_DOF_get_autoinheritance_info(void);
          plhs[0] = sf_c5_DOF_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_DOF_get_eml_resolved_functions_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_DOF_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_DOF_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_DOF_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_DOF_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_DOF_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_DOF_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_DOF_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_DOF_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_DOF_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_DOF_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_DOF_third_party_uses_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "yOy4VhNAr0aVcvrzuol5bG") == 0) {
          extern mxArray *sf_c1_DOF_third_party_uses_info(void);
          plhs[0] = sf_c1_DOF_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "6TnTOR9uIXOlrjm0ZwetfD") == 0) {
          extern mxArray *sf_c2_DOF_third_party_uses_info(void);
          plhs[0] = sf_c2_DOF_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "vrArC9dcciQJhIzZG2b51D") == 0) {
          extern mxArray *sf_c3_DOF_third_party_uses_info(void);
          plhs[0] = sf_c3_DOF_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "OPK9SKXupg5qxFom2u2AnD") == 0) {
          extern mxArray *sf_c4_DOF_third_party_uses_info(void);
          plhs[0] = sf_c4_DOF_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "2zHqJMYKfL2PHhZwAWMKiD") == 0) {
          extern mxArray *sf_c5_DOF_third_party_uses_info(void);
          plhs[0] = sf_c5_DOF_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_DOF_updateBuildInfo_args_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "yOy4VhNAr0aVcvrzuol5bG") == 0) {
          extern mxArray *sf_c1_DOF_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_DOF_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "6TnTOR9uIXOlrjm0ZwetfD") == 0) {
          extern mxArray *sf_c2_DOF_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_DOF_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "vrArC9dcciQJhIzZG2b51D") == 0) {
          extern mxArray *sf_c3_DOF_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_DOF_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "OPK9SKXupg5qxFom2u2AnD") == 0) {
          extern mxArray *sf_c4_DOF_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_DOF_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "2zHqJMYKfL2PHhZwAWMKiD") == 0) {
          extern mxArray *sf_c5_DOF_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_DOF_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void DOF_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _DOFMachineNumber_ = sf_debug_initialize_machine(debugInstance,"DOF","sfun",0,
    5,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_DOFMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_DOFMachineNumber_,0);
}

void DOF_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_DOF_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("DOF", "DOF");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_DOF_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
