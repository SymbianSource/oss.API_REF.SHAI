/*
  audio_sourcesink_chipset_api.h

  Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/

#ifndef AUDIO_SOURCESINK_CHIPSET_API_H
#define AUDIO_SOURCESINK_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 *  header to compile without errors.  The includes below are required
 *  for this header file to compile successfully 
 */

#include <OMX_Audio.h>

/* Including audio_hw_control_chipset_api_v0_1.h */
#include "audio_hw_control_chipset_api_v0_1.h"

typedef struct OMX_AUDIO_PARAM_SIDETONEYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_S32 nAttenuation;
    OMX_S32 nGain;
   } OMX_AUDIO_PARAM_SIDETONETYPE;


/* HDMI related configuration structure */
typedef struct OMX_AUDIO_PARAM_HDMITYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nSubFrameSize;
    OMX_U32 nVaildBitsPerSample;
    OMX_U32 nQFormat;
} OMX_AUDIO_PARAM_HDMITYPE;

typedef struct OMX_AUDIO_CONFIG_TONEGENERATORTYPE {
		OMX_U32 nSize;
		OMX_VERSIONTYPE nVersion;
		OMX_U32 nPortIndex;
		OMX_BOOL bEnabled;
		OMX_TONEGENTONETYPE eTonetype;
		OMX_U32 nFrequency[2];
		OMX_U32 nDigit;
} OMX_AUDIO_CONFIG_TONEGENERATORTYPE

/* Enumerations */
typedef enum OMX_TONEGENTONETYPE { 
    OMX_TONEGEN_NormalTone,  /**< Normal Tone */ 
    OMX_TONEGEN_DtmfTone,    /**< DTMF Tone */ 
  } OMX_TONEGENTONETYPE; 

      

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif