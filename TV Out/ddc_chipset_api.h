/*
  ddc_chipset_api.h

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
  DDC is found from interface storage with bus name DISP_BUS_DDC.</p>
  <p></p>

*/
/** @file

Declaration of TV chipset driver API

@publishedDeviceAbstraction
*/

#ifndef DDC_CHIPSET_API_H
#define DDC_CHIPSET_API_H

/*- Include Files  ----------------------------------------------------------*/

#include "display_chipset_os.h"  /* OS specific header file, typedef etc. */
#include "display_chipset_api.h" /* Fetch enumeration etc */

/*- Namespace ---------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/** One DDC segment size. See that EDID block size is just 128 bytes,
    so base-EDID read might contain one EDID extension */
const uint32 KSegmentSize = 256;

/** One data block */
typedef uint8 DISPA_DDC_DATA_BLOCK[ KSegmentSize ];

/** API version number. @see dispDdcApiVersion().
    1:  First version */
const uint32 KApiDdcVersionNumber = 1;

/*- Macros ------------------------------------------------------------------*/

/*- External Data -----------------------------------------------------------*/

/*- Variables ---------------------------------------------------------------*/

/*- Forward Declarations ----------------------------------------------------*/

/*- Functional Prototypes ---------------------------------------------------*/

/* VERSION -> */

/** Gets implemented chipset API version. Verify the return value to KApiDdcVersionNumber.
    @param  api  API interface pointer, fetched from dispGetInterface()
    @see KApiDdcVersionNumber
    @return Implemented Tv chipset API version, KApiDdcVersionNumber (should match to client version) */
inline uint32 dispDdcApiVersion(API_POINTER api);

/* <- VERSION */


/* ACCESS -> */

/** Starts DDC read from wanted port.

    Method reads one DISPA_DDC_DATA_BLOCK, and it size is double of one EDID block,
    so the first EDID read might get base-EDID and first extension, if exists.
    With variable size of DisplayID, method reads anyway whole size of DISPA_DDC_DATA_BLOCK,
    even DisplayID section is smaller.

    @param  api               API interface pointer, fetched from dispGetInterface()
    @param  ddcPortAddress    DDC port which needs to be read
    @param  blockNumber       Datablock which needs to be read (parameter maps to segment-register 0x60)
    @param  dataBlock         Method fills this with read values. Ensure that this data exists all the time,
                              be careful if local variable.
    @param  callbackWhenRead  Will be called when ready, if no errors, then aDataBlock contains read values.
                              Call with NULL-callback cancels all read operations
                              (and ddc-driver calls pending callbacks).
    @return an error code */
inline DISPE_ERROR dispDdcRead(API_POINTER api, uint8 ddcPortAddress, uint32 blockNumber, DISPA_DDC_DATA_BLOCK* dataBlock, DISPT_READY_CB callbackWhenRead);

/* <- ACCESS */

/*- Inline Functions --------------------------------------------------------*/

#include "ddc_chipset_api.inl"

#endif /* DDC_CHIPSET_API_H */

/* End of File */

