/*
  mmmCtrl_chipset_api.h

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
@brief mmm Ctrl Chipset API H

This is the header file for Muxed Mass Memory Control chipset API.

@publishedDeviceAbstraction
*/

#ifndef __MMM_CTRL_CHIPSET_API_H__
#define __MMM_CTRL_CHIPSET_API_H__

#ifdef __cplusplus
extern "C" {

#ifndef SYMOS_OAM
#define SYMOS_OAM
#endif

#endif

#if defined(SYMOS_OAM)   /* do not use SYMOS_OAM -flag inside chipset API code */
#define MMM_CTRL_SYMBIAN
#else
    /* these definitions are for non symbian code */
typedef unsigned long int TUint32;
typedef unsigned char TUint8;
typedef unsigned int TUint;
typedef signed int TInt;
typedef void TAny;
#endif

/* Include files */

    /*  all the needed include files must be included by C or CPP -file */
    /*  before this header file.                                        */

/* Constants */

    /* Parameter values for mmmCtrlStateSet */
#define mmmCtrlDeviceOff                 0x0000
#define mmmCtrlBusControllerReset        0x0001
#define mmmCtrlBusModeNormal             0x0002

    /* return values for mmmCtrlLastErrorGet() -function     */
#define mmmCtrlErrorNone                ((TUint32)mmmCtrlOk)
    /* the rest of the error codes are defined by the vendor */
    /* to their own header file.                             */

    /* Error return value for mmmCtrlIntPinGet() –function   */
#define mmmCtrlNonValid                 (-1)

    /* Error return value for mmmCtrlBaseAddressGet() –function */
#define mmmCtrlInvalidAddress	        (TAny*)(-1)

/* Macros */

/* Data types */

typedef enum
    {
    mmmCtrlOk = 0,               /* status OK */
    mmmCtrlNotSupported,         /* feature not supported */
    mmmCtrlDmaOnGoing,           /* DMA started */
    mmmCtrlFail                  /* error has happened */
    }    TmmmCtrlStatus;

typedef enum
    {
    mmmCtrlVirtualAddress = 0,   /* Virtual base address of device */
    mmmCtrlPhysicalAddress       /* Physical base address of device */
    }    TmmmCtrlAddress;

    /* Function prototypes */
TmmmCtrlStatus mmmCtrlInit( void );
TUint32 mmmCtrlVersionGet( void );
TAny* mmmCtrlBaseAddressGet( TmmmCtrlAddress address );
TmmmCtrlStatus mmmCtrlStateSet( TUint32 state );
TInt mmmCtrlIntPinGet( void );
TmmmCtrlStatus mmmCtrlMemCpy( TAny* target, TAny* source, TUint32 n,
    void (*cb)(TmmmCtrlStatus) );
TUint32 mmmCtrlLastErrorGet( void );

/* Class declaration */

#ifdef __cplusplus
}
#endif

#endif /* __MMM_CTRL_CHIPSET_API_H__  */
