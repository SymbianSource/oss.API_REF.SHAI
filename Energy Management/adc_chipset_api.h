/*
  adc_chipset_api.h

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
 @brief ADC chipset API.
 
 For details see document "EM Chipset API Specification"

 @publishedDeviceAbstraction
 */

#ifndef ADC_CHIPSET_API_H
#define ADC_CHIPSET_API_H

/* ---------------------------------------------------------------------------
 *
 * CONSTANTS
 *
 */

/* Battery Voltage (VBAT) */
#define HAL_ADC_CHIPSET_VBAT 0x01

/* Battery Size Identification (BSI) */
#define HAL_ADC_CHIPSET_BSI 0x04

/* Battery TEMPerature (BTEMP) */
#define HAL_ADC_CHIPSET_BTEMP 0x05

/* Power Amplifier TEMPerature (PATEMP) */
#define HAL_ADC_PATEMP 0x09

/* Battery current (positive: current from battery to phone, negative: current running to the battery) */
/* Ibat can be implemented as a physical or logical adc channel, in case of logical this channel is still used in calibration */
#define HAL_ADC_CHIPSET_IBAT 0x0E

/* PWB Temperature */
#define HAL_ADC_CHIPSET_PWBTEMP 0x22

/* Main channel  */
#define HAL_ADC_MAIN_CAL 0xFE

#include <kernel.h>
#include <platform.h>

/* ---------------------------------------------------------------------------
 *
 * TYPES
 *
 */

/*
 * Type definition for the call-back function used writing to
 *  asynchronous em callback.
 */
typedef void (*HAL_ADC_CALLBACK)(TUint event, TInt p1, TAny* p2);

/* ---------------------------------------------------------------------------
 *
 * FUNCTIONAL PROTOTYPES AND MACROS
 *
 */
class TAdcHal
    {

    // Class declaration

    /**
     Implements AdcHal chipset
     */

public:

    enum THalAdcCalType
        {
        EHalAdcCalAppliedVoltage = 1,
        EHalAdcCalAppliedCurrent,
        EHalAdcCalSensor
        };

    /* ---------------------------------------------------------------------------
     *
     * DATA STRUCTURES
     *
     */

    class HAL_ADC_CAL_DATA_ELEMENT_TYPE
        {
    public:
        TUint8 Channel;
        TUint16 RawReading;
        THalAdcCalType Type;
        TInt32 ReferenceValue;
        TInt32 Identification;
        };

    class HAL_ADC_CAL_DATA_TYPE
        {
    public:
        TUint16 NumberOfElements;
        HAL_ADC_CAL_DATA_ELEMENT_TYPE *Element;
        };

    /*
     * Constructor:
     */

    TAdcHal();

    /*
     * Extension entrypoint
     */
    IMPORT_C static TAdcHal* hal_adc_entry_point();

    /* Initialisation */
    virtual void hal_adc_init();

    /* Read/convert raw values */
    virtual TInt hal_adc_raw_read(TUint channel, TUint* value,
            HAL_ADC_CALLBACK adc_handler, TAny* context);
    virtual TInt hal_adc_unit_convert(TUint channel, TUint value);

    /* Calibration depending function */
    virtual TInt hal_adc_unit_read(TUint channel, TInt* value,
            HAL_ADC_CALLBACK adc_handler, TAny* context);
    virtual TInt hal_adc_cal_unit_conv(TUint channel, TUint rawval,
            TInt *unitval);
    virtual TInt hal_adc_cal_get(TUint8 channel, TUint *identification,
            TInt *value1, TInt *value2, TInt *value3);
    virtual TInt hal_adc_cal_set(HAL_ADC_CAL_DATA_TYPE *data);
    virtual TInt hal_adc_cal_store();
    virtual TInt hal_adc_unit_lock_channel(TUint channel, TBool action,
            TInt value);
    };

#endif /* ADC_CHIPSET_API_H */
/* End of Include File */
