/*
  pm_definitions_chipset_api.h

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
@brief PM Definitions Chipset API H

Purpose of this header is to describe the protocol that should be followed by
Nokia and chipset vendor regarding some of the parameters used in power
management chipset API specifications. The aim of this definition is to specify
platform specific entities in an abstract way and at the same time, providing an
option for some level of granularity for possible performance optimizations.
Definition of the following parameters is included in this document.

@publishedDeviceAbstraction
*/

#ifndef PM_DEFINITIONS_CHIPSET_API_H
#define PM_DEFINITIONS_CHIPSET_API_H


// Include files

#include <kern_priv.h>


// Constants

/**
Latency resource minimum value
*/
const TInt KMinLatency = 0;

/**
Latency resource maximum values
*/
const TInt KMaxLatency = KMaxTInt32;

/**
Maximum level of any performance resource
*/
const TInt KPerfMax = 100;

/**
CPU normal performance level
*/
const TInt KPerfNormalCpu = 100;

/**
Memory normal performance level
*/
const TInt KPerfNormalMemory = 100;

/**
Bus normal performance level
*/
const TInt KPerfNormalBus = 100;

/**
Audio HWA normal performance level
*/
const TInt KPerfNormalHwaAudio = 100;

/**
Graphics HWA normal performance level
*/
const TInt KPerfNormalHwaGfx = 100;

/**
Imaging HWA normal performance level
*/
const TInt KPerfNormalHwaImg = 100;

/**
Video HWA normal performance level
*/
const TInt KPerfNormalHwaVideo = 100;

/**
Modem normal performance level
*/
const TInt KPerfNormalModem = 100;

/**
Minimum level of any performance level
*/
const TInt KPerfMin = 0;

// Data types

/**
Symbian power resource IDs
*/
enum TPowerRes
    {
    EPwrResLatency      = 0,            /**< latency                        */
    EPwrResAnalogAcc    = 0,            /**< analog accessory               */
    EPwrResBT           = 0,            /**< bluetooth                      */
    EPwrResCamera1      = 0,            /**< camera#1                       */
    EPwrResCamera2      = 0,            /**< camera#2                       */
    EPwrResDBR          = 0,            /**< DBR                            */
    EPwrResDigMic       = 0,            /**< digital mic                    */
    EPwrResDisplay1     = 0,            /**< display#1                      */
    EPwrResDisplay2     = 0,            /**< display#2                      */
    EPwrResEAR          = 0,            /**< EAR                            */
    EPwrRes_eMMC        = 0,            /**< eMMC                           */
    EPwrResFMRadioTx    = 0,            /**< FM radio transmitter           */
    EPwrResFMRadioRx    = 0,            /**< FM radio receiver              */
    EPwrResGPS          = 0,            /**< GPS                            */
    EPwrResHSUSB        = 0,            /**< HS-USB                         */
    EPwrResIHF          = 0,            /**< IHF                            */
    EPwrResIrDA         = 0,            /**< IrDA                           */
    EPwrResKeypad       = 0,            /**< keypad                         */
    EPwrResMassStorage  = 0,            /**< mass storage                   */
    EPwrResMemCard      = 0,            /**< memory card                    */
    EPwrResMic          = 0,            /**< mic                            */
    EPwrResNFC          = 0,            /**< NFC                            */
    EPwrResSIMIF        = 0,            /**< SIM IF                         */
    EPwrResTouchScreen  = 0,            /**< touch screen                   */
    EPwrResTVOut        = 0,            /**< TV out                         */
    EPwrResULP          = 0,            /**< ULP                            */
    EPwrResUSBOTG       = 0,            /**< USB OTG                        */
    EPwrResUWB          = 0,            /**< UWB                            */
    EPwrResVibra        = 0,            /**< vibra                          */
    EPwrResWiMax        = 0,            /**< WiMax                          */
    EPwrResWLAN         = 0,            /**< WLAN                           */
    EPwrResHDMI         = 0,            /**< HDMI                           */
    EPwrResUSB_UICC_IF  = 0,            /**< USB UICC IF                    */
    EPwrResExtClk1      = 0,            /**< External clock 1               */
    EPwrResExtClk2      = 0,            /**< External clock 2               */
    EPwrResExtClk3      = 0,            /**< External clock 3               */
    EPwrResExtClk4      = 0,            /**< External clock 4               */
    EPwrResExtClk5      = 0,            /**< External clock 5               */
    EPwrResExtClk6      = 0,            /**< External clock 6               */
    EPwrResExtClk7      = 0,            /**< External clock 7               */
    EPwrResExtClk8      = 0,            /**< External clock 8               */
    EPwrResExtClk9      = 0,            /**< External clock 9               */
    EPwrResExtClk10     = 0,            /**< External clock 10              */
    EPwrResExtVoltage1  = 0,            /**< External voltage 1             */
    EPwrResExtVoltage2  = 0,            /**< External voltage 2             */
    EPwrResExtVoltage3  = 0,            /**< External voltage 3             */
    EPwrResExtVoltage4  = 0,            /**< External voltage 4             */
    EPwrResExtVoltage5  = 0,            /**< External voltage 5             */
    EPwrResExtVoltage6  = 0,            /**< External voltage 6             */
    EPwrResExtVoltage7  = 0,            /**< External voltage 7             */
    EPwrResExtVoltage8  = 0,            /**< External voltage 8             */
    EPwrResExtVoltage9  = 0,            /**< External voltage 9             */
    EPwrResExtVoltage10 = 0,            /**< External voltage 10            */
    };

/**
Symbian performance resource IDs
*/
enum TPerfRes
    {
    EPwrResPerfCpu      = 0,            /**< CPU performance                */
    EPwrResPerfMemory   = 0,            /**< Main memory                    */
    EPwrResPerfBus      = 0,            /**< Main interconnect bus          */
    EPwrResPerfHwaAudio = 0,            /**< Audio HW accelerator           */
    EPwrResPerfHwaGfx   = 0,            /**< Graphics HW accelerator        */
    EPwrResPerfHwaImg   = 0,            /**< Imaging HW accelerator         */
    EPwrResPerfHwaVideo = 0,            /**< Video HW accelerator           */
    EPwrResPerfModem    = 0             /**< Modem                          */
    };

/**
Possible resource levels
*/
enum TDevState
    {
    EDevD0  = 0xf,                      /**< (fixed) highest power state    */
    EDevD1  = 0xe,                      /**< (fixed)                        */
    EDevD2  = 0xd,                      /**< (fixed)                        */
    EDevD3  = 0xc,                      /**< (fixed)                        */
    EDevD4  = 0xb,                      /**< (fixed)                        */
    EDevD5  = 0xa,                      /**< (fixed)                        */
    EDevD6  = 0x9,                      /**< (fixed)                        */
    EDevD7  = 0x8,                      /**< (fixed)                        */
    EDevD8  = 0x7,                      /**< (fixed)                        */
    EDevD9  = 0x6,                      /**< (fixed)                        */
    EDevD10 = 0x5,                      /**< (fixed)                        */
    EDevD11 = 0x4,                      /**< (fixed)                        */
    EDevD12 = 0x3,                      /**< (fixed)                        */
    EDevD13 = 0x2,                      /**< (fixed)                        */
    EDevD14 = 0x1,                      /**< (fixed)                        */
    EDevD15 = 0x0                       /**< (fixed) lowest power state     */
    };

/**
Power is fully off. Least power consuming state.
*/
const TInt KDevOff = EDevD15;

/**
Device is in reset state.
*/
const TInt KDevReset = EDevD14;

/**
Device is in retention state
*/
const TInt KDevRetention = EDevD13;

/**
Device is in sleep state.
An intermediate state whose definition varies by device.
*/
const TInt KDevSleep = EDevD12;

/**
Device is in idle state.
An intermediate state whose definition varies by device.
*/
const TInt KDevIdle = EDevD2;

/**
Device is capable itself to control power states.
*/
const TInt KDevAuto = EDevD1;

/**
Power is fully on.
*/
const TInt KDevOn = EDevD0;

/**
The set of HW blocks whose load is monitored by the DVFS algorithms. Each
scalable domain may consist of one or more of such blocks.
*/
enum TDvfsMonitor
    {
    EDvfsMonCpu1     = 0,               /**< General purpose CPU 1          */
    EDvfsMonCpu2     = 0,               /**< General purpose CPU 2          */
    EDvfsMonMemory   = 0,               /**< Main program memory (RAM)      */
    EDvfsMonBus      = 0,               /**< Main bus                       */
    EDvfsMonDma      = 0,               /**< System DMA                     */
    EDvfsMonAudio    = 0,               /**< Audio HW accelerator           */
    EDvfsMonHwaGfx   = 0,               /**< Graphics HW accelerator        */
    EDvfsMonHwaImg   = 0,               /**< Imaging HW accelerator         */
    EDvfsMonHwaVideo = 0,               /**< Video HW accelerator           */
    EDvfsMonModem    = 0,               /**< Modem                          */
    EDvfsMonResv0    = 0,               /**< Reserved                       */
    EDvfsMonResv1    = 0,               /**< Reserved                       */
    EDvfsMonResv2    = 0,               /**< Reserved                       */
    EDvfsMonResv3    = 0,               /**< Reserved                       */
    EDvfsMonResv4    = 0,               /**< Reserved                       */
    EDvfsMonResv5    = 0,               /**< Reserved                       */
    EDvfsMonResv6    = 0,               /**< Reserved                       */
    };

/**
Global (system wide) sleep states from a software point of view. The system
shall have up to 16 different sleep states. EGblG0 is the most power consuming
and EGblG1S15 is the least power consuming states.
*/
enum TGlobalState
    {
    EGblG0    = 0xf,                    /**< (fixed) highest power state    */
    EGblG1S1  = 0xe,                    /**< (fixed)                        */
    EGblG1S2  = 0xd,                    /**< (fixed)                        */
    EGblG1S3  = 0xc,                    /**< (fixed)                        */
    EGblG1S4  = 0xb,                    /**< (fixed)                        */
    EGblG1S5  = 0xa,                    /**< (fixed)                        */
    EGblG1S6  = 0x9,                    /**< (fixed)                        */
    EGblG1S7  = 0x8,                    /**< (fixed)                        */
    EGblG1S8  = 0x7,                    /**< (fixed)                        */
    EGblG1S9  = 0x6,                    /**< (fixed)                        */
    EGblG1S10 = 0x5,                    /**< (fixed)                        */
    EGblG1S11 = 0x4,                    /**< (fixed)                        */
    EGblG1S12 = 0x3,                    /**< (fixed)                        */
    EGblG1S13 = 0x2,                    /**< (fixed)                        */
    EGblG1S14 = 0x1,                    /**< (fixed)                        */
    EGblG1S15 = 0x0                     /**< (fixed) lowest power state     */
    };

/**
The least power consuming mode of the chipset (also called the deep sleep).
*/
const TInt KGblDeepSleep = EGblG1S15;   /**< (fixed)                        */

/**
Power state when at least one of the generic CPUs are active (not in WFI state).
This is the most power consuming mode of the chipset.
*/
const TInt KGblActive    = EGblG0;      /**< (fixed)                        */

#endif // PM_DEFINITIONS_CHIPSET_API_H
