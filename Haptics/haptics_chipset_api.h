/*
  haptics_chipset_api.h

  Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/

#ifndef HAPTICS_CHIPSET_API_H
#define HAPTICS_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 *  header to compile without errors.  The includes below are required
 *  for this header file to compile successfully 
 */

#include <OMX_Audio.h>

typedef struct OMX_AUDIO_PARAM_HAPTICSDRIVERPROPERTIESTYPE 
	{
    OMX_U32 nSize;	
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nNativeSamplingRate;
    OMX_U32 nHapticsDriverNominalVoltage;    
    OMX_U32 nHapticsDriverImpedance;		 
	} OMX_AUDIO_PARAM_HAPTICSDRIVERPROPERTIESTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif