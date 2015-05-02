#ifdef SUPPORTS_PRAGMA_ONCE
# pragma once
#endif
#ifndef sl_fileio_rtw_h
#define sl_fileio_rtw_h
/*
 *
 * Copyright 2008-2013 The MathWorks, Inc.
 *
 * This header is the interface to the sl_fileio module. It is used by the
 * RTW-RSim and Rapid Accelerator targets.
 *
 * 
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

extern const char *rtwH5LoggingCreateInstance(
    const char     *fileName, 
    int            errorXMLMode,
    const char     *objName,
    const char     *sigName,
    const char     *interpolationName,
    const char     *className,
    const int       nDims,
    const int      *dims,
    const int       isComplex,
    const int       decimation,
    const int       formatInt,
    const int       isFixedPoint,
    const int       dataTypeMode,
    const int       isSigned,
    const int       wordLength,
    const double    slopeAdjustmentFactor,
    const int       fixedExponent,
    const double    bias,
    void          **outH5logging);

extern const char *rtwH5LoggingDestroyInstance(
    int  errorXMLMode,
    void *h5logging);

extern const char *rtwH5LoggingWrite(
    int          errorXMLMode,
    void         *h5logging,
    const double  t,
    const void   *u);

extern const char *rtwH5LoggingCollectionCreateInstance(
    int    errorXMLMode,
    void **outH5LoggingCollection
    );

extern const char *rtwH5LoggingCollectionDestroyInstance(
    int   errorXMLMode,
    void *h5LoggingCollection);

extern const char *rtwH5LoggingCollectionAddElement(
    int           errorXMLMode,
    void         *h5LoggingCollection,
    const char   *fileName,
    const char   *mtxName,
    const int     leafIdx,
    const char   *signalName,
    const char   *interpolationName,
    const char   *className,
    const int     nDims,
    const int    *dims,
    const int     isComplex,
    const int     decimation,
    const int     formatInt,
    const int     isFixedPoint,
    const int     dataTypeMode,
    const int     isSigned,
    const int     wordLength,
    const double  slopeAdjustmentFactor,
    const int     fixedExponent,
    const double  bias
    );

extern const char *rtwH5LoggingCollectionWrite(
    int           errorXMLMode,
    void         *h5LoggingCollection,
    const size_t  elementId,
    const double  t,
    const void   *u
    );

extern const char *rtwSetMcosObjName(
    const char *fileName,
    int        errorXMLMode,
    const char *objName
    );

extern const char *rtwMATFileLoaderCreateInstance(
    const char  *fileName,
    int          errorXMLMode,
    const int    extrapolationBeforeFirstDataPointInt,
    const int    interpolationWithinTimeRangeInt,
    const int    extrapolationAfterLastDataPointInt,
    const unsigned char *ground,
    const int    iZeroCrossingSwitch,
    int          fxpDiagnosticOverflow,
    const char  *fxpBlockPath,
    void        **outMATFileLoader
    );

extern const char *rtwMATFileLoaderDestroyInstance(
    int  errorXMLMode,
    void *pMATFileLoader
    );

extern const char *rtwMATFileLoaderGetOutput(
    int            errorXMLMode,
    void          *pMATFileLoader,
    const double   t,
    const int      iMajorTimeStep,
    void         **outOutputValue
    );

extern const char *rtwMATFileLoaderGetZeroCrossingSignal(
    void         *pMATFileLoader,
    const double  t,
    const int     iMajorTimeStep,
    void         *outZeroCrossingSignal
    );

extern const char *rtwMatFileLoaderCollectionCreateInstance(
    int    errorXMLMode,
    void **outMatFileLoaderCollection
    );

extern const char *rtwMatFileLoaderCollectionDestroyInstance(
    int   errorXMLMode,
    void *matFileLoaderCollection
    );

extern const char *rtwMatFileLoaderCollectionAddElement(
    int                   errorXMLMode,
    void                 *matFileLoaderCollection,
    const char           *fileName,
    const char           *varPath,
    const int             extrapolationBeforeFirstDataPointInt,
    const int             interpolationWithinTimeRangeInt,
    const int             extrapolationAfterLastDataPointInt,
    const int             iZeroCrossingSwitch,
    const unsigned char  *ground,
    const char           *className,
    const int             storageDTypeId,
    const int             nDims,
    const int            *dims,
    const int             complexity,
    const int             isFixedPoint,
    const int             dataTypeMode,
    const int             isSigned,
    const int             wordLength,
    const double          slopeAdjustmentFactor,
    const int             fixedExponent,
    const double          bias,
    const int             enumNStrings,
    const char          **enumStrings,
    const int            *enumValues,
    int                   fxpDiagnosticOverflow,
    const char           *fxpBlockPath
    );

extern const char *rtwMatFileLoaderCollectionGetOutput(
    int            errorXMLMode,
    void          *matFileLoaderCollection,
    const size_t   elementId,
    const double   t,
    const int      iMajorTimeStep,
    void         **outOutputValue
    );

extern const char *rtwMATFileLoaderCollectionGetZeroCrossingSignal(
    void         *pMatFileLoaderCollection,
    const size_t  elementId,
    const double  t,
    const int     iMajorTimeStep,
    void         *outZeroCrossingSignal
    );

extern const char *rtwMATFileLoaderCheckMATFileConsistency(
    void           *pMATFileLoader,
    const char     *MATFileName,
    int             errorXMLMode,
    const char     *expDTypeName,
    const int       expNDims,
    const int      *expDims,
    const int       expComplexity,
    const int       isFixedPoint,
    const int       dataTypeMode,
    const int       isSigned,
    const int       wordLength,
    const double    slopeAdjustmentFactor,
    const int       fixedExponent,
    const double    bias,
    const int       expEnumNStrings,
    const char    **expEnumStrings,
    const int      *expEnumValues);

/*
 * Logging Codegen declarations.
 */

extern void rtwSignalProbeCreateInstance(
    const char *datasetName,
    const char *elementName,
    const char *signalName,
    const char *blockPath,
    unsigned int portIndex,
    const char *interpolationMethod,
    unsigned int decimation,
    unsigned int maxPoints,
    void **outSignalProbe,
    const char *typeName,
    unsigned int complex,
    unsigned int nDim,
    unsigned int * pDim
    );

extern void rtwFxpSignalProbeCreateInstance(
    const char *datasetName,
    const char *elementName,
    const char      *signalName,
    const char      *blockPath,
    unsigned int portIndex,
    const char      *interpolationMethod,
    unsigned int decimation,
    unsigned int maxPoints,
    void            **outSignalProbe,
    const char      *typeName,
    unsigned int    complex,
    unsigned int    nDim,
    unsigned int *pDim,
    const int       isSigned,
    const int       wordLength,
    const double    slopeAdjustmentFactor,
    const int       fixedExponent,
    const double    bias
    );

extern void rtwSignalProbeDestroyInstace(
    void *pOpaqueSignalProbe
    );

extern void rtwSignalProbeAppendSample(
    void *pOpaqueSignalProbe,
    const double t,
    const void *u
    );

extern void rtwSignalProbeSaveDatasetMatFile(
    const void *pOpaqueSignalProbe,
    const char *fileName
    );

extern void rtwAobHierarchyCreateRootNode(void **outAobHierarchy);

extern void rtwAobHierarchyCreateNode(const char *name, void **outAobHierarchy);

extern void rtwAobHierarchySetDim(
    void *pOpaqueAobHierarchy,
    const unsigned int nDims,
    const unsigned int *pDim
    );

extern void rtwAobHierarchyAddChild(
    void *pOpaqueAobParent, 
    void *pOpaqueAobChild
    );

extern void rtwAobHierarchyVerifyNNodes(
    void *pOpaqueAobHierarchy,
    const unsigned int nNodes
    );

extern void rtwSignalProbeCollectionCreateInstance(
    const char *datasetName,
    const char *elementName,
    const char *blockPathToTopMdl,
    const char *localBlockPath,
    const char *sigLogSelectorFileName,
    const unsigned int portIdx,
    void **outSignalProbeCollection
    );

extern void rtwSignalProbeCollectionDestroyInstance(
    void *pOpaqueSignalProbeCollection    
    );

extern void rtwSignalProbeCollectionAddElement(
    void * const pOpaqueSignalProbeCollection,
    const char *signalName,
    const char *interpMethod,
    const unsigned int decimation,
    const unsigned int maxDataPoints,
    const unsigned int nDims,
    const unsigned int *pDim,
    const unsigned int complexity,
    const char *typeName
    );

extern void rtwSignalProbeCollectionAddElementFxp(
    void * const pOpaqueSignalProbeCollection,
    const char *signalName,
    const char *interpMethod,
    const unsigned int decimation,
    const unsigned int maxDataPoints,
    const unsigned int nDims,
    const unsigned int *pDim,
    const unsigned int complexity,
    const char *typeName,
    const unsigned int isSigned,
    const int wordLength,
    const double slopeAdjustmentFactor,
    const int fixedExponent,
    const double bias
    );

extern void rtwSignalProbeCollectionVerifyNLeaves(
    const void * const pOpaqueSignalProbeCollection,
    const unsigned int nLeaves
    );

extern void rtwSignalProbeCollectionSetAobHierarchy(
    void * const pOpaqueSignalProbeCollection,
    void * const pOpaqueAobHierarchy
    );

extern void rtwSignalProbeCollectionFinalizeMetaData(
    void * const pOpaqueSignalProbeCollection
    );

extern void rtwSignalProbeCollectionAppendSample(
    void * const pOpaqueSignalProbeCollection,
    const unsigned int elementIdx,
    const double t,
    const void * const pData
    );

extern void rtwSignalProbeCollectionSaveDatasetMatFile(
    const void * const pOpaqueSignalProbeCollection,
    const char *fileName
    );

extern int rtwSignalProbeCollectionGetLoggingIsOn(
    const void * const pOpaqueSignalProbeCollection
    );

#ifdef __cplusplus
}
#endif

#endif /* sl_fileio_rtw_h */

/* LocalWords:  RSim
 */
