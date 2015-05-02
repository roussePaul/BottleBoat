/* Copyright 2013 The MathWorks, Inc. */

#ifndef _sf_runtime_sf_runtime_h_
#define _sf_runtime_sf_runtime_h_

#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#include "simstruc.h"

#include "sf_runtime_spec.h"

LIBMWSF_RUNTIME_API void sf_msg_calendar_push(SimStruct* S, int outportNum, void* payload, size_t payloadSize);
LIBMWSF_RUNTIME_API int sf_msg_calendar_peek(SimStruct* S, int inportNum, void* payload, size_t payloadSize);
LIBMWSF_RUNTIME_API void sf_msg_calendar_pop(SimStruct* S, int inportNum);
LIBMWSF_RUNTIME_API void sf_msg_calendar_terminate();
LIBMWSF_RUNTIME_API void sf_msg_calendar_initialize();
#endif
