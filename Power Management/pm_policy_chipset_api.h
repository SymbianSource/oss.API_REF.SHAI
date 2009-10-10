/*
  pm_policy_chipset_api.h

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
@brief PM Policy Chipset API H

The purpose of this interface is to enable Nokia to affect power management
functionalities implemented below the Chipset API.
This interface is meant to be used only by Symbian kernel side clients.

@publishedDeviceAbstraction
*/

#ifndef PM_POLICY_CHIPSET_API_H
#define PM_POLICY_CHIPSET_API_H


// Include files

#include <kern_priv.h>
#include "pm_definitions_chipset_api.h"


// Class declaration

/**
@brief Class description

This class contains static methods to set and get certain power management
policy parameters. There are no data members.
*/
class PMPolicy
    {
    public:
        /**
        This enumeration is purposed to include the list of known load
        prediction algorithms. It is mainly used for enquiring about current
        algorithm and for setting and getting their parameters if applicable.
        */
        enum TAlgorithm
            {
            EAlgoAll,       /**< Any algorithm that is in use   */
            EAlgoAVGn,      /**< Weighted average of past loads */
            EAlgoMAW,       /**< Moving average workload        */
            EAlgoLMS,       /**< Least mean square              */
            EAlgoUnknown    /**< Any other algorithm            */
            };

        /**
        The purpose of this enumeration is to specify the type of parameters
        that can be changed for one or more of the load prediction algorithms.
        */
        enum TParam
            {
            EParamSampleCount = 1   /**< number of history samples  */
            };

        /**
        Method to set the load prediction trigger delay. When the predicted load
        is changed, it waits the specific amount of time before triggering the
        OPP change. If the load changes back to the previous OPP window during
        the wait period, then no OPP change will be done.

        @param aRes The performance resource
        @param aDelayInc Delay to be applied when the load is increasing
        @param aDelayDec Delay to be applied when the load is decreasing

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt SetLoadPredTrigDelay(TPerfRes aRes, TInt aDelayInc,
            TInt aDelayDec);

        /**
        Method to get the current trigger delay setting value of a particular
        load monitor.

        @param aRes The performance resource
        @param aDelayInc Current delay setting when the load is increasing
        @param aDelayDec Current delay setting when the load is decreasing

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetLoadPredTrigDelay(TPerfRes aRes,
            TInt& aDelayInc, TInt& aDelayDec);

        /**
        Method to lock the load monitor trigger delay. If it is already in
        locked state, this call is ignored.

        @param aRes The performance resource

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt LockLoadPredTrigDelay(TPerfRes aRes);

        /**
        Method to unlock the load monitor trigger delay. If it is not in locked
        state, this call is ignored.

        @param aRes The performance resource

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt UnlockLoadPredTrigDelay(TPerfRes aRes);

        /**
        Method to set the WP tick period
        @param aMon Monitor id
        @param aPeriod New period value to be set (in milliseconds)
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt SetWpTickPeriod(TDvfsMonitor aMon, TUint aPeriod);

        /**
        Method to get the WP tick period
        @param aMon Monitor id
        @param aPeriod [Out] Current period value
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt GetWpTickPeriod(TDvfsMonitor aMon, TUint& aPeriod);

        /**
        Method to lock the WP tick period setting. If it is already locked, this
        call is ignored
        @param aMon Monitor id
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt LockWpTickPeriod(TDvfsMonitor aMon);

        /**
        Method to unlock the WP tick period setting. If it is not locked, this
        call is ignored
        @param aMon Monitor id
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt UnlockWpTickPeriod(TDvfsMonitor aMon);

        /**
        Method to set the WP window width
        @param aMon Monitor id
        @param aWidth The WP window width to set (in number of prediction ticks)
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt SetWpWindowWidth(TDvfsMonitor aMon, TUint aWidth);

        /**
        Method to get the WP window width
        @param aMon Monitor id
        @param aWidth [Out] The WP window width to get (in number of prediction ticks)
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt GetWpWindowWidth(TDvfsMonitor aMon, TUint& aWidth);

        /**
        Method to lock the WP window width. Does nothing if it is already locked
        @param aMon Monitor id
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt LockWpWindowWidth(TDvfsMonitor aMon);

        /**
        Method to unlock the WP window width. Does nothing if it is not locked
        @param aMon Monitor id
        @return One of the system wide Symbian error codes according to the API
        error handling specification
        */
        IMPORT_C static TInt UnlockWpWindowWidth(TDvfsMonitor aMon);

        /**
        Method to get the current load prediction algorithm.

        @param aMon The DVFS monitor
        @param aAlgo Current algorithm returned to the caller (out parameter)
        @param aCustom Any additional information (optional parameter).

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetCurrentAlgorithm(TDvfsMonitor aMon,
            TAlgorithm& aAlgo, TInt* aCustom = 0);

        /**
        Method to set parameters to load monitor algorithm.

        @param aMon The DVFS monitor
        @param aAlgo Algorithm whose parameter has to be changed.
        @param aParam Algorithm parameter name.
        @param aArg The parameter value.

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt SetLoadMonitorParam(TDvfsMonitor aMon,
            TAlgorithm aAlgo, TParam aParam, TAny* aArg);

        /**
        Method to retrieve existing parameters from load monitor algorithms.

        @param aMon The DVFS monitor
        @param aAlgo Algorithm whose parameter has to be retrieved.
        @param aParam Algorithm parameter name.
        @param aArg Pointer to a location where the value must be stored. This
        can not be null (passing null value results in returning error code).

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetLoadMonitorParam(TDvfsMonitor aMon,
            TAlgorithm aAlgo, TParam aParam, TAny* aArg);

        /**
        Locks the load monitor parameters. This lock should apply only to known
        parameters of known algorithms – those that are enumerated in this
        specification.

        @param aMon The DVFS monitor

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt LockLoadMonitorParam(TDvfsMonitor aMon);

        /**
        Unlocks the load monitor parameters.

        @param aMon The DVFS monitor

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt UnlockLoadMonitorParam(TDvfsMonitor aMon);

        /**
        Method to enable or disable a particular operation point.

        @param aPerfRes Performance resource ID.
        @param aOPP The operation point that is to be enable or disabled
        @param aEnable If ETrue is specified, the OPP is enabled and if EFalse
        is specified, then the OPP is disabled.

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt SetOPPState(TPerfRes aPerfRes, TInt aOPP,
            TBool aEnable);

        /**
        Method to set the status of a list of operation points.

        @param aPerfRes Performance resource ID.
        @param aOppState Array containing the operation point status to be set.

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt SetOPPState(TPerfRes aPerfRes,
            RArray<TBool>& aOppState);

        /**
        Method to get the current enabled/disabled status of a particular
        operation point. OPPs are specified in the same way as mentioned
        earlier.
        Argument:
        @param aPerfRes Performance resource ID.
        @param aOPP The operation point that is to be checked.
        @param aEnable Status of the operation point returned to the caller.

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetOPPState(TPerfRes aPerfRes, TInt aOPP,
            TBool& aEnable);

        /**
        Method to get the full list of operation point enabled status.
        Argument:
        @param aPerfRes Performance resource ID.
        @param aOppState Array containing the operation point enabled status
        indexed by the operation point enumeration.

        @return One of the system wide Symbian error codes according to the API
        error handling specification.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static TInt GetOPPState(TPerfRes aPerfRes,
            RArray<TBool>& aOppState);

        /**
        Method to pass context inputs to the vendor software.
        Argument:
        @param aArg0 Argument 0
        @param aArg1 Argument 1
        @param aArg2 Argument 2
        @param aArg3 Argument 3

        @return None.

        @pre Called from thread context with interrupts enabled.
        */
        IMPORT_C static void SetInput(TUint32 aArg0, TUint32 aArg1,
            TUint32 aArg2, TUint32 aArg3);
    };


#endif // PM_POLICY_CHIPSET_API_H
