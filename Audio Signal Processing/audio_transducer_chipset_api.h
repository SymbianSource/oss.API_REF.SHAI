/*
  audio_transducer_chipset_api.h

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

#ifndef AUDIO_TRANSDUCER_CHIPSET_API_H
#define AUDIO_TRANSDUCER_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 *  header to compile without errors.  The includes below are required
 *  for this header file to compile successfully 
 */

#include <OMX_Audio.h>

#define MAX_FIRRESPONSE_POINTS 100

/* Transducer Equalizer parameters */


typedef enum OMX_AUDIO_PHASERESPONSETYPE {
OMX_AUDIO_PhaseNotDefined,   
OMX_AUDIO_LinearPhase,	
OMX_AUDIO_MinimumPhase,
} OMX_AUDIO_PHASERESPONSETYPE;


typedef enum OMX_AUDIO_FILTERTYPE {
OMX_AUDIO_NotDefined,   
OMX_AUDIO_Peaking,	
OMX_AUDIO_Lowpass,	
OMX_AUDIO_Highpass,
OMX_AUDIO_Lowshelf,	
OMX_AUDIO_Highshelf,
} OMX_AUDIO_FILTERTYPE;


typedef struct OMX_AUDIO_CONFIG_IIR_EQUALIZER  {
     OMX_U32 nSize;
     OMX_VERSIONTYPE nVersion;  
     OMX_U32 nPortIndex;
     OMX_BU32 sBandIndex ; 
     OMX_AUDIO_FILTERTYPE eFilterType;
     OMX_U32 nFilterCenterCutoffFrequency;
     OMX_S32 nFilterGain;
     OMX_U32 nFilterBandwidth; /* Q-value could be used instead. */
 } OMX_AUDIO_CONFIG_IIR_EQUALIZER;


typedef struct OMX_AUDIO_CONFIG_FIR_RESPONSE  {
     OMX_U32 nSize;
     OMX_VERSIONTYPE nVersion;  
     OMX_U32 nPortIndex;
     OMX_u32 nFrequencyPoints; 
     OMX_S32 nFrequencies[MAX_FIRRESPONSE_POINTS];
     OMX_S32 nGains[MAX_FIRRESPONSE_POINTS];
} OMX_AUDIO_CONFIG_FIR_RESPONSE;


typedef struct OMX_AUDIO_CONFIG_TRANSDUCEREQUALIZERTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_BOOL bEnableFir;
     OMX_BOOL bEnableIir;
     OMX_U32 nChannel;
     OMX_AUDIO_PHASERESPONSETYPE ePhaseResponseTargetFir;
     OMX_AUDIO_PHASERESPONSETYPE ePhaseResponseTargetIir;
     OMX_U32 nIIREqualizerBlocks;
     OMX_U32 nIIREqualizerGain;
} OMX_AUDIO_CONFIG_TRANSDUCEREQUALIZERTYPE;


/* MDRC parameters */

typedef struct OMX_AUDIO_CONFIG_MDRCTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_BU32 sBandIndex;
    OMX_BU32 sBandRange;
    OMX_BU32 sBandLevel;
    OMX_BU32 sKneePoints;	
    OMX_U32 nDynamicResponse[10][2];
    OMX_BU32 sAttackTime; 
    OMX_BU32 sReleaseTime;	    
} OMX_AUDIO_CONFIG_MDRCTYPE;

/* Transducer (Loudspeaker) protection parameters */

typedef struct OMX_AUDIO_CONFIG_LSPROTECTIONTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_AUDIO_CHANNELTYPE eChannel;
    OMX_BOOL bEnable;
 } OMX_AUDIO_CONFIG_LSPROTECTIONTYPE;

/* End of Transducer protection params */

/* Transducer SPL limit parameters */

typedef enum OMX_AUDIO_SPLLIMITTYPE {
OMX_AUDIO_SPLLimitation,	
OMX_AUDIO_SPLNormalization,	
OMX_AUDIO_SPLMax,
} OMX_AUDIO_OMX_AUDIO_SPLLIMITTYPE;


typedef struct OMX_AUDIO_CONFIG_SPLLIMITTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_AUDIO_SPLLIMITTYPE eMode;
    OMX_S32 nSplLimit;
    OMX_S32 nGain;	    
} OMX_AUDIO_CONFIG_SPLLIMITTYPE;
/* End of transducer SPL limit params */

/* Click Removal algorithm parameters */

typedef struct OMX_AUDIO_CONFIG_CLICKREMOVALTYPE {
   	OMX_U32 nSize;
   	OMX_VERSIONTYPE nVersion;
   	OMX_U32 nPortIndex;
   	OMX_BOOL bEnable;
		OMX_BU16 sClickControl;
} OMX_AUDIO_CONFIG_CLICKREMOVALTYPE;
/* End of click removal params */

/* Earpiece Active Noise Control */

typedef struct OMX_AUDIO_CONFIG_EARPIECE_ACTIVE_NOISE_CONTROL { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_BOOL bEnable;
} OMX_AUDIO_CONFIG_EARPIECE_ACTIVE_NOISE_CONTROL;

/* Algorithm for Preventing System Shutdown by Audio System (APSSAS) */

typedef struct OMX_AUDIO_PARAM_APSSASTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
} OMX_AUDIO_PARAM_APSSASTYPE;

typedef struct OMX_AUDIO_CONFIG_BATTERY_VOLTAGETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nBattVol;
} OMX_AUDIO_CONFIG_BATTERY_VOLTAGETYPE;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif