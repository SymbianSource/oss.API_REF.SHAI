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


/** WMA param **/

typedef struct OMX_AUDIO_PARAM_WMAAVGBYTESTYPE { 
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_U32 nPortIndex;  
OMX_U32 nAvgBytesPerSec;
} OMX_AUDIO_PARAM_WMAAVGBYTESTYPE;

/** End of WMA related **/

/** WMA Pro params **/

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
		OMX_AUDIO_WMAPROPROFILETYPE eProfile;
		OMX_U32 nSamplingRate;
		OMX_U32 nBlockAlign;
		OMX_U32 nSuperBlockAlign;
		OMX_U32 nEncodeOptions;
		OMX_U32 nAdvancedEncodeOptions;
		OMX_U32 nAdvancedEncodeOptions2;
		OMX_U32 nChannelMask;
		OMX_U32 nSourceBitsPerSample;
} OMX_AUDIO_PARAM_WMAPROTYPE;

/** End of WMA Pro related **/

typedef struct OMX_AUDIO_CONFIG_AMRMODETYPE {
		OMX_U32 nSize;
		OMX_VERSIONTYPE nVersion;
		OMX_U32 nPortIndex;
		OMX_U32 nBitRate;
		OMX_AUDIO_AMRBANDMODETYPE eAMRBandMode;
} OMX_AUDIO_CONFIG_AMRMODETYPE;

typedef struct OMX_AUDIO_CONFIG_ILBCFRAMETYPE {
		OMX_U32 nSize;
		OMX_VERSIONTYPE nVersion;
		OMX_U32 nPortIndex;
		OMX_U32 nFrameLength; 
} OMX_AUDIO_CONFIG_ILBCFRAMETYPE;

/** SBC codec related **/
typedef struct OMX_AUDIO_CONFIG_SBCBITPOOLTYPE {
	  OMX_U32 nSize;
	  OMX_VERSIONTYPE nVersion;
	  OMX_U32 nPortIndex;
	  OMX_U32 nNewBitPool; 
} OMX_AUDIO_CONFIG_SBCBITPOOLTYPE;

/** End of SBC codec related **/

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif