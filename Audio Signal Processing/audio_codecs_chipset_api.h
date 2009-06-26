/*
  audio_codecs_chipset_api.h

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

#ifndef AUDIO_CODECS_CHIPSET_API_H
#define AUDIO_CODECS_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 *  header to compile without errors.  The includes below are required
 *  for this header file to compile successfully 
 */

#include <OMX_Audio.h>

/** AMR-WB+ related **/

typedef enum OMX_AUDIOCODINGEXTTYPE {
    OMX_AudioCodingExtStart = 0x6F000000,    /* =  OMX_AUDIO_CodingExtensions */
    /* Add Khronos approved extended components indexes here */
    OMX_AUDIO_CodingAMRWBPLUS,
    OMX_AudioCodingExtMax = 0x6FFFFFFF
} OMX_AUDIOCODINGEXTTYPE;

/** AMR Wideband Plus Extensions */
/** AMR Frame format Extension */ 
typedef enum OMX_AUDIO_AMREXT_FRAMEFORMATTYPE { 
    OMX_AUDIO_AMRFrameFormatConformance = 0,  /**< Frame Format is AMR Conformance 
                                                   (Standard) Format */ 
    OMX_AUDIO_AMRFrameFormatIF1,              /**< Frame Format is AMR Interface 
                                                   Format 1 */ 
    OMX_AUDIO_AMRFrameFormatIF2,              /**< Frame Format is AMR Interface 
                                                   Format 2*/ 
    OMX_AUDIO_AMRFrameFormatFSF,              /**< Frame Format is AMR File Storage 
                                                   Format */ 
    OMX_AUDIO_AMRFrameFormatRTPPayload,       /**< Frame Format is AMR Real-Time 
                                                   Transport Protocol Payload Format */ 
    OMX_AUDIO_AMRFrameFormatITU,              /**< Frame Format is ITU Format (added at Motorola request) */ 
    OMX_AUDIO_AMRWideBandPlusFrameFormat,     /**< 3GPP TS 26.290, clause 8.2 */
    OMX_AUDIO_AMRFrameFormatMax = 0x7FFFFFFF 
} OMX_AUDIO_AMREXT_FRAMEFORMATTYPE; 

typedef enum OMX_AUDIO_AMRDTXMODETYPE { 
    OMX_AUDIO_AMRDTXModeUsed = 0,  /**< DTX used or unused */ 
    OMX_AUDIO_AMRDTXModeOnVAD1,    /**< Use Type 1 VAD */ 
    OMX_AUDIO_AMRDTXModeOnVAD2,    /**< Use Type 2 VAD */
    OMX_AUDIO_AMRDTXModeOnAuto,    /**< VAD type automatic */
    OMX_AUDIO_AMRDTXModeAsEFR,     /**< DTX frames as EFR */
    OMX_AUDIO_AMRDTXModeMax = 0x7FFFFFFF 

 } OMX_AUDIO_AMRDTXMODETYPE; 



/** AMR band mode extension */
typedef enum OMX_AUDIO_AMREXT_BANDMODETYPE {
    OMX_AUDIO_AMRBandModeUnused = 0,          /**< AMRNB Mode unused / unknown */
    OMX_AUDIO_AMRBandModeNB0,                 /**< AMRNB Mode 0 =  4750 bps */
    OMX_AUDIO_AMRBandModeNB1,                 /**< AMRNB Mode 1 =  5150 bps */
    OMX_AUDIO_AMRBandModeNB2,                 /**< AMRNB Mode 2 =  5900 bps */ 
    OMX_AUDIO_AMRBandModeNB3,                 /**< AMRNB Mode 3 =  6700 bps */
    OMX_AUDIO_AMRBandModeNB4,                 /**< AMRNB Mode 4 =  7400 bps */
    OMX_AUDIO_AMRBandModeNB5,                 /**< AMRNB Mode 5 =  7950 bps */
    OMX_AUDIO_AMRBandModeNB6,                 /**< AMRNB Mode 6 = 10200 bps */
    OMX_AUDIO_AMRBandModeNB7,                 /**< AMRNB Mode 7 = 12200 bps */
    OMX_AUDIO_AMRBandModeWB0,                 /**< AMRWB Mode 0 =  6600 bps */
    OMX_AUDIO_AMRBandModeWB1,                 /**< AMRWB Mode 1 =  8850 bps */
    OMX_AUDIO_AMRBandModeWB2,                 /**< AMRWB Mode 2 = 12650 bps */ 
    OMX_AUDIO_AMRBandModeWB3,                 /**< AMRWB Mode 3 = 14250 bps */ 
    OMX_AUDIO_AMRBandModeWB4,                 /**< AMRWB Mode 4 = 15850 bps */
    OMX_AUDIO_AMRBandModeWB5,                 /**< AMRWB Mode 5 = 18250 bps */
    OMX_AUDIO_AMRBandModeWB6,                 /**< AMRWB Mode 6 = 19850 bps */
    OMX_AUDIO_AMRBandModeWB7,                 /**< AMRWB Mode 7 = 23050 bps */
    OMX_AUDIO_AMRBandModeWB8,                 /**< AMRWB Mode 8 = 23850 bps */      
    OMX_AUDIO_AMRBandModeWP0,                 /**< AMR-WB+ 13.6 kbps (mono, 16/24kHz output) */
    OMX_AUDIO_AMRBandModeWP1,                 /**< AMR-WB+ 18 kbps (stereo, 16/24kHz output) */
    OMX_AUDIO_AMRBandModeWP2,                 /**< AMR-WB+ 24 kbps (mono, 16/24kHz output) */
    OMX_AUDIO_AMRBandModeWP3,                 /**< AMR-WB+ 24 kbps (stereo, 16/24kHz output) */
    OMX_AUDIO_AMRBandModeWP4,                 /**< AMR-WB+ 10.4 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP5,                 /**< AMR-WB+ 12.0 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP6,                 /**< AMR-WB+ 13.6 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP7,                 /**< AMR-WB+ 15.2 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP8,                 /**< AMR-WB+ 16.8 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP9,                 /**< AMR-WB+ 19.2 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP10,                /**< AMR-WB+ 20.8 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP11,                /**< AMR-WB+ 24.0 kbps (mono) */
    OMX_AUDIO_AMRBandModeWP12,                /**< AMR-WB+ 12.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP13,                /**< AMR-WB+ 12.8 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP14,                /**< AMR-WB+ 14.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP15,                /**< AMR-WB+ 14.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP16,                /**< AMR-WB+ 15.2 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP17,                /**< AMR-WB+ 16.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP18,                /**< AMR-WB+ 16.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP19,                /**< AMR-WB+ 17.2 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP20,                /**< AMR-WB+ 18.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP21,                /**< AMR-WB+ 18.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP22,                /**< AMR-WB+ 19.2 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP23,                /**< AMR-WB+ 20.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP24,                /**< AMR-WB+ 20.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP25,                /**< AMR-WB+ 21.2 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP26,                /**< AMR-WB+ 22.4 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP27,                /**< AMR-WB+ 23.2 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP28,                /**< AMR-WB+ 24.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP29,                /**< AMR-WB+ 25.6 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP30,                /**< AMR-WB+ 26.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP31,                /**< AMR-WB+ 26.8 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP32,                /**< AMR-WB+ 28.8 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP33,                /**< AMR-WB+ 29.6 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP34,                /**< AMR-WB+ 30.0 kbps (stereo) */
    OMX_AUDIO_AMRBandModeWP35,                /**< AMR-WB+ 32.0 kbps (stereo) */
    
    OMX_AUDIO_AMRBandModeMax = 0x7FFFFFFF /**< 5.15 kbps */
} OMX_AUDIO_AMREXT_BANDMODETYPE;
     

/** AMR params extension */


typedef struct OMX_AUDIO_PARAM_AMREXT_TYPE {
    OMX_U32 nSize;                          /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;               /**< OMX specification version information */
    OMX_U32 nPortIndex;                     /**< port that this structure applies to */
    OMX_U32 nChannels;                      /**< Number of channels */
    OMX_U32 nBitRate;                       /**< Bit rate read only field */
    OMX_AUDIO_AMREXT_BANDMODETYPE eAMRBandMode; /**< AMR Band Mode enumeration */ 
    OMX_AUDIO_AMRDTXMODETYPE  eAMRDTXMode;  /**< AMR DTX Mode enumeration */
    OMX_AUDIO_AMREXT_FRAMEFORMATTYPE eAMRFrameFormat; /**< AMR frame format enumeration */
    OMX_U32 nAMRWideBandPlusISF;            /**< AMR-WB+ internal Sampling Frequency Factor expressed in percentage */
    OMX_BOOL bAMRWideBandPlusLC;            /**< Activates/deactivates AMR-WB+ low complexity Extended AMR Wide Band encoding mode */
    OMX_BOOL bAMRWideBandPlusLimiter        /**< Activates/deactivates the limiter option of the decoder */

} OMX_AUDIO_PARAM_AMREXT_TYPE;

/** End of AMR-WB+ related **/

/** WMA Pro related **/

/** WMA Pro params **/

typedef enum OMX_AUDIO_WMAPROFORMATTYPE {
    OMX_AUDIO_WMAPROFormatUnused = 0,          /**< AMRNB Mode unused / unknown */
    OMX_AUDIO_WMAPROFormat9,           
    OMX_AUDIO_WMAPROFormat10,
    OMX_AUDIO_WMAPROFormatMax = 0x7FFFFFFF    
} OMX_AUDIO_WMAPROFORMATTYPE;

typedef enum OMX_AUDIO_WMAPROPROFILETYPE {
    OMX_AUDIO_WMAPROProfileUnused = 0,          /**< AMRNB Mode unused / unknown */
    OMX_AUDIO_WMAPROProfileM0,
    OMX_AUDIO_WMAPROProfileM1,
    OMX_AUDIO_WMAPROProfileM2,
    OMX_AUDIO_WMAPROProfileM3,               
    OMX_AUDIO_WMAPROProfileMax = 0x7FFFFFFF
} OMX_AUDIO_WMAPROPROFILETYPE;
    
typedef struct OMX_AUDIO_PARAM_WMAPROTYPE {
		OMX_U32 nSize;
		OMX_VERSIONTYPE nVersion;
		OMX_U32 nPortIndex;
		OMX_U16 nChannels;
		OMX_U32 nBitRate;
		OMX_AUDIO_WMAPROFORMATTYPE eFormat;
		OMX_AUDIO_WMAPROPROFILETYPE eProfile;
		OMX_U32 nSamplingRate;
		OMX_U32 nBlockAlign;
		OMX_U32 nSuperBlockAlign;
		OMX_U32 nEncodeOptions;
		OMX_U32 nAdvancedEncodeOptions;
		OMX_U32 nAdvancedEncodeOptions2;
		OMX_U32 nChannelMask;
} OMX_AUDIO_PARAM_WMAPROTYPE;

/** End of WMA Pro related **/

/** iLBC related **/
typedef struct OMX_AUDIO_PARAM_ILBCTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_U32 nFrameLength;
     OMX_BOOL bIsDTXCNGSupported;
     OMX_BOOL bDTXCNGSelected;                       
     OMX_BOOL bPLCSelected;                                                                       
 } OMX_AUDIO_PARAM_ILBCTYPE;

/** End of iLBC related **/

/** G711 related **/
typedef struct OMX_AUDIO_PARAM_G711TYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex; 
     OMX_BOOL bIsDTXCNGSupported;
     OMX_BOOL bIsPLCSupported;       
     OMX_BOOL bDTXCNGEnabled;           
     OMX_BOOL bPLCEnabled;
     OMX_U32  nFrameLength;                                                                     
 } OMX_AUDIO_PARAM_G711TYPE;

/** End of G711 related **/


/** End of Dummy component **/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif