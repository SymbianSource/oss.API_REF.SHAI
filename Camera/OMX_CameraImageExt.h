/*
  OMX_CameraImageExt.h
  
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
@brief Symbian OpenMAX IL Extension Data Structures in the Image Domain.

This file contains the extension structures for the Symbian IL extensions that
pertain to imaaging components.

@publishedDeviceAbstraction
*/

#ifndef OMX_CameraImageExt_h
#define OMX_CameraImageExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header must include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully 
 */
#include <OMX_Types.h>
#include <OMX_CameraTypesExt.h>
#include <OMX_Image.h>

/** 
 * Enumeration of possible image orientation types 
 */

typedef enum OMX_IMAGE_ORIENTATIONORIGINTYPE
{
	OMX_IMAGE_ORIENTATION_NOT_SPECIFIED =0x0,
	OMX_IMAGE_ORIENTATION_ROWTOP_COLUMNLEFT,
	OMX_IMAGE_ORIENTATION_ROWTOP_COLUMNRIGHT,
	OMX_IMAGE_ORIENTATION_ROWBOTTOM_COLUMNRIGHT,
	OMX_IMAGE_ORIENTATION_ROWBOTTOM_COLUMNLEFT,
	OMX_IMAGE_ORIENTATION_ROWLEFT_COLUMNTOP,
	OMX_IMAGE_ORIENTATION_ROWRIGHT_COLUMNTOP,
	OMX_IMAGE_ORIENTATION_ROWRIGHT_COLUMNBOTTOM,
	OMX_IMAGE_ORIENTATION_ROWLEFT_COLUMNBOTTOM
} OMX_IMAGE_ORIENTATIONORIGINTYPE;

/** 
 * Enumeration of possible focus region types 
 */
typedef enum OMX_FOCUSREGIONCONTROL {
    OMX_FocusRegionAuto,
    OMX_FocusRegionManual,
    OMX_FocusRegionFacePriority,
    OMX_FocusRegionObjectPriority
} OMX_FOCUSREGIONCONTROL;

/** 
 * Enumeration of possible xenon flash status values 
 */
typedef enum OMX_XENONFLASHSTATUS
{
	OMX_XENON_FLASH_NONE 	= 0x00000000,
	OMX_XENON_FLASH_DISCHARGED,
	OMX_XENON_FLASH_CHARGING,
	OMX_XENON_FLASH_READY,
	OMX_XENON_FLASH_NOTAVAILABLE
} OMX_XENONFLASHSTATUS;

/** 
 * Enumeration of possible capture exposure time values 
 */
typedef enum OMX_CAPTUREEXPOSURETIME
{
	OMX_CAPTURE_EXPOSURE_NONE_OR_ONGOING =0x0,
	OMX_CAPTURE_EXPOSURE_NORMAL,
	OMX_CAPTURE_EXPOSURE_SHORT,
	OMX_CAPTURE_EXPOSURE_LONG
} OMX_CAPTUREEXPOSURETIME;

/** 
 * Enumeration of possible bracket mode values 
 */
typedef enum OMX_BRACKETMODETYPE {
	OMX_BracketExposureRelativeInEV,
	OMX_BracketExposureAbsoluteMs,
	OMX_BracketFocusRelative,
	OMX_BracketFocusAbsolute,
	OMX_BracketFlashPower,
	OMX_BracketAperture,    
} OMX_BRACKETMODETYPE;

/** 
 * Enumeration of possible levels of RAW processing 
 */
typedef enum OMX_RAWPRESETTYPE {
    OMX_RawUnprocessed,
    OMX_RawProcessed
} OMX_RAWPRESETTYPE;

/** 
 * Extension of Focus Control
 */

enum {
	OMX_Image_FocusControlIdle = OMX_IMAGE_FocusControlVendorStartUnused + 0x01,
};

/** 
 * Extension of Flash Control
 */

enum {
	OMX_Image_FlashControlSlowFrontSync = OMX_IMAGE_FlashControlVendorStartUnused + 0x01,
	OMX_Image_FlashControlSlowRearSync
};


/** Orientation Configuration.

The OMX_IMAGE_CONFIG_ORIENTATIONTYPE structure is used to set or query
the orientation of camera sensor relative to captured scene. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.Orientation".
*/


typedef struct OMX_IMAGE_CONFIG_ORIENTATIONTYPE {
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_IMAGE_ORIENTATIONORIGINTYPE eOrientation;
} OMX_IMAGE_CONFIG_ORIENTATIONTYPE;

/** Image Parameters Lock.

The OMX_IMAGE_CONFIG_LOCKTYPE structure is used to set or query
the freezing of settings during capture. 
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.Lock".
*/

typedef struct OMX_IMAGE_CONFIG_LOCKTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bLock;
    OMX_BOOL bAtCapture;
} OMX_IMAGE_CONFIG_LOCKTYPE;

/** Image Flash Control Config.

The OMX_IMAGE_CONFIG_FLASHCONTROLTYPE structure is used to set or query
the flash mode to be used during capture.
An extension is needed because flash is a feature that may need changing while
camera is executing, so it is a config.
The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.FlashControl".
*/

typedef struct OMX_IMAGE_CONFIG_FLASHCONTROLTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_IMAGE_FLASHCONTROLTYPE eFlashControl;
}OMX_IMAGE_CONFIG_FLASHCONTROLTYPE;

/** Focus Region Control Config.

The OMX_IMAGE_CONFIG_FOCUSREGIONTYPE structure is used to set or query
the focus regions to be used. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.FocusRegion".
*/

typedef struct OMX_IMAGE_CONFIG_FOCUSREGIONTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_FOCUSREGIONCONTROL eFocusRegionControl;
    OMX_RELATIVERECTTYPE sFocusRegion;
} OMX_IMAGE_CONFIG_FOCUSREGIONTYPE;

/** Image Regions Of Interests ROIs Control Config.

The OMX_IMAGE_CONFIG_FOCUSREGIONTYPE structure is used to set or query
the regions of interests of image frames. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.ROI".
*/

typedef struct OMX_IMAGE_CONFIG_ROITYPE {    
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nNumberOfROIs;
    OMX_RELATIVERECTTYPE sROIs[OMX_MAX_NUMBER_OF_ROIS];
    OMX_U32 nPriority[OMX_MAX_NUMBER_OF_ROIS];
    OMX_OBJECTTYPE eObjectType;
} OMX_IMAGE_CONFIG_ROITYPE; 

/** Xenon flash status Config.

The OMX_IMAGE_CONFIG_XENONFLASHSTATUSTYPE structure is used to query
the xenon flash status. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.XenonFlashStatus".
*/


typedef struct OMX_IMAGE_CONFIG_XENONFLASHSTATUSTYPE { 
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_U32 nPortIndex;
OMX_XENONFLASHSTATUS eFlashStatus;
} OMX_IMAGE_CONFIG_XENONFLASHSTATUSTYPE;

/** Capture Exposure Time Config.

The OMX_IMAGE_CONFIG_CAPTUREEXPOSURETIMETYPE structure is used to set or query
the type of capture exposure time values. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.CaptureExposureTime".
*/


typedef struct OMX_IMAGE_CONFIG_CAPTUREEXPOSURETIMETYPE {
OMX_U32 nSize; 
OMX_VERSIONTYPE nVersion; 
OMX_U32 nPortIndex;
OMX_CAPTUREEXPOSURETIME eExposureTime;
} OMX_IMAGE_CONFIG_CAPTUREEXPOSURETIMETYPE;

/** Bracketing Config.

The OMX_IMAGE_CONFIG_BRACKETINGTYPE structure is used to set or query
the bracketing settings. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.Bracketing".
*/

typedef struct OMX_IMAGE_CONFIG_BRACKETINGTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BRACKETMODETYPE eBracketMode;
    OMX_U32 nNbrBracketingValues;
    OMX_U32 nBracketValues[5];
} OMX_IMAGE_CONFIG_BRACKETINGTYPE;

/** RAW Preset Config.

The OMX_IMAGE_CONFIG_RAWPRESETTYPE structure is used to set or query
the RAW type of images. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.RawPreset".
*/

typedef struct OMX_IMAGE_CONFIG_RAWPRESETTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_RAWPRESETTYPE ePreset;
} OMX_IMAGE_CONFIG_RAWPRESETTYPE;

/** GPS Location Config.

The OMX_IMAGE_CONFIG_GPSLOCATIONTYPE structure is used to set or query
the GPS Location Data for usage when capturing. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Config.Image.GPSLocation".
*/

typedef struct OMX_IMAGE_CONFIG_GPSLOCATIONTYPE {    
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U64 nLatitudeDegrees;
    OMX_U64 nLatitudeMinutes;
    OMX_U64 nLatitudeSeconds;
    OMX_U64 nLongitudeDegrees;
    OMX_U64 nLongitudeMinutes;
    OMX_U64 nLongitudeSeconds;
    OMX_U64 nAltitudeMetters;
    OMX_BOOL bLatitudeRefNorth;
    OMX_BOOL bLongitudeRefEast;
    OMX_BOOL bAltitudeRefAboveSea;
    OMX_BOOL bLocationKnown;  
} OMX_IMAGE_CONFIG_GPSLOCATIONTYPE;

/** Image Filename Param.

The OMX_IMAGE_PARAM_IW_FILENAMEFORMAT structure is used to set or query
the GPS Location Data for usage when capturing. The setting can be changed using
the OMX_SetParam() function, and the current state can be queried using 
the OMX_GetParam() function. When calling either function, the index 
specified for this structure is retrieved using OMX_GetExtensionIndex()
with the extension string "OMX.Index.Param.Image.FilenameFormat".
*/

typedef struct OMX_IMAGE_PARAM_IW_FILENAMEFORMAT {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nFileSequenceNumber;
    OMX_BOOL bGenerateFileInSequence;
}OMX_IMAGE_PARAM_IW_FILENAMEFORMAT;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_CameraImageExt_h */
