/*
  audio_telephony_chipset_api.h

  Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/

#ifndef AUDIO_TELEPHONY_CHIPSET_API_H
#define AUDIO_TELEPHONY_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 *  header to compile without errors.  The includes below are required
 *  for this header file to compile successfully 
 */

#include <OMX_Audio.h>

  /* Speech decoder status information */

  typedef struct OMX_AUDIO_DECODER_STATUS  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion ;
    OMX_AUDIO_CODINGTYPE nCoding;
    OMX_U32 nBitrate;
  } OMX_AUDIO_DECODER_STATUS;
  
  /* Speech encoder status information */

  typedef struct OMX_AUDIO_ENCODER_STATUS  { 
    OMX_U32 nSize;                                    
    OMX_VERSIONTYPE nVersion ;
    OMX_AUDIO_CODINGTYPE nCoding;
    OMX_U32 nBitrate;
    OMX_BOOL bDtx;
    OMX_BOOL bAudioActivityControl;
    OMX_BOOL bNsync;
  } OMX_AUDIO_ENCODER_STATUS;

  /* Uplink timing control */

  typedef struct OMX_AUDIO_UPLINK_TIMING  { 
    OMX_U32 nSize;                                    
    OMX_VERSIONTYPE nVersion;                   
    OMX_U32 nDeliveryTime;
    OMX_U32 nModemProcessingTime;
  } OMX_AUDIO_UPLINK_TIMING;

  /* RF-TX Power information */

  typedef struct OMX_AUDIO_RF_TX_POWER  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPower;
    OMX_U32 nTime;
  } OMX_AUDIO_RF_TX_POWER;

  /* Acoustic echo control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_ACOUSTIC_ECHO_CONTROL {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_S32 sEchoGain;
    OMX_U32 nEchoMinDelay;
    OMX_U32 nEchoMaxDelay;
  } OMX_AUDIO_CONFIG_ACOUSTIC_ECHO_CONTROL;

  /* Artificial bandwidth expansion configuration parameters */

  typedef struct OMX_AUDIO_ARTIFICIAL_BANDWIDTH_EXPANSION  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_S32 nStrength;
  } OMX_AUDIO_ARTIFICIAL_BANDWIDTH_EXPANSION;
  
  /* Automatic volume control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_AUTOMATIC_VOLUME_CONTROL { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_AUTOMATIC_VOLUME_CONTROL;
  
  /*  Background noise control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_BACKGROUND_NOISE_CONTROL { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;            
    OMX_BOOL bEnable;
    OMX_U32 nStrength;
  } OMX_AUDIO_CONFIG_BACKGROUND_NOISE_CONTROL;
  
  /* Comfort noise generation configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_COMFORT_NOISE_GENERATION { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;            
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_COMFORT_NOISE_GENERATION;
  
  /*  Downlink noise control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_DOWNLINK_NOISE_CONTROL { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;            
    OMX_BOOL bEnable;
    OMX_U32 nStrength;
  } OMX_AUDIO_CONFIG_DOWNLINK_NOISE_CONTROL;
  
  /* Multimicrophone noise control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_MULTIMICROPHONE_NOISE_CONTROL { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;            
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_MULTIMICROPHONE_NOISE_CONTROL;
  
  /*  Sidetone howling control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_SIDETONE_HOWLING_CONTROL  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_S32 nSidetoneAttenuation;
  } OMX_AUDIO_CONFIG_SIDETONE_HOWLING_CONTROL;
  
  /*  Transducer dynamic range control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_TRANSDUCER_DYNAMIC_RANGE_CONTROL  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_TRANSDUCER_DYNAMIC_CONTROL;
  
  /*  Uplink level configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_UPLINK_LEVEL_NORMALIZATION  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_UPLINK_LEVEL_NORMALIZATION;

  /*  Voice clarity configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_VOICE_CLARITY  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
  } OMX_AUDIO_CONFIG_VOICE_CLARITY;
  
  /*  Wind noise control configuration parameters */

  typedef struct OMX_AUDIO_CONFIG_WIND_NOISE_CONTROL  { 
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_U32 nSensitivity;
  } OMX_AUDIO_CONFIG_WIND_NOISE_CONTROL;

  /*  Extra data base typeWind noise control configuration parameters */
  
  typedef struct OMX_OTHER_EXTRADATABASETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_EXTRADATATYPE eType;
    OMX_U32 nDataSize;
  } OMX_OTHER_EXTRADATABASETYPE;

  /*  Extra data base type */

  typedef struct OMX_AUDIO_DLSPEECHINFOTYPE {
    OMX_BOOL bComfortNoiseFrame;
    OMX_BOOL bCorruptedFrame;
  } OMX_AUDIO_DLSPEECHINFOTYPE;

  /*  Downlink speech information extra data */

  typedef struct OMX_AUDIO_EXTRADATA_DLSPEECHINFOTYPE {
    OMX_OTHER_EXTRADATABASETYPE base;
    OMX_AUDIO_DLSPEECHINFOTYPE dlspeechinfo;
  } OMX_AUDIO_EXTRADATA_DLSPEECHINFOTYPE;

  /*  DA-AD timing difference information extra data */

  typedef struct OMX_AUDIO_DAADTIMINGDIFFTYPE {
    OMX_TICKS nDaAdTimingDifference;
  } OMX_AUDIO_DAADTIMINGDIFFTYPE;

  /*  DA-AD timing difference information extra data */

  typedef struct OMX_AUDIO_DAADTIMINGDIFFTYPE {
    OMX_OTHER_EXTRADATABASETYPE base;
    OMX_AUDIO_DLSPEECHINFOTYPE dlspeechinfo;
  } OMX_AUDIO_OMX_AUDIO_DAADTIMINGDIFFTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
