/*
  cec_chipset_api.h

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

/**

  @mainpage
  @section intro_sec Introduction

  <p>This is the tv chipset driver API document.</p>
  <p>This API hides HW differencies from display (and other users) driver.
  API is not kept as binary compatible.</p>
  <p>Get API pointer:
  API pointer (API_POINTER) will be found from Interface Storage.
  DDC is found from interface storage with bus name DISP_BUS_CEC.</p>
  <p></p>

*/
/** @file

Declaration of TV chipset driver API

@publishedDeviceAbstraction
*/

#ifndef CEC_CHIPSET_API_H
#define CEC_CHIPSET_API_H

/*- Include Files  ----------------------------------------------------------*/

#include "display_chipset_os.h"  /* OS specific header file, typedef etc. */
#include "display_chipset_api.h" /* Fetch enumeration etc */

/*- Namespace ---------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** CEC logical addresses */
typedef enum
    {
    DISP_CEC_TV              = 0,
    DISP_CEC_REC_DEV1        = 1,
    DISP_CEC_REC_DEV2        = 2,
    DISP_CEC_TUNER1          = 3,
    DISP_CEC_PLAYBACK_DEV1   = 4,
    DISP_CEC_AUDIO_SYSTEM    = 5,
    DISP_CEC_TUNER2          = 6,
    DISP_CEC_TUNER3          = 7,
    DISP_CEC_PLAYBACK_DEV2   = 8,
    DISP_CEC_REC_DEV3        = 9,
    DISP_CEC_TUNER4          = 10, /**< Since HDMI 1.3a */
    DISP_CEC_PLAYBACK_DEV3   = 11, /**< Since HDMI 1.3a */
    DISP_CEC_RESERVED1       = 12, /**< Reserved until specified */
    DISP_CEC_RESERVED2       = 13, /**< Reserved until specified */
    DISP_CEC_FREE_USE        = 14,
    DISP_CEC_UNREG_BROADCAST = 15, /**< Unregistered=As initiator address, Broadcast=As destination address */
    } DISPE_CEC_LOGICAL_ADDR;

/** Use case on bus - needed for protocol timing */
typedef enum
    {
    DISP_CEC_UNKNOWN        = 0,
    DISP_CEC_NEW_INITIATOR  = 1, /**< New initiator wants to send a frame */
    DISP_CEC_SAME_INITIATOR = 2, /**< Present initiator wants to send another frame immediately after its previous frame */
    } DISPE_CEC_SEND_USE_CASE;

/*- Data Structs ------------------------------------------------------------*/

/**
CEC header block
*/
typedef struct
    {
    /** Initiator logical address */
    DISPE_CEC_LOGICAL_ADDR initiator;
    /** Destination logical address */
    DISPE_CEC_LOGICAL_ADDR destination;
    } DISPS_CEC_HEADER_BLOCK;

/**
CEC data block
*/
typedef struct
    {
    /** Information bits (data, opcode or address) */
    uint8 infoBits;
    } DISPS_CEC_DATA_BLOCK;

///Maximum amount of operands (max amount of blocks=16, 2 goes to header and opcode)
const uint32 KMaxCecOperands = 14;

/**
CEC frame
@code
__________________________ __________________________
|                        | |                        |
| DISPS_CEC_HEADER_BLOCK | | DISPS_CEC_DATA_BLOCK(n)|
|                        | |                        |
¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯ ¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯
            `--------------------------´
             ____________|_____________
             |                        |
             |    DISPS_CEC_FRAME     |
             |                        |
             ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
@endcode
*/
typedef struct
    {
    /** Message header */
    DISPS_CEC_HEADER_BLOCK cecHeader;
    /** Message opcode (optional) */
    DISPS_CEC_DATA_BLOCK opcode;
    /** Message operand(s) */
    DISPS_CEC_DATA_BLOCK operand[ KMaxCecOperands ];
    /** Describes how many blocks in this frame has to be sent. 0 is invalid, means start bit only.
        1 = cecHeader only, 2 = cecHeader+opcode, 3 = cecHeader+opcode+operand[0], and so on.
        Blocks (cecHeader/opcode/operand) which are after this value, are undefined. */
    uint8 numOfBlocks;
    /** Fill this for giving hint for driver (dispCecTransmit).
        When reading, driver tries to fill this. */
    DISPE_CEC_SEND_USE_CASE useCase;
    } DISPS_CEC_FRAME;

/*- Constants ---------------------------------------------------------------*/

/** API version number. @see dispCecApiVersion().
    1:  First version */
const uint32 KApiCecVersionNumber = 1;

/*- Macros ------------------------------------------------------------------*/

/*- External Data -----------------------------------------------------------*/

/*- Variables ---------------------------------------------------------------*/

/*- Forward Declarations ----------------------------------------------------*/

/*- Functional Prototypes ---------------------------------------------------*/

/* VERSION -> */

/** Gets implemented chipset API version. Verify the return value to KApiCecVersionNumber.
    @param  api  API interface pointer, fetched from dispGetInterface()
    @see KApiCecVersionNumber
    @return Implemented Tv chipset API version, KApiCecVersionNumber (should match to client version) */
inline uint32 dispCecApiVersion(API_POINTER api);

/* <- VERSION */


/* CONTROL -> */

/** Sets device's own allocated logical address to driver.

    With this address, driver can detect message which is sent for this
    particular device and act ACK-bit as specified.

    If for some reason, address is wanted set to undefined, DISP_CEC_TV can be used for
    that. Therefore, with this method, DISP_CEC_TV=undefined=unallocated.

    @param  api                API interface pointer, fetched from dispGetInterface()
    @param  ownLogicalAddress  Device's own allocated logical address

    @return an error code */
inline DISPE_ERROR dispSetLogicalAddress(API_POINTER api, DISPE_CEC_LOGICAL_ADDR ownLogicalAddress);

/** Transmits one frame to follower.

    Driver sends DISPS_CEC_FRAME blocks until numOfBlocks value is reached.

    Driver is responsible for taking care about timing issues,
    for reaching minimum signal free times in separate use cases (DISPE_CEC_SEND_USE_CASE).

    When driver detectes an error while transferring, it tries re-transmit
    specified max times, and after that rises error for client with callback.

    If dispSetLogicalAddress() is not called and initiator&destination addresses are equal,
    then it is assumed that there is a logical address allocation ongoing.
    If a free logical address is found, callbackWhenTransmitted returns DISP_ERROR_NACK (NACK).

    When iDestination==DISP_CEC_UNREG_BROADCAST (broadcast), driver detects that
    and observing ACK-bit with this special way.

    @see dispSetLogicalAddress
    @see dispCecRead

    @param  api                      API interface pointer, fetched from dispGetInterface()
    @param  frame                    A CEC frame, which needs to be sent to follower
    @param  callbackWhenTransmitted  Completed when sent or error.
                                       Multiple (max 8) transmits can be pending at same time.
                                       Frames will be sent in same order as received by client.
                                       Always check callbackWhenTransmitted for getting reason for complete:
                                         DISP_ERROR_NONE = Sent ok (no detected errors during transmit)
                                         DISP_ERROR_NACK = Acknowledge error (NACK)
                                         DISP_ERROR_DATA_LINES = If the initiator detects low impedance on the
                                                                 CEC-line, when it is transmitting high impedance and
                                                                 is not expecting a follower asserted bit.

    @return DISP_ERROR_NONE if success */
inline DISPE_ERROR dispCecTransmit(API_POINTER api, const DISPS_CEC_FRAME* frame, DISPT_READY_CB callbackWhenTransmitted);

/** Listening and reads all CEC traffic.

    When complete is ready, readFrame will contain data moved in CEC.

    If monitorAll is True, received message might not be sent for this
    particular device, so all frames will be detected with this,
    therefore method can be used for CEC-bus monitoring. Of course,
    if this device is not the follower for a message, driver will not
    acknowledge the data, except broadcast-messages.

    callbackWhenRead should always pending (when cable connected).

    If new frame is detected by driver while callbackWhenRead is not pending,
    cec-driver caches (min 10 frames) the read data and calls callbackWhenRead
    immediately after next dispCecRead() call. This way data should not be lost by API client.

    readFrame.numOfBlocks is filled correctly showing the number of valid received
    blocks.

    Driver tries to fill DISPE_CEC_SEND_USE_CASE if possible, otherwise useCase=DISP_CEC_UNKNOWN.

    @param  api               API interface pointer, fetched from dispGetInterface()
    @param  readFrame         Read frame when callbackWhenRead completed.
    @param  monitorAll        True if Read method monitors all traffic on CEC,
                              even this device is not follower for message.
    @param  callbackWhenRead  Will be completed when ready, if no errors,
                                then readFrame contains read values.
                                Check always callbackWhenRead.
                                Call with NULL-callback cancels all read operations
                                (and cec-driver calls pending callbacks).

    @return DISP_ERROR_NONE if success.
            DISP_ERROR_NOT_IMPLEMENTED if monitorAll==True but Hw hasn't capability for that.
            DISP_ERROR_INVALID_PARAMETER if readFrame has illegal value(s) (driver does not care about actual data)
            DISP_ERROR_ALREADY_EXISTS if Read is already pending.
            Any other error for rest of reasons. */
inline DISPE_ERROR dispCecRead(API_POINTER api, DISPS_CEC_FRAME* readFrame, bool8 monitorAll, DISPT_READY_CB callbackWhenRead);

/* <- CONTROL */

/*- Inline Functions --------------------------------------------------------*/

#include "cec_chipset_api.inl"

#endif /* CEC_CHIPSET_API_H */

/* End of File */

