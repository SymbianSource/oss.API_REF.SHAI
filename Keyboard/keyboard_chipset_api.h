/*
  keyboard_chipset_api.h

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
@brief Keyboard Chipset API H

This is the header file for Keyboard Chipset API that is used to access 
the matrix keyboard and power key services provided by the third party chipset vendors.

@publishedDeviceAbstraction
*/

#ifndef __KEYBOARD_CHIPSET_API_H__
#define __KEYBOARD_CHIPSET_API_H__


// Include files

#include <kern_priv.h>
#include <e32event.h>


// Constants


// Macros


// Data types

/**
This defines the type of a callback function which is called to 
notify a new key event to the client. The callback function is 
executed in the context of the calling thread.
*/
typedef void (*TKeyboardEventCbFn)();

// Function prototypes

// Forward declarations

// Class declaration

/**
This class defines the Chipset API that is used to access 
the matrix keyboard service provided by the third party chipset vendors.
*/
class KeyboardMatrix
    {
    public:

        /**
        This function is used to do the necessary initialization with the given matrix size 
        so that the chipset is ready to provide the matrix keyboard service. It registers 
		a callback function which is called to notify a new key event.

        @param aSize The size of matrix keyboard that the client is using.
        @param aCallback The callback function which is called to notify a new key event.

        @return Symbian OS system wide error code, and the followings are required:
                KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;

        @pre Pre-condition, it should be called before the other methods in the class are used.
        */
        IMPORT_C static TInt Init(TUint aSize, TKeyboardEventCbFn aCallback);

        /**
        This function is used to enable the matrix keyboard service.  

        @return Symbian OS system wide error code, and the followings are required:
                KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;

        @pre Pre-condition, the matrix keyboard service has been initialized successfully.
        */
        IMPORT_C static TInt Enable();

        /**
        This function is used to disable the matrix keyboard service.

        @return Symbian OS system wide error code, and the followings are required:
                KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;

        @pre Pre-condition, the matrix keyboard service has been enabled.
        */
        IMPORT_C static TInt Disable();

        /**
        This function is used to read the key state of the matrix keyboard.

        @param aKeys   Reference to the number of keys that are currently pressed. 
                       If the return value is 0 then it means all the previously pressed keys are released.
        @param aBuffer Pointer to the buffer where all the key presses shall be reported.

        @return Symbian OS system wide error code, and the followings are required:
				KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;

        @pre Pre-condition, the matrix keyboard service has been enabled.
        */
        IMPORT_C static TInt Read(TInt& aKeys, TInt* aBuffer);

    };


/**
This class defines the Chipset API that is used to access 
the power key service provided by the third party chipset vendors.
*/
class KeyboardPowerKey
    {
    public:

        /**
        This function is used to do the necessary initialization so that 
        the chipset is ready to provide the power key service. It registers 
        a callback function which is called to notify a new power key event.

        @param aCallback The callback function which is called to notify a new power key event.

        @return Symbian OS system wide error code, and the followings are required:
                KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;
        */
        IMPORT_C static TInt Init(TKeyboardEventCbFn aCallback);

        /**
        This function is used to read the key state of the power key.

        @param aState Reference to the variable that contains the power key state.

        @return Symbian OS system wide error code, and the followings are required:
                KErrNone – the operation is successfully executed;
                KErrGeneral – error condition;
        */
        IMPORT_C static TInt Read(TRawEvent::TType& aState);

    };

#endif // __KEYBOARD_CHIPSET_API_H__
