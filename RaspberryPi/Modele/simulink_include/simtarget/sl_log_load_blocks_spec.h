/* Copyright 2013 The MathWorks, Inc. */

#ifndef SL_LOG_LOAD_BLOCKS_SPEC_H
#define SL_LOG_LOAD_BLOCKS_SPEC_H

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifdef BUILDING_SL_LOG_LOAD_BLOCKS

# define SL_LOG_LOAD_BLOCKS_EXPORT_EXTERN_C extern "C" DLL_EXPORT_SYM

#elif defined(DLL_IMPORT_SYM)

#ifdef __cplusplus
# define SL_LOG_LOAD_BLOCKS_EXPORT_EXTERN_C extern "C" DLL_IMPORT_SYM
#else
# define SL_LOG_LOAD_BLOCKS_EXPORT_EXTERN_C extern DLL_IMPORT_SYM
#endif

#else

#ifdef __cplusplus
#define SL_LOG_LOAD_BLOCKS_EXPORT_EXTERN_C extern "C"
#else
#define SL_LOG_LOAD_BLOCKS_EXPORT_EXTERN_C extern
#endif

#endif

#endif

