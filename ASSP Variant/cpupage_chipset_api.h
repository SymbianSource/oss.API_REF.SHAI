/*
  cpupage_chipset_api.h

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
@brief CPU page chipset API H


@publishedDeviceAbstraction
*/

#ifndef __CPUPAGE_CHIPSET_API_H__
#define __CPUPAGE_CHIPSET_API_H__


// Include files
#include <kern_priv.h>


/**
CPU page structure which contains data delivered by bootstrap to ASSP/Variant
*/
struct TCpuPage
    {
    public:
        TBool     iRdcAvailable;     /**< is R&D certificate available */
        TPhysAddr *iDebugBufferPhys; /**< address of the debug buffer */
        TUint32   iDebugBufferSize;  /**< size of the debug buffer */
    };

/**
@brief CPU page class

class CPU page which contains the methods returning the CPU page related data
*/
class CpuPage
    {
    public:
        /**
        returns the address and size of the debug buffer

        @param aAddr address of the buffer on output in case of a success, NULL otherwise
        @param aSize size of the buffer on output (65536 bytes on success, 0 otherwise)
        @return returns KErrNone on success, KErrNotSupported otherwise
        @pre Pre-condition: bootstrap has reserved the memory for the debug buffer
             and has set up the CPU page: iDebugBufferPhys, iDebugBufferSize, Kern::SuperPage().iMachineData
        */
        IMPORT_C static TInt GetDebugBuffer(TPhysAddr &aAddr, TUint32 &aSize);


        /**
        returns whether R&D certificate is available
        @pre Pre-condition: bootstrap has set up the CPU page: iRdcAvailable, Kern::SuperPage().iMachineData
        */
        IMPORT_C static TBool IsRdcAvailable();
    };


#endif // __CPUPAGE_CHIPSET_API_H__
