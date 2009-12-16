/*
  OMX_CameraIVCommonExt.h
  
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
@brief Symbian OpenMAX IL Extension Data Structures Common for Imaging and Video.

This file contains the extension structures for the Symbian IL extensions that
are common to Imaging and Video domains.

@publishedDeviceAbstraction
*/

#ifndef OMX_CameraIVCommonExt_h
#define OMX_CameraIVCommonExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header must include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully 
 */
#include <OMX_Types.h>
#include <OMX_IVCommon.h>


/** Color format extensions. */
typedef enum OMX_EXTCOLORFORMATTYPE {
    OMX_COLOR_FormatYUV420MBPackedSemiPlanar = OMX_COLOR_FormatVendorStartUnused + 0x1
} OMX_EXTCOLORFORMATTYPE;

/** Primary color enumeration. */
typedef enum OMX_COLORPRIMARYTYPE {
    OMX_ColorPrimaryFullRange,
    OMX_ColorPrimaryBT601,
    OMX_ColorPrimaryBT709,
    OMX_ColorMax = 0x7FFFFFFF
} OMX_COLORPRIMARYTYPE;


/** High level control type classification.
*/

typedef enum OMX_HIGHLEVELCONTROLTYPE {
    OMX_HighLevelControlOff,
    OMX_HighLevelControlOn,
    OMX_HighLevelControlAuto
} OMX_HIGHLEVELCONTROLTYPE;

/** 
 * Enumeration of possible focus ranges 
 */

typedef enum OMX_IMAGE_FOCUSRANGETYPE {
OMX_IMAGE_FocusRangeAuto, 
OMX_IMAGE_FocusRangeHyperfocal,
OMX_IMAGE_FocusRangeSuperMacro,
OMX_IMAGE_FocusRangeMacro,
OMX_IMAGE_FocusRangeInfinity,
} OMX_IMAGE_FOCUSRANGETYPE;

/** 
 * Enumeration of possible flicker removal values 
 */

typedef enum OMX_COMMONFLICKERREMOVALTYPE {
OMX_FlickerRemovalOff, 
OMX_FlickerRemovalAuto,
OMX_FlickerRemoval50,
OMX_FlickerRemoval60,
} OMX_COMMONFLICKERREMOVALTYPE;

/** 
 * Enumeration of possible power versus image quality choices
 */

typedef enum OMX_IMAGE_QHINTTYPE {
    OMX_IMAGE_QNotSpecified = 0,
    OMX_IMAGE_QLow,//low power mode
    OMX_IMAGE_QBalanced,
    OMX_IMAGE_QHigh
} OMX_IMAGE_QHINTTYPE;

/** 
 * Enumeration of possible depth of field choices
 */

typedef enum OMX_IMAGE_DOFHINTTYPE {
    OMX_IMAGE_DoFNotSpecified = 0,
    OMX_IMAGE_DoFSmall,
    OMX_IMAGE_DoFMedium,
    OMX_IMAGE_DoFLarge
} OMX_IMAGE_DOFHINTTYPE;

/** 
 * Enumeration of possible rotation angles
 */

typedef enum OMX_ROTATIONANGLETYPE {
    OMX_CW_0 = 0,
    OMX_CW_90,
    OMX_CW_180,
    OMX_CW_270
} OMX_ROTATIONANGLETYPE;

/** 
 * Enumeration of possible rotation types for metadata
 */

typedef enum OMX_METADATAROTATIONTYPE {
    OMX_MetadataRotationNone,
    OMX_MetadataRotationScene,
    OMX_MetadataRotationUI
} OMX_METADATAROTATIONTYPE;

/** 
 * Extension of Exposure Control
 */

enum {
	OMX_ExposureControlExtensionCenter = OMX_ExposureControlVendorStartUnused + 0x02,
	OMX_ExposureControlExtensionVeryLong
};


/** 
 * Extension of Image Filter
 */

enum {
	OMX_ImageFilterSepia = OMX_ImageFilterVendorStartUnused + 0x01,
	OMX_ImageFilterGrayScale,
	OMX_ImageFilterNatural,
	OMX_ImageFilterVivid
};

/** YUV data color range.

The index specified for this structure is retrieved using 
OMX_GetExtensionIndex() with the extension string 
"OMX.Index.Param.Common.ColorPrimary".
*/
typedef struct OMX_PARAM_COLORPRIMARYTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_COLORPRIMARYTYPE eColorPrimary;
} OMX_PARAM_COLORPRIMARYTYPE;


/** Pixel Aspect Ratio.

The index specified for this structure is retrieved using 
OMX_GetExtensionIndex() with the extension string 
"OMX.Index.Param.Common.PixelAspectRatio".
*/
typedef struct OMX_PARAM_PIXELASPECTRATIOTYPE
{
    OMX_U32 nSize;              /**< Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /**< OMX specification version information */
    OMX_U32 nPortIndex;         /**< Port that this structure applies to */
    OMX_U8 nHorizontal;         /**< Width of pixel. nHorizontal is 4 is For 4:3 PAR */
    OMX_U8 nVertical;           /**< Height of pixel. nVertical is 3 is For 4:3 PAR */
    OMX_TICKS nTimestamp;       /**< Time when PAR change should happen */
} OMX_PARAM_PIXELASPECTRATIOTYPE;

/** High Level Control.
The OMX_CONFIG_HIGHLEVELCONTROLTYPE structure is used to set or query
the used control level of a setting. 
The index specified for this structure is retrieved using 
OMX_GetExtensionIndex() with the extension string 
"OMX.Index.Config.Common.HighLevelControl".
*/
typedef struct OMX_CONFIG_HIGHLEVELCONTROLTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_HIGHLEVELCONTROLTYPE eControl;
} OMX_CONFIG_HIGHLEVELCONTROLTYPE;


/** Zoom Factor.
The OMX_CONFIG_ZOOMFACTORTYPE structure is used to set or query
the used zoom value. The index specified for this structure is 
retrieved using OMX_GetExtensionIndex() with the extension string 
"OMX.Index.Config.Common.ZoomFactor".
*/

typedef struct OMX_CONFIG_ZOOMFACTORTYPE { 
  OMX_U32 nSize; 
  OMX_VERSIONTYPE nVersion; 
  OMX_U32 nPortIndex; 
  OMX_S32 xZoomFieldOfView; 
}OMX_CONFIG_ZOOMFACTORTYPE;

/** Focus Range.

The OMX_CONFIG_FOCUSRANGETYPE structure is used to set or query
the used range of focus when focusing. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.FocusRange".
*/

typedef struct OMX_CONFIG_FOCUSRANGETYPE {
OMX_U32 nSize;
OMX_VERSIONTYPE nVersion;
OMX_U32 nPortIndex;
OMX_IMAGE_FOCUSRANGETYPE eFocusRange;
} OMX_CONFIG_FOCUSRANGETYPE;

/** Focus Status.

The OMX_CONFIG_EXTFOCUSSTATUSTYPE structure is used to query
the current status of focusing process. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.FocusStatus".
*/

typedef struct OMX_CONFIG_EXTFOCUSSTATUSTYPE { 
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_FOCUSSTATUSTYPE eFocusStatus;
} OMX_CONFIG_EXTFOCUSSTATUSTYPE;

/** Flicker Removal.

The OMX_CONFIG_FLICKERREMOVAL structure is used to set or query
the flicker removal setting. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.FlickerRemoval".
*/

typedef struct OMX_CONFIG_FLICKERREMOVALTYPE {
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_U32 nPortIndex;
OMX_COMMONFLICKERREMOVALTYPE eFlickerRemoval;
}OMX_CONFIG_FLICKERREMOVALTYPE;

/** Power versus quality hint provided by IL client to implementation.

The OMX_PARAM_HINTPQTYPE structure is used to set or query
the IL client choice of importance: power savings or quality. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Param.Common.HintPQ".
*/

typedef struct OMX_PARAM_HINTPQTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_IMAGE_QHINTTYPE eQHint;
} OMX_PARAM_HINTPQTYPE;

/** Depth of field hint provided by IL client to implementation.

The OMX_PARAM_HINTDOFTYPE structure is used to set or query
the IL client choice for depth of field. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Param.Common.HintDOF".
*/

typedef struct  OMX_PARAM_HINTDOFTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_IMAGE_DOFHINTTYPE eDoFHint;
} OMX_PARAM_HINTDOFTYPE;

/** HW information retrieval struct.

The OMX_PARAM_HWINFOTYPE structure is used to query
the sensor (HW) information details. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.HWInfo".
*/

typedef struct OMX_CONFIG_HWINFOTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nVersion1;
    OMX_U32 nVersion2;
    OMX_STRING cInfoString;
} OMX_CONFIG_HWINFOTYPE;

/** Motion information retrieval struct.

The OMX_CONFIG_MOTIONLEVELTYPE structure is used to query the motion 
information details obtained by component from a stream of input images. 

The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.MotionLevel".
*/

typedef struct OMX_CONFIG_MOTIONLEVELTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion; 
    OMX_U32 nPortIndex;
    OMX_U32 nMotionLevel;
}OMX_CONFIG_MOTIONLEVELTYPE;

/** Capturing bit extension.

Capturing bit is extended to be different on different ports to trigger 
parallel capturing on those ports.

The OMX_CONFIG_CAPTURINGTYPE structure is used to set or query
the capturing bit. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.Capturing".
*/

typedef struct OMX_CONFIG_CAPTURINGTYPE {
OMX_U32 nSize;
OMX_VERSIONTYPE nVersion;
OMX_U32 nPortIndex;
OMX_BOOL bEnabled;    
} OMX_CONFIG_CAPTURINGTYPE;

/** Capture mode extension.

Capture mode is extended to allow additional capture modes.

The OMX_CONFIG_EXTCAPTUREMODETYPE structure is used to set/query
extended capture modes. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.ExtCaptureMode".
*/

typedef struct OMX_CONFIG_EXTCAPTUREMODETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nFrameBefore;
    OMX_BOOL bPrepareCapture;
    OMX_BOOL bEnableBracketing;
}OMX_CONFIG_EXTCAPTUREMODETYPE;

/** Rotation extension.

Rotation capabilities to allow implementing rotation wherever possible 
and more efficient.

The OMX_CONFIG_EXTENDEDROTATETYPE structure is used to set or query
the rotation details. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Common.ExtendedRotate".
*/

typedef struct OMX_CONFIG_EXTENDEDROTATETYPE { 
    OMX_U32 nSize; 
    OMX_VERSIONTYPE nVersion; 
    OMX_U32 nPortIndex;
    OMX_ROTATIONANGLETYPE eRot;
    OMX_METADATAROTATIONTYPE eMeta;	
} OMX_CONFIG_EXTENDEDROTATETYPE;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_CameraIVCommonExt_h */
