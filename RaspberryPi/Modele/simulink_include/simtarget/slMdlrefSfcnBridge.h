/* Copyright 2013-2014 The MathWorks, Inc. */

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifndef SLMDLREFSFCNBRIDGE_H
#define SLMDLREFSFCNBRIDGE_H

#include "simulink_spec.h"

SIMULINK_EXPORT_EXTERN_C void slmrPortSampleTimeMapAddStructs(
    SimStruct* S, int numStructs, size_t* allStructs);

SIMULINK_EXPORT_EXTERN_C void slmrSetDataTypeOverrideSettings(
    SimStruct* sfcnS, int dataTypeOverrideMode,
    int dataTypeOverrideAppliesTo );

SIMULINK_EXPORT_EXTERN_C void slmrSetDataDictionarySet(SimStruct* sfcnS, const char* ddSetString);

SIMULINK_EXPORT_EXTERN_C void slmrSetIsInlineParamsOn(SimStruct* S, bool isInlineParamsOn);

SIMULINK_EXPORT_EXTERN_C void slmrSetHasNonVirtualConstantTs(SimStruct* S, bool hasNonVirtualConstantTs);

SIMULINK_EXPORT_EXTERN_C void slmrSetUnionTsContainedTs(SimStruct* S,
                                            int unionTsIdx,
                                            int containedTsIdx);

SIMULINK_EXPORT_EXTERN_C int_T slmrGetParentTidFromExpFcnMdlChildTid(SimStruct* S,
                                                         int_T      childTid);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefFcnCallPortGroupSetSpecifiedTs(SimStruct* S,
                                                             double     period,
                                                             double     offset);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefFcnCallPortGroupSetNeedRunTimeCheck(
    SimStruct* S, bool val);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefFcnCallPortGroupAddPortGroupWithDataTransferConnection(
    SimStruct* S, int_T portGroupIdx);

SIMULINK_EXPORT_EXTERN_C void slmrSetHasDataLoggedInLegacyFormat(SimStruct* S,
                                                     boolean_T  val);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefInitPortGroupsInSameRate(SimStruct* S);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateAddMergeGroup(
    SimStruct* S, const char* rootMergeBlkName);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateAddMergedPortGroup(
    SimStruct* S, int portGroupIdx);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateInitDSMEntry(
    SimStruct* S, const char* dsmName);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateAddDSMPortGroupIdx(
    SimStruct* S, int portGroupIdx);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateInitGlobalDSMEntry(
    SimStruct* S, const char* dsmName);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefPortGroupsInSameRateAddGlobalDSMPortGroupIdx(
    SimStruct* S, int portGroupIdx);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefAddCompTsOfGlobalDSMAccessedByDescExpFcnMdlToHash(
    SimStruct  *S,
    const char *dsmName,
    double      period,
    double      offset,
    const char *descExpFcnMdlPath);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefSetHasDescExpFcnMdl(SimStruct* S,
                                                              boolean_T  val);

SIMULINK_EXPORT_EXTERN_C void slmrModelRefSetOutputPortDrivenByNonCondExecStateflow(
    SimStruct* S, int portIdx, boolean_T val);

#endif
