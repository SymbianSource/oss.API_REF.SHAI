/*
  display_chipset_api.inl

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

Inline methods of display chipset driver API

@publishedDeviceAbstraction
*/

/*- Include Files  ----------------------------------------------------------*/

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Error codes */
typedef enum  
    {
    /* Init */
    DISP_FUNC_DISP_API_VERSION = 0,
    DISP_FUNC_GET_NUMBER_OF_CAPABILITIES,
    DISP_FUNC_GET_CAPABILITIES,
    DISP_FUNC_BIND_DISPLAY_NUMBER,
    DISP_FUNC_UNBIND_DISPLAY_NUMBER,

    /* Control */
    DISP_FUNC_SET_FINAL_VIEW,
    DISP_FUNC_CLONE_OUTPUT,
    DISP_FUNC_POWER_CONTROL,
    DISP_FUNC_DRIVER_MESSAGE,

    /* Flush */
    DISP_FUNC_PREPARE_FLUSH,
    DISP_FUNC_FLUSH,

    /* Commands */
    DISP_FUNC_CLEAR_LIST,
    DISP_FUNC_APPEND_COMMAND,
    DISP_FUNC_APPEND_PARAMETER,
    DISP_FUNC_APPEND_READ,
    DISP_FUNC_APPEND_READ_RAW,
    DISP_FUNC_PROCESS_LIST,

    /* Memory */
    DISP_FUNC_ALLOCATE_BUFFER,
    DISP_FUNC_CALCULATE_MEMORY_SIZE,
    DISP_FUNC_INITIALISE_BUFFER,
    DISP_FUNC_DEALLOCATE_BUFFER,
    DISP_FUNC_GET_WORK_BUFFER,

    DISP_FUNC_SIZE_OF_ARRAY,
    } DISPE_FUNCTIONS;

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/*- Functions ---------------------------------------------------------------*/

/*== Init ===================================================================*/

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline uint32 dispApiVersion(API_POINTER api)
    {

    typedef uint32 (*DISPT_API_VERSION)();
    DISPT_API_VERSION function = ( DISPT_API_VERSION ) api[ DISP_FUNC_DISP_API_VERSION ];
    return function();

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline uint32 dispGetNumberOfCapabilities(API_POINTER api)
    {

    typedef uint32 (*DISPT_GET_NUMBER_OF_CAPABILITIES)();
    DISPT_GET_NUMBER_OF_CAPABILITIES function = ( DISPT_GET_NUMBER_OF_CAPABILITIES ) api[ DISP_FUNC_GET_NUMBER_OF_CAPABILITIES ];
    return function();

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispGetCapabilities(API_POINTER api, uint32 capabilityNumber, DISPS_CAPABILITIES* capability)
    {

    typedef DISPE_ERROR (*DISPT_GET_CAPABILITIES)(uint32 capabilityNumber, DISPS_CAPABILITIES* capability);
    DISPT_GET_CAPABILITIES function = ( DISPT_GET_CAPABILITIES ) api[ DISP_FUNC_GET_CAPABILITIES ];
    return function( capabilityNumber, capability );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispBindDisplayNumber(API_POINTER api, DISPE_BUS busInterface, void* cbParam,
                                         IDENTIFIER* identifier, const DISPS_HW_SETTINGS* displaySettings)
    {

    typedef DISPE_ERROR (*DISPT_BIND_DISPLAY_NUMBER)(DISPE_BUS busInterface, void* cbParam,
                                                     IDENTIFIER* identifier, const DISPS_HW_SETTINGS* displaySettings);
    DISPT_BIND_DISPLAY_NUMBER function = ( DISPT_BIND_DISPLAY_NUMBER ) api[ DISP_FUNC_BIND_DISPLAY_NUMBER ];
    return function( busInterface, cbParam, identifier, displaySettings );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispUnbindDisplayNumber(API_POINTER api, IDENTIFIER identifier)
    {

    typedef DISPE_ERROR (*DISPT_UNBIND_DISPLAY_NUMBER)(IDENTIFIER identifier);
    DISPT_UNBIND_DISPLAY_NUMBER function = ( DISPT_UNBIND_DISPLAY_NUMBER ) api[ DISP_FUNC_UNBIND_DISPLAY_NUMBER ];
    return function( identifier );

    }


/*== Control ================================================================*/


/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispSetFinalView(API_POINTER api, IDENTIFIER identifier, const DISPS_FINAL_VIEW* finalView)
    {

    typedef DISPE_ERROR (*DISPT_SET_FINAL_VIEW)(IDENTIFIER identifier, const DISPS_FINAL_VIEW* finalView);
    DISPT_SET_FINAL_VIEW function = ( DISPT_SET_FINAL_VIEW ) api[ DISP_FUNC_SET_FINAL_VIEW ];
    return function( identifier, finalView );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCloneOutput(API_POINTER api, IDENTIFIER identifier, const DISPE_BUS destinationBus)
    {

    typedef DISPE_ERROR (*DISPT_CLONE_OUTPUT)(IDENTIFIER identifier, const DISPE_BUS destinationBus);
    DISPT_CLONE_OUTPUT function = ( DISPT_CLONE_OUTPUT ) api[ DISP_FUNC_CLONE_OUTPUT ];
    return function( identifier, destinationBus );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispPowerControl(API_POINTER api, IDENTIFIER identifier, DISPE_PWR_MODE powerMode, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*DISPT_POWER_CONTROL)(IDENTIFIER identifier, DISPE_PWR_MODE powerMode, DISPT_READY_CB callback);
    DISPT_POWER_CONTROL function = ( DISPT_POWER_CONTROL ) api[ DISP_FUNC_POWER_CONTROL ];
    return function( identifier, powerMode, callback );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispDriverMessage(API_POINTER api, IDENTIFIER identifier, CHIPSET_DRV_NAME receiver,
                                     DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback)
    {

    typedef DISPE_ERROR (*DISPT_DRIVER_MESSAGE)(IDENTIFIER identifier, CHIPSET_DRV_NAME receiver,
                                                DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback);
    DISPT_DRIVER_MESSAGE function = ( DISPT_DRIVER_MESSAGE ) api[ DISP_FUNC_DRIVER_MESSAGE ];
    return function( identifier, receiver, message, param, callback );

    }


/*== Flush ==================================================================*/


/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispPrepareFlush(API_POINTER api, IDENTIFIER identifier, const DISPS_UPDATE* changedArea, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*DISPT_PREPARE_FLUSH)(IDENTIFIER identifier, const DISPS_UPDATE* changedArea, DISPT_READY_CB callback);
    DISPT_PREPARE_FLUSH function = ( DISPT_PREPARE_FLUSH ) api[ DISP_FUNC_PREPARE_FLUSH ];
    return function( identifier, changedArea, callback );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispFlush(API_POINTER api, IDENTIFIER identifier, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*DISPT_FLUSH)(IDENTIFIER identifier, DISPT_READY_CB callback);
    DISPT_FLUSH function = ( DISPT_FLUSH ) api[ DISP_FUNC_FLUSH ];
    return function( identifier, callback );

    }


/*== Commands ===============================================================*/


/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispClearList(API_POINTER api, IDENTIFIER identifier)
    {

    typedef DISPE_ERROR (*DISPT_CLEAR_LIST)(IDENTIFIER identifier);
    DISPT_CLEAR_LIST function = ( DISPT_CLEAR_LIST ) api[ DISP_FUNC_CLEAR_LIST ];
    return function( identifier );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispAppendCommand(API_POINTER api, IDENTIFIER identifier, uint32 command)
    {

    typedef DISPE_ERROR (*DISPT_APPEND_COMMAND)(IDENTIFIER identifier, uint32 command);
    DISPT_APPEND_COMMAND function = ( DISPT_APPEND_COMMAND ) api[ DISP_FUNC_APPEND_COMMAND ];
    return function( identifier, command );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispAppendParameter(API_POINTER api, IDENTIFIER identifier, uint32 parameter)
    {

    typedef DISPE_ERROR (*DISPT_APPEND_PARAMETER)(IDENTIFIER identifier, uint32 parameter);
    DISPT_APPEND_PARAMETER function = ( DISPT_APPEND_PARAMETER ) api[ DISP_FUNC_APPEND_PARAMETER ];
    return function( identifier, parameter );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispAppendRead(API_POINTER api, IDENTIFIER identifier, uint32 lengthInBytes, void* readBuffer)
    {

    typedef DISPE_ERROR (*DISPT_APPEND_READ)(IDENTIFIER identifier, uint32 lengthInBytes, void* readBuffer);
    DISPT_APPEND_READ function = ( DISPT_APPEND_READ ) api[ DISP_FUNC_APPEND_READ ];
    return function( identifier, lengthInBytes, readBuffer );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispAppendReadRaw(API_POINTER api, IDENTIFIER identifier, uint32 lengthInBytes, void* readBuffer, uint32 readBufferOneLine, uint32 readBufferStride)
    {

    typedef DISPE_ERROR (*DISPT_APPEND_READ_RAW)(IDENTIFIER identifier, uint32 lengthInBytes,
                         void* readBuffer, uint32 readBufferOneLine, uint32 readBufferStride);
    DISPT_APPEND_READ_RAW function = ( DISPT_APPEND_READ_RAW ) api[ DISP_FUNC_APPEND_READ_RAW ];
    return function( identifier, lengthInBytes, readBuffer, readBufferOneLine, readBufferStride );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispProcessList(API_POINTER api, IDENTIFIER identifier, DISPT_READY_CB callback)
    {

    typedef DISPE_ERROR (*DISPT_PROCESS_LIST)(IDENTIFIER identifier, DISPT_READY_CB callback);
    DISPT_PROCESS_LIST function = ( DISPT_PROCESS_LIST ) api[ DISP_FUNC_PROCESS_LIST ];
    return function( identifier, callback );

    }


/*== Memory =================================================================*/


/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispAllocateBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer)
    {

    typedef DISPE_ERROR (*DISPT_ALLOCATE_BUFFER)(IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer);
    DISPT_ALLOCATE_BUFFER function = ( DISPT_ALLOCATE_BUFFER ) api[ DISP_FUNC_ALLOCATE_BUFFER ];
    return function( identifier, bufferInfo, allocatedBuffer );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispCalculateMemorySize(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, uint32* neededMemorySize)
    {

    typedef DISPE_ERROR (*DISPT_CALCULATE_MEMORY_SIZE)(IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, uint32* neededMemorySize);
    DISPT_CALCULATE_MEMORY_SIZE function = ( DISPT_CALCULATE_MEMORY_SIZE ) api[ DISP_FUNC_CALCULATE_MEMORY_SIZE ];
    return function( identifier, bufferInfo, neededMemorySize );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispInitialiseBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer)
    {

    typedef DISPE_ERROR (*DISPT_INITIALISE_BUFFER)(IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer);
    DISPT_INITIALISE_BUFFER function = ( DISPT_INITIALISE_BUFFER ) api[ DISP_FUNC_INITIALISE_BUFFER ];
    return function( identifier, bufferInfo, allocatedBuffer );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispDeallocateBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferToBeRemoved)
    {

    typedef DISPE_ERROR (*DISPT_DEALLOCATE_BUFFER)(IDENTIFIER identifier, const DISPS_BUFFER* bufferToBeRemoved);
    DISPT_DEALLOCATE_BUFFER function = ( DISPT_DEALLOCATE_BUFFER ) api[ DISP_FUNC_DEALLOCATE_BUFFER ];
    return function( identifier, bufferToBeRemoved );

    }

/*---------------------------------------------------------------------------*/
/**
    @see header
*/
inline DISPE_ERROR dispGetWorkBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_RECTANGLE* fetchedArea, DISPS_BUFFER* fetchedWorkBuffer)
    {

    typedef DISPE_ERROR (*DISPT_GET_WORK_BUFFER)(IDENTIFIER identifier, const DISPS_RECTANGLE* fetchedArea, DISPS_BUFFER* fetchedWorkBuffer);
    DISPT_GET_WORK_BUFFER function = ( DISPT_GET_WORK_BUFFER ) api[ DISP_FUNC_GET_WORK_BUFFER ];
    return function( identifier, fetchedArea, fetchedWorkBuffer );

    }

/* End of File */

