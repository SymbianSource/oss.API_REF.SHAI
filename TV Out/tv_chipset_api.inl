/*
  tv_chipset_api.inl

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

/** @file

Inline methods of tv chipset driver API

@publishedDeviceAbstraction
*/

/*- Include Files  ----------------------------------------------------------*/

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Error codes */
typedef enum  
    {
    /* VERSION */
    DISP_FUNC_DISP_TVAPI_VERSION = 0,

    /* CAPABILITY */
    DISP_FUNC_DISP_GET_TV_CAPABILITIES,
    DISP_FUNC_DISP_GET_SUPPORTED_HDMI_MODE,

    /* CONTROL */
    DISP_FUNC_DISP_SET_TV_CONFIG,
    DISP_FUNC_DISP_RESOLUTION_QUERY,
    DISP_FUNC_DISP_ENABLE_TV_OUT,
    DISP_FUNC_DISP_DISABLE_TV_OUT,
    DISP_FUNC_DISP_IS_TV_OUT_ENABLED,
    DISP_FUNC_DISP_TV_MESSAGE,

    /* LISTENERS AND COPY PROTECTION */
    DISP_FUNC_DISP_CABLE_LISTENER,
    DISP_FUNC_DISP_COPY_PROTECTION_STATUS,
    DISP_FUNC_DISP_COPY_PROTECTION_STATUS_LISTENER,
    DISP_FUNC_DISP_SET_SRM,
    DISP_FUNC_DISP_SET_HDCP_KEY,

    /* CONTENT UPDATE */
    DISP_FUNC_DISP_SET_TV_FINAL_VIEW,
    DISP_FUNC_DISP_TV_FLUSH,

    /* Size of array */
    DISP_FUNC_TV_SIZE_OF_ARRAY,
    } DISPE_TV_FUNCTIONS;

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/*- Functions ---------------------------------------------------------------*/

/*== VERSION ================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline uint32 dispTvApiVersion(API_POINTER api)
    {

    typedef uint32 (*FUNC)();
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_TVAPI_VERSION ];
    return function();

    }

/*== CAPABILITY =============================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispGetTvCapabilities(API_POINTER api, DISPS_TV_CAPABILITIES* tvCapabilities)
    {

    typedef DISPE_ERROR (*FUNC)(DISPS_TV_CAPABILITIES* tvCapabilities);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_GET_TV_CAPABILITIES ];
    return function( tvCapabilities );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispGetSupportedHdmiMode(API_POINTER api, uint32 capabilityNumber, DISPS_SUPPORTED_HDMI_MODE* readMode)
    {

    typedef DISPE_ERROR (*FUNC)(uint32 capabilityNumber, DISPS_SUPPORTED_HDMI_MODE* readMode);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_GET_SUPPORTED_HDMI_MODE ];
    return function( capabilityNumber, readMode );

    }

/*== CONTROL ================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetTvConfig(API_POINTER api, const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*FUNC)(const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPT_READY_CB callback);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_SET_TV_CONFIG ];
    return function( tvSettings, callback );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispResolutionQuery(API_POINTER api, const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPS_TV_RESOLUTION* resolution)
    {

    typedef DISPE_ERROR (*FUNC)(const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPS_TV_RESOLUTION* resolution);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_RESOLUTION_QUERY ];
    return function( tvSettings, resolution );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispEnableTvOut(API_POINTER api, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*FUNC)(DISPT_READY_CB callback);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_ENABLE_TV_OUT ];
    return function( callback );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispDisableTvOut(API_POINTER api, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*FUNC)(DISPT_READY_CB callback);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_DISABLE_TV_OUT ];
    return function( callback );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline bool8 dispIsTvOutEnabled(API_POINTER api)
    {

    typedef bool8 (*FUNC)();
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_IS_TV_OUT_ENABLED ];
    return function();

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispTvMessage(API_POINTER api, CHIPSET_DRV_NAME receiver, DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback)
    {

    typedef DISPE_ERROR (*FUNC)(CHIPSET_DRV_NAME receiver, DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_TV_MESSAGE ];
    return function( receiver, message, param, callback );

    }

/*== LISTENERS AND COPY PROTECTION ==========================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCableListener(API_POINTER api, DISPF_LISTENER_CB callback, bool8 add)
    {

    typedef DISPE_ERROR (*FUNC)(DISPF_LISTENER_CB callback, bool8 add);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_CABLE_LISTENER ];
    return function( callback, add );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline bool8 dispCopyProtectionStatus(API_POINTER api)
    {

    typedef bool8 (*FUNC)();
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_COPY_PROTECTION_STATUS ];
    return function();

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCopyProtectionStatusListener(API_POINTER api, DISPF_LISTENER_CB copyProtectionChangedCb, bool8 add)
    {

    typedef DISPE_ERROR (*FUNC)(DISPF_LISTENER_CB copyProtectionChangedCb, bool8 add);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_COPY_PROTECTION_STATUS_LISTENER ];
    return function( copyProtectionChangedCb, add );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetSrm(API_POINTER api, void* srmData, uint32 srmInBytes)
    {

    typedef DISPE_ERROR (*FUNC)(void* srmData, uint32 srmInBytes);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_SET_SRM ];
    return function( srmData, srmInBytes );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetHdcpKey(API_POINTER api, void* hdcpData, uint32 hdcpInBytes)
    {

    typedef DISPE_ERROR (*FUNC)(void* hdcpData, uint32 hdcpInBytes);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_SET_HDCP_KEY ];
    return function( hdcpData, hdcpInBytes );

    }

/*== CONTENT UPDATE =========================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetTvFinalView(API_POINTER api, const DISPS_FINAL_VIEW* finalView)
    {

    typedef DISPE_ERROR (*FUNC)(const DISPS_FINAL_VIEW* finalView);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_SET_TV_FINAL_VIEW ];
    return function( finalView );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispTvFlush(API_POINTER api, const DISPS_UPDATE* changedArea, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*FUNC)(const DISPS_UPDATE* changedArea, DISPT_READY_CB callback);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_TV_FLUSH ];
    return function( changedArea, callback );

    }

/* End of File */

