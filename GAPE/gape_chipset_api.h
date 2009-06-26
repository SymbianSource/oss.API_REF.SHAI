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
@brief gape_chipset_api.h

This a header file of gape_chipset_api.h

@publishedDeviceAbstraction
*/

#ifndef __GAPE_H__
#define __GAPE_H__

// Include files

#include <kern_priv.h>

// Constants

/* The list of the descriptor names what the array can hold */
_LIT8( KTvOut, "TvOut" );
_LIT8( KKeypad, "Keypad" );
_LIT8( KNand, "Nand" );
_LIT8( KPrimaryDisplay, "PriDisp" );
_LIT8( KSecondaryDisplay, "SecDisp" );
_LIT8( KSecurity, "Security" );
_LIT8( KUsbExt, "UsbExtension" );
_LIT8( KUsbDriver, "UsbDriver" );
_LIT8( KDigitiser, "Digitiser" );
_LIT8( KMmc, "Mmc" );
_LIT8( KSd, "Sd" );
_LIT8( KHdd, "Hdd" );
_LIT8( KCustom, "Custom" );
_LIT8( KJoystick, "Joystick" );
_LIT8( KLight, "Light" );
_LIT8( KSwitch, "Switch" );
_LIT8( KQwerty, "Qwerty" );
_LIT8( KPanicScreen, "PanicScreen" );
_LIT8( KBootFigure0, "BootFigure0" );
_LIT8( KBootFigure1, "BootFigure1" );
_LIT8( KThermalSensor, "ThermalSensor" );
_LIT8( KCameraHWA, "CameraHWA" );
_LIT8( KCameraDriver, "CameraDriver" );
_LIT8( KDisplayDriver, "DisplayDriver" );
_LIT8( KPowerModel, "PowerController" );
_LIT8( KTwistDriver, "TwistDriver" );
_LIT8( KCameraStaticData, "CameraStaticData" );
_LIT8( KAccelerometer, "Accelerometer" );
_LIT8( KExpander, "KeypadExpander" );
_LIT8( KPowerTouareg, "PowerTouareg" );
_LIT8( KKernelDataTransferApiUsb, "UsbDataIf" );
_LIT8( KNaviScroll, "NaviScroll" );
_LIT8( KTouchIC, "TouchIC" );

/** Array for pointers (for registered descriptors) */
const TDesC8* const KPtrArray[] =
    {
    &KTvOut,
    &KKeypad,
    &KNand,
    &KPrimaryDisplay,
    &KSecondaryDisplay,
    &KSecurity,
    &KUsbExt,
    &KUsbDriver,
    &KDigitiser,
    &KMmc,
    &KSd,
    &KHdd,
    &KCustom,
    &KJoystick,
    &KLight,
    &KSwitch,
    &KQwerty,
    &KPanicScreen,
    &KBootFigure0,
    &KBootFigure1,
    &KThermalSensor,
    &KCameraHWA,
    &KCameraDriver,
    &KDisplayDriver,
    &KPowerModel,
    &KCameraStaticData,
    &KAccelerometer,
    &KExpander,
    &KPowerTouareg,
    &KKernelDataTransferApiUsb,
    &KNaviScroll,
    &KTouchIC
    };

/** Maximum number of items in an array */
const TUint KPtrArraySize = ( sizeof( KPtrArray ) / sizeof( KPtrArray[0] ) );

// Macros

// Data types

// Function prototypes

// Forward declarations

// Class declaration

/**
@brief Class description
/**

Generic APE-side library for kernel side clients.

*/
class GApe
    {
    public:
        /**
            Return an instance to GApe interface. This method returns the
            only GApe instance system can have, it is not possible to create
            new instances of this class.

            @return GApe* An instance to GApe class
        */
        static GApe* Instance();

        /**
            Save pointer to internal array e.g.

            @code
            TInt ret = GApe::SetPtr( KTvOut, this );
            if ( ret != KErrNone )
                {
                // Error handling...
                }
            @endcode

            @param  aName   Name used for registering pointer
            @param  aPtr    Pointer to be saved

            @return KErrNone, if successful. KErrAlreadyExists, if the pointer
                    is already registered. KErrNotFound, if the 'aName' is not
                    a valid name.
        */
        IMPORT_C static TInt SetPtr(const TDesC8& aName, TAny* const aPtr);

        /**
            Get pointer from internal array e.g.

            @code
            DTvOut* tvout = static_cast<DTvOut*>( GApe::GetPtr( KTvOut ) );
            if ( tvout )
                {
                // Usage...
                }
            @endcode

            @param  aName   Name of the registered pointer

            @return Pointer to requested item. May also return NULL, which
                    indicates that the pointer is not registered or the name
                    is not valid.
        */
        IMPORT_C static TAny* GetPtr(const TDesC8& aName);

    private:
        /**
            Defined as a private to prevent clients to create own instances
            from this class.
        */
        GApe();

        /**
            Defined as a private to prevent clients to delete the instance of
            this class.
        */
        ~GApe();

    private:
        /** Array where the registered pointers are stored */
        TAny* iPtrArray[ KPtrArraySize ];

        /** Internal instance to allow static methods to access instance
            data. */
        static GApe* GApePtr;
    };

// Global Function Prototypes

// Inline Functions

// Namespace

#endif // __GAPE_H__

// End of File
