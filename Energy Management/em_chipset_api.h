/*
  em_chipset_api.h

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
 @brief Energy management chipset API

 @publishedDeviceAbstraction
 */

#ifndef EM_CHIPSET_API_H
#define EM_CHIPSET_API_H

#include <kernel.h>
#include <platform.h>

/* ---------------------------------------------------------------------------
 *
 * TYPES
 *
 */

/**
 * Type definition for the call-back function used writing to
 *  asynchronous em callback. Callback is executed in the EM chipset's context.
 */
typedef void (*HAL_EM_CALLBACK)(TUint event, TInt p1, TAny* p2);

/* ---------------------------------------------------------------------------
 *
 * FUNCTIONAL PROTOTYPES AND MACROS
 *
 */

class TEmHal
    {
    // Class declaration

    /**
     Implements EmHal chipset
     */
public:

    /* ---------------------------------------------------------------------------
     *
     * CONSTANTS
     *
     */

    enum THalEmChaEvtType
        {
        EHalEMChaChargeStarted = 1,
        EHalEmChaChargeStopped,
        EHalEamChaChargeReady,
        EHalEamChaChargeChargerType,
        EHalEamChaChargeFull,
        EHalEamChaChargeError
        };

    enum THalEmChaChargerType
        {
        EHalEmChaChargerNone = 1,
        EHalEmChaChargerSpecial,
        EHalEmChaChargerDynamo
        };

    enum THalEmChaSource
        {
        EHalEmChaSourceDynamo = 1, 
        EHalEmChaSourceUsb
        };

    enum THalEmIbatEvtType
        {
        EHalEmChaIbatStarted = 1,
        EHalEmChaIbatStopped,
        EHalEmChaIbatSampling,
        EHalEmChaIbatError
        };

    enum THalEmVbatEvtType
        {
        EHalEmVbatTxOn = 1,
        EHalEmVbatTxOff,
        EHalEmVbatChOn,
        EHalEmVbatChOff,
        EHalEmVbatError
        };

    enum THalEmBsiEvtType
        {
        EHalEmBsiFloating = 1
        };

    enum THalEmDbiEvtType
        {
        EHalEmDbiAuthenticationOk = 1,
        EHalEmDbiAuthenticationFailed,
        EHalEmDbiReadReady,
        EHalEmDbiReadError,
        EHalEmDbiWriteReady,
        EHalEmDbiWriteError
        };

    /*
     * Constructor:
     */

    TEmHal();

    /*
     * Extension entrypoint
     */

    IMPORT_C static TEmHal* hal_em_entry_point();

    /*
     * INIT (setup):
     */

    virtual void hal_em_init(HAL_EM_CALLBACK cha_handler,
            HAL_EM_CALLBACK ibat_handler, HAL_EM_CALLBACK vbat_handler,
            HAL_EM_CALLBACK bsi_handler);

    /*
     * CHARGING:
     */
    virtual TInt hal_em_cha_charge(TInt action);
    virtual TInt hal_em_cha_charge_pause(TInt action);
    virtual TInt hal_em_cha_set_target_voltage(TInt mV);
    virtual TInt hal_em_cha_set_termination_current(TInt mA);
    virtual TInt hal_em_cha_set_in_current(TInt mA);
    virtual TInt hal_em_cha_set_out_current(TInt mA);
    virtual TInt hal_em_cha_set_min_vbus_volt(TInt mv);
    virtual TInt hal_em_cha_set_charging_source(THalEmChaSource source);

    /*
     * IBAT
     */
    virtual TInt hal_em_ibat_read();
    virtual TUint hal_em_ibat_sample_time();
    virtual TUint hal_em_ibat_avg_time_get();
    virtual TInt hal_em_ibat_avg_time_set(TUint number);
    virtual TInt hal_em_ibat_avg_get();
    virtual TInt hal_em_ibat_avg_start();
    virtual TInt hal_em_ibat_avg_stop();
    virtual TInt hal_em_ibat_avg_state_get();

    /*
     * VBAT
     */

    virtual TInt hal_em_vbat_initial();
    virtual TInt hal_em_vbat_read(TUint *value);
    virtual TInt hal_em_vbat_sync(TInt action);

    /*
     * BTEMP
     */
    virtual TInt hal_em_btemp_read(TUint *value);

    /*
     * BSI
     */
    virtual TInt hal_em_bsi_read(TUint *value);

    /* WATCHDOG */
    virtual void hal_em_watchdog();

    /* DBI */

    virtual TInt hal_em_dbi_init(HAL_EM_CALLBACK dbi_handler);
    virtual TInt hal_em_dbi_authenticate(TUint8 *challenge,
            TUint8 challengelength, TUint8 *response, TUint8 responselength);
    virtual TInt
            hal_em_dbi_read(TUint address, TUint length, TUint8* readbuf);
    virtual TInt hal_em_dbi_write(TUint address, TUint length,
            TUint8* writebuf);
    };

#endif /* EM_CHIPSET_API_H */
/* End of Include File */
