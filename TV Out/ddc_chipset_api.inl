/*
  ddc_chipset_api.inl

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

Inline methods of ddc chipset driver API

@publishedDeviceAbstraction
*/

/*- Include Files  ----------------------------------------------------------*/

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Error codes */
typedef enum  
    {
    /* VERSION */
    DISP_FUNC_DISP_DDC_API_VERSION = 0,

    /* ACCESS */
    DISP_FUNC_DISP_DDC_READ,

    /* Size of array */
    DISP_FUNC_DDC_SIZE_OF_ARRAY,
    } DISPE_DDC_FUNCTIONS;

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/*- Functions ---------------------------------------------------------------*/

/*== VERSION ================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline uint32 dispDdcApiVersion(API_POINTER api)
    {

    typedef uint32 (*FUNC)();
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_DDC_API_VERSION ];
    return function();

    }

/*== ACCESS =================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispDdcRead(API_POINTER api, uint8 ddcPortAddress, uint32 blockNumber,
                               DISPA_DDC_DATA_BLOCK* dataBlock, DISPT_READY_CB callbackWhenRead)
    {

    typedef DISPE_ERROR (*FUNC)(uint8 ddcPortAddress, uint32 blockNumber,
                                DISPA_DDC_DATA_BLOCK* dataBlock, DISPT_READY_CB callbackWhenRead);
    FUNC function = ( FUNC ) api[ DISP_FUNC_DISP_DDC_READ ];
    return function( ddcPortAddress, blockNumber, dataBlock, callbackWhenRead );

    }

/* End of File */

