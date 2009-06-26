/*
  display_chipset_api_interfaces.h

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

Declaration of display chipset driver API interface storage

@publishedDeviceAbstraction
*/

#ifndef DISPLAY_CHIPSET_API_INTERFACES_H
#define DISPLAY_CHIPSET_API_INTERFACES_H

/*- Include Files  ----------------------------------------------------------*/

#include "display_chipset_os.h"  /* OS specific header file, typedefs etc. */
#include "display_chipset_api.h" /* Fetch enumeration etc */

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/*- Data Structs ------------------------------------------------------------*/

/*- Constants ---------------------------------------------------------------*/

/*- Macros ------------------------------------------------------------------*/

/*- External Data -----------------------------------------------------------*/

/*- Variables ---------------------------------------------------------------*/

/*- Forward Declarations ----------------------------------------------------*/

/*- Functional Prototypes ---------------------------------------------------*/

/** Chipset API interface registration method.
    @param  driverName  Unique name of component which will register to the Interface Storage
    @param  displayBus  Bus type what this interface controls
    @param  apiPointer  This chipset API interface pointer
    @return  DISP_ERROR_NONE if ok.
             DISP_ERROR_ALREADY_EXISTS if same name and bus is already registered. */
DLL_IMPORT DISPE_ERROR dispSetInterface(CHIPSET_DRV_NAME driverName, DISPE_BUS displayBus, API_POINTER apiPointer);

/** Chipset API interface getter.
    If got pointer is NULL or DISP_ERROR_NOT_FOUND is returned, caller has to try same query later.
    @param  callerName     Unique name of component which is getting the pointer to specific 'displayBus'
    @param  displayBus     Bus type what this interface controls
    @param  gotApiPointer  Pointer to API interface. This is filled for caller by interface storage.
    @return  DISP_ERROR_NONE if ok.
             DISP_ERROR_INVALID_NAME This name is not recognised
             DISP_ERROR_NOT_FOUND no any registered for this DISPE_BUS */
DLL_IMPORT DISPE_ERROR dispGetInterface(CHIPSET_DRV_NAME callerName, DISPE_BUS displayBus, API_POINTER* gotApiPointer);

/*- Inline Functions --------------------------------------------------------*/

#endif /* DISPLAY_CHIPSET_API_INTERFACES_H */

/* End of File */

