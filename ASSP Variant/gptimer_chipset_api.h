/*
  gptimer_chipset_api.h

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
@brief General Purpose Timer Chipset API H

@publishedDeviceAbstraction
*/

#ifndef __GPTIMER_CHIPSET_API_H__
#define __GPTIMER_CHIPSET_API_H__


// Include files
#include <kern_priv.h>


/**
Pointer to a callback function for the GPT client to use

@note "Callback is executed in the DFC or ISR context"

@param TAny* pointer to a parameter the call back function may use
*/
typedef void (*GPTimerFn)(TAny*);



// Class declaration

/**
@brief GP timer class

 General Purpose Timer functionality for clients
*/
class GPTimer
    {
    public:
        /**
        constructor of a GPT object
        */
        IMPORT_C GPTimer();
          
          
        /**
        allocates a HW GPT

        @param aFunction A pointer to a callback function which is called 
               when the timer expires.
        @param aPtr A parameter of the callback function.

        @return returns KErrNone if there was no error or KErrInUse if no 
                HW GPT is available.

        @pre Pre-condition: HW GPT must be available
        */
        IMPORT_C TInt Open(GPTimerFn aFunction, TAny* aPtr);
          
          
        /**
        Releases a HW GPT

        @return Returns KErrNone if there was no error or KErrNotFound if 
                no HW GPT was allocated before.

        @pre Pre-condition: Open was called
        */
        IMPORT_C TInt Close();
          
          
        /**
        Starts a GPT in one-shot mode, the callback routine will be called in 
        interrupt context.

        @param aTime Timeout in microseconds.

        @return returns KErrNone if there was no error, KErrInUse if the timer is already active,
                        KErrNotFound if no HW GPT was allocated before.
        */
        IMPORT_C TInt OneShot(TUint aTime);



        /**
        Starts a GPT in one-shot mode, the callback routine will be called in client's DFC context.

        @param aTime Timeout in microseconds.
        @param aDfc client's DFC object.

        @return returns KErrNone if there was no error, KErrInUse if the timer is already active,
                        KErrArgument if aDfc is NULL, KErrNotFound if no HW GPT was allocated before.
        */
        IMPORT_C TInt OneShot(TUint aTime, TDfc& aDfc);



        /**
        Starts a GPT in periodic mode (the timer is restarted after it expired).
        The callback routine will be called in interrupt context.

        @param aTime Timeout in microseconds.

        @return returns KErrNone if there was no error, KErrInUse if the timer is already active,
                        KErrNotFound if no HW GPT was allocated before.
        */
        IMPORT_C TInt Periodic(TUint aTime);


        /**
        Starts a GPT in periodic mode (the timer is restarted after it expired).
        The callback routine will be called in client's DFC context.

        @param aTime Timeout in microseconds.
        @param aDfc client's DFC object.

        @return returns KErrNone if there was no error or KErrInUse if the timer is already active,
                        KErrArgument if aDfc is NULL, KErrNotFound if no HW GPT was allocated before.
        */
        IMPORT_C TInt Periodic(TUint aTime, TDfc& aDfc);


        /**
        Requests to cancel a GPT.

        @return Returns ETrue if the timer was actually cancelled or EFalse if the timer was not
                        cancelled because it was not running or the callback was already running.
        */
        IMPORT_C TBool Cancel();

        /**
        destructor of a GPT object
        */
        IMPORT_C ~GPTimer();
          
    private:
        /**
        stores aFunction parameter
        */
        GPTimerFn iFunction;


        /**
        stores aPtr parameter
        */
        TAny* iPtr;
        
        
        /**
        stores aTime parameter
        */
        TUint iTime;


        /**
        stores aDfc parameter
        */
        TDfc iDfc;
    };


#endif // __GPTIMER_CHIPSET_API_H__
