/*
  pm_services_chipset_api.h

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
@brief PM Services Chipset API H

The purpose of this interface is to enable Nokia to test power management
functionalities implemented below the Chipset API. This interface is meant to be
used only by Symbian kernel side clients.

@publishedDeviceAbstraction
*/

#ifndef PM_SERVICES_CHIPSET_API_H
#define PM_SERVICES_CHIPSET_API_H

// Include files

#include <kern_priv.h>
#include "pm_definitions_chipset_api.h"

// Data types

/**
Dvfs monitor callback function
@param aMonitor monitor id
@param aLoad load (casted in case of non-integer types)
*/
typedef void (*TDvfsMonitorCbFn)(TDvfsMonitor aMonitor, TUint32 aLoad);

/**
Idle entry callback function
@param aMode Target sleep mode
@param aPtr Client parameter
*/
typedef void (*TIdleEntryCbFn)(TInt aMode, TAny* aPtr);

/**
Idle exit callback function
@param aMode Sleep mode just exited
@param aPtr Client parameter
*/
typedef void (*TIdleExitCbFn)(TInt aMode, TUint32 aIdleTime, TAny* aPtr);

// Class declaration

/**
@brief Class description

This class contains static methods to set and get certain power management
services parameters. There are no data members.
*/
class PMServices
    {
    public:
        /**
        The integer aLevel will be passed and this will represent the forced
        OPP.
        @param aRes The ID for a power resource(CPU, DMA) that will be forced to
        an OPP.
        @param aLevel An integer, which represents the forced OPP level.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt ForceSystemOPP(TPerfRes aRes, TInt aLevel);

        /**
        A resource is no longer forced to a particular OPP.  The OPP will now be
        based on the DVFS algorithms.  If the system was not forced then no
        action need take place.
        @param aRes resource id.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt UnForceSystemOPP(TPerfRes aRes);

        /**
        Gets the number of supported global sleep states.
        @return Number of sleep states supported
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetNumSleepStates();

        /**
        Blocks a certain sleep state.
        @param aSleepState The Sleep state to be blocked..
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt BlockSleepState(TInt aSleepState);

        /**
        Un-blocks a certain sleep state.
        @param aSleepState The Sleep state to be un-blocked..
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt UnBlockSleepState(TInt aSleepState);

        /**
        Starts the monitoring and load prediction algorithms but does nothing to
        the OPP.
        @param aRes The ID for a power resource(CPU, DMA) that will now start to
        use the DVFS algorithms.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt EnableDVFS(TPerfRes aRes);

        /**
        Stops the monitoring and load prediction algorithms.  This API will not
        change the OPP.  The OPP will remain the same as it was before this API
        was called
        @param aRes The ID for a power resource(CPU, DMA) that will no longer
        use the DVFS algorithms.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt DisableDVFS(TPerfRes aRes);

        /**
        Finds out if the DVFS algorithms are currently running for a given power
        resource.
        @param aRes Find out if the DVFS algorithms are working for this
        particular power resource ID .
        @return ETrue if DVFS enabled, EFalse otherwise.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TBool IsDVFSEnabled(TPerfRes aRes);

        /**
        Gets the current load of a given HW block.
        @param aMon Monitor id
        @param aLoad Load value (casted into TUint32 in case of non-integer
        types)
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetCurrentLoad(TDvfsMonitor aMon, TUint32 aLoad);

        /**
        Register to receive notifications of a change in load for a given
        monitor.
        @param aCb callback function pointer
        @param aMon monitor id.
        @param aGranuality The percentage change at which notifications will be
        sent.  Zero will mean that notifications will be sent straight away.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.  The preferable
        way to call this function is from a thread context with interrupts
        enabled after all the kernel extensions have been initialized in the
        boot up.
        */
        IMPORT_C static TInt RegisterForLoadObservations(TDvfsMonitorCbFn aCb,
            TDvfsMonitor aMon, TInt aGranuality);
        /**
        Method to cancel any load observation callback.
        @param aCb callback function pointer
        @param aMon monitor id.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt DeRegisterForLoadObservations(TDvfsMonitorCbFn
            aCb, TDvfsMonitor aMon);

        /**
        Method to get the number of supported OPPs for a given performance
        resource.
        @param aRes performance resource id.
        @return The resource’s available OPPs.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetNumOPPs(TPerfRes aRes);

        /**
        Get the workload prediction window buffer pointer (Symbian kernel data).
        @return The window buffer pointer (casted into TUint32 type)
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TUint32 GetWpWindowBuf();

        /**
        Request for idle entry callback.
        @param aCbFn Callback function
        @param aPtr A pointer to be passed to the callback function when called
        @param aCore Core number. If -1, API applies to system idle
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt RequestIdleEntryCallback(TIdleEntryCbFn aCbFn,
            TAny* aPtr, TInt aCore = -1);

        /**
        Request for idle exit callback
        @param aCbFn Callback function
        @param aPtr A pointer to be passed to the callback function when called
        @param aCore Core number. If -1, API applies to system idle
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt RequestIdleExitCallback(TIdleExitCbFn aCbFn,
            TAny* aPtr, TInt aCore = -1);

        /**
        Cancel idle entry callback
        @param aCbFn Callback function
        @param aCore Core number. If -1, API applies to system idle
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt CancelIdleEntryCallback(TIdleEntryCbFn aCbFn,
            TInt aCore);

        /**
        Cancel idle exit callback
        @param aCbFn Callback function
        @param aCore Core number. If -1, API applies to system idle
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt CancelIdleExitCallback(TIdleExitCbFn aCbFn,
            TInt aCore);

        /**
        Method to get the hardware time based on a real time clock.
        @return Hardware time in microseconds.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TUint32 HwTime();

        /**
        Retire a given number of cores. It is possible that no cores can be
        retired because all remaining running cores have features not available
        on any other core; and so may not allow any to be retired ( even if
        there are no threads in the ready list that may require those features);
        when that happens this API will fail (and return as error code).
        @param aCount number of cores to retire
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt RetireCore(TInt aCount);

        /**
        Enables any retired cores.  If no cores can be engaged due to all cores
        being on or for some other   reason then this API returns an error.
        @param aEngage The number of cores to Engage.
        @return One of the system wide Symbian error codes according to the API
        error handling specification.
        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt EngageCore(TInt aEngage);
    };


#endif // PM_SERVICES_CHIPSET_API_H
