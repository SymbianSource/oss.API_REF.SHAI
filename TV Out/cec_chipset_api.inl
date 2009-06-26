/*
  cec_chipset_api.inl

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

Inline methods of cec chipset driver API

@publishedDeviceAbstraction
*/

/*- Include Files  ----------------------------------------------------------*/

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Error codes */
typedef enum  
    {
    /* VERSION */
    DISP_FUNC_DISP_CEC_API_VERSION = 0,

    /* CONTROL */
    DISP_FUNC_DISP_SET_LOGICAL_ADDRESS,
    DISP_FUNC_DISP_CEC_TRANSMIT,
    DISP_FUNC_DISP_CEC_READ,

    /* Size of array */
    DISP_FUNC_CEC_SIZE_OF_ARRAY,
    } DISPE_CEC_FUNCTIONS;

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/*- Functions ---------------------------------------------------------------*/

/*== VERSION ================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline uint32 dispCecApiVersion(API_POINTER api)
    {

    typedef uint32 (*FUNC)();
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_CEC_API_VERSION ];
    return function();

    }

/*== CONTROL ================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetLogicalAddress(API_POINTER api, DISPE_CEC_LOGICAL_ADDR ownLogicalAddress)
    {

    typedef DISPE_ERROR (*FUNC)(DISPE_CEC_LOGICAL_ADDR ownLogicalAddress);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_SET_LOGICAL_ADDRESS ];
    return function( ownLogicalAddress );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCecTransmit(API_POINTER api, const DISPS_CEC_FRAME* frame, DISPT_READY_CB callbackWhenTransmitted)
    {

    typedef DISPE_ERROR (*FUNC)(const DISPS_CEC_FRAME* frame, DISPT_READY_CB callbackWhenTransmitted);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_CEC_TRANSMIT ];
    return function( frame, callbackWhenTransmitted );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCecRead(API_POINTER api, DISPS_CEC_FRAME* readFrame, bool8 monitorAll, DISPT_READY_CB callbackWhenRead)
    {

    typedef DISPE_ERROR (*FUNC)(DISPS_CEC_FRAME* readFrame, bool8 monitorAll, DISPT_READY_CB callbackWhenRead);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_CEC_READ ];
    return function( readFrame, monitorAll, callbackWhenRead );

    }

/* End of File */

