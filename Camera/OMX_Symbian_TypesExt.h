/*
  OMX_CameraTypesExt.h
  
  Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.
*/

/** @file
@brief Symbian OpenMAX IL Extension Data Structures for the Generic Types.

This file contains the extension structures for the Symbian IL extensions of the
Types.

@publishedDeviceAbstraction
*/

#ifndef OMX_CameraTypesExt_h
#define OMX_CameraTypesExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header must include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully 
 */
#include <OMX_Types.h>


#define OMX_MAX_NUMBER_OF_ROIS 10


/** @name Point type extension */

/*@{*/

/** Point extension type.
*/

typedef struct OMX_POINTTYPE {
    OMX_S32 nX; 
    OMX_S32 nY;
} OMX_POINTTYPE;

/** Size extension type.
*/

typedef struct OMX_SIZETYPE {
    OMX_S32 nWidth;
    OMX_S32 nHeight;
} OMX_SIZETYPE;

/** Rectangular extension type.

There exist also a rectangular config defined in the OMX IL standard.
The purpose of this addition is to provide a generic rectangular type to 
be used by other configs and params.
*/

typedef struct OMX_RECTTYPE {
    OMX_POINTTYPE sTopLeft;
    OMX_SIZETYPE sSize;    
} OMX_RECTTYPE;

/** Relative rectangular extension type.
*/

typedef struct OMX_RELATIVERECTTYPE {
    OMX_RECTTYPE sRect;
    OMX_SIZETYPE sReference;
} OMX_RELATIVERECTTYPE;

/** Tracking object type classification.
*/

typedef enum OMX_OBJECTTYPE {
    OMX_ObjectTypeFace,
    OMX_ObjectTypeObject
} OMX_OBJECTTYPE;

/** 32 Integer Config Generic OMX struct.
*/

typedef struct OMX_CONFIG_S32INTTYPE { 
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_U32 nPortIndex; 
OMX_S32 nS32; 
} OMX_CONFIG_S32INTTYPE; 

/** Bool Config Generic OMX struct.
*/

typedef struct OMX_CONFIG_PORT_BOOLEANTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnabled;    
} OMX_CONFIG_PORT_BOOLEANTYPE; 

/** Unsigned 32 bit Integer Config Generic OMX struct.
*/
typedef struct OMX_CONFIG_UINTEGERTYPE {
    OMX_U32 nSize; 
    OMX_VERSIONTYPE nVersion; 
    OMX_U32 nPortIndex;
    OMX_U32 nNumber;
} OMX_CONFIG_UINTEGERTYPE; 


/*@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_CameraTypesExt_h */
