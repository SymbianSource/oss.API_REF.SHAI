/*
  magickey_chipset_api.h

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
@brief Chipset API H Template

This is a header template for Chipset API work. This template should not be
used as a normal code template because the location of where the API is
documented is different in normal coding style! Doxygen commenting style tries
to be similar what Symbian is using for their kernel side development.

You can define here also the scope of the whole API see below, or you can
define the scope separately before the class or even before the function if
that is needed.

@publishedDeviceAbstraction
*/

#ifndef __MAGICKEY_CHIPSET_API_H__
#define __MAGICKEY_CHIPSET_API_H__


// Include files
// Constants
/**
* Magic key press handling P&S Uid.
*/
const TUid KUidMagicKeyPress = {0x10204CE3};

/**
* Information was the MagicKey1 pressed when the key driver was started.
* The keypad driver that is handling MagicKey1 have to publish the information.
* @value one of TMagicKeyState enumerations.
* @type RProperty::EInt
*/
const TUint32 KMagicKey1Info = 0x00000001;

/**
* Information was the MagicKey2 pressed when the key driver was started.
* The keypad driver that is handling MagicKey2 have to publish the information.
* @value one of TMagicKeyState enumerations.
* @type RProperty::EInt
*/
const TUint32 KMagicKey2Info = 0x00000002;

/**
* Information was the MagicKey3 pressed when the key driver was started.
* The keypad driver that is handling MagicKey3 have to publish the information.
* @value one of TMagicKeyState enumerations.
* @type RProperty::EInt
*/
const TUint32 KMagicKey3Info = 0x00000003;

// Macros
// Data types


/**
* Enums for checking the magic keys states
*/
enum TMagicKeyState
    {
    EMagicKeyUp,	// The magic key was not pressed when the key driver was started
    EMagicKeyDown	// The magic key was pressed when the key driver was started
    };

// Function prototypes
// Forward declarations
// Class declaration


#endif // __MAGICKEY_CHIPSET_API_H__
