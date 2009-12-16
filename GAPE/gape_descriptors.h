/*
Nokia/Devices/R&D/SD/SSS
CONFIDENTIAL
Deliverable software



            GAPE_DESCRIPTORS.H
            --------------------------------

            SW Include Document - Symbian OS



Document identification and location in Synergy/CM

Database:           ...

Object (this information is substituted by Synergy/CM):
    %name:           %
    %cvtype:         %
    %instance:       %
    %version:        %
    %date_modified:  %

Copyright (c) Nokia. This material, including documentation and any related
computer programs, is protected by copyright controlled by Nokia.
All rights are reserved. Copying, including reproducing, storing, adapting or
translating, any or all of this material requires the prior written consent
of Nokia. This material also contains confidential information, which may not
be disclosed to others without the prior written consent of Nokia.
*/

/** @file
@brief gape_descriptors.h

This a header file of gape_descriptors.h

@publishedDeviceAbstraction
*/
#ifndef __GAPE_DESCRIPTORS_H__
#define __GAPE_DESCRIPTORS_H__


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
_LIT8( KTouchIC2, "TouchIC2" );
_LIT8( KExpander2, "KeypadExpander2" );
_LIT8( KAddriver, "KAddriver" );
_LIT8( KOFN, "OFN" );
_LIT8( KCustomRTC, "CustomRtc" );

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
    &KTouchIC,
    &KTouchIC2,
    &KExpander2, 
    &KAddriver,
    &KOFN,
    &KCustomRTC
    };
    
    
    /** Maximum number of items in an array */
const TUint KPtrArraySize = ( sizeof( KPtrArray ) / sizeof( KPtrArray[0] ) );


#endif    // __GAPE_DESCRIPTORS_H__

// end of file
