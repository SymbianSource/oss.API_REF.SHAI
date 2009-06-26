/*
  audio_hw_control_chipset_api.h

  Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/

#ifndef AUDIO_HWCTRL_CHIPSET_API_H
#define AUDIO_HWCTRL_CHIPSET_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Each OMX header must include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully 
 */

#include <OMX_Audio.h>


/* structures and enums used by OMX interface */

 typedef enum OMX_AUDIO_HWREGISTERTYPE { 
     OMX_AUDIO_IO = 0,
     OMX_AUDIO_I2C,
     OMX_AUDIO_SLIMBUS,
     OMX_AUDIO_CBUS = 0xFFFF     
 } OMX_AUDIO_HWREGISTERTYPE;
 
 typedef struct OMX_AUDIO_REGBANKDESCRIPTORTYPE { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nRegBankIndex;   
     OMX_U32 nLogicalStartAddr;
     OMX_U32 nLogicalEndAddr;
     OMX_AUDIO_HWREGISTERTYPE eRegBankType;
       
 } OMX_AUDIO_REGBANKDESCRIPTORTYPE;

 typedef enum OMX_AUDIO_HWLOOPSTYPE { 
     OMX_AUDIO_NOLOOP = 0,
     OMX_AUDIO_SIDETONE_LOOP = 0xFFFF
     /* rest of HW loops are to be defined on a vendor specific basis */
     
 } OMX_AUDIO_HWLOOPSTYPE;

 typedef enum OMX_AUDIO_HWOPERATIONTYPE { 
     OMX_AUDIO_NOOP = 0,
     OMX_AUDIO_16BIT_SINGLE_READ,
     OMX_AUDIO_16BIT_SINGLE_WRITE,
     OMX_AUDIO_32BIT_SINGLE_READ,
     OMX_AUDIO_32BIT_SINGLE_WRITE,
     OMX_AUDIO_16BIT_MULTI_READ,
     OMX_AUDIO_16BIT_MULTI_WRITE,
     OMX_AUDIO_32BIT_MULTI_READ,
     OMX_AUDIO_32BIT_MULTI_WRITE,
     OMX_AUDIO_16BIT_BURST_MULTI_READ,
     OMX_AUDIO_16BIT_BURST_MULTI_WRITE,
     OMX_AUDIO_32BIT_BURST_MULTI_READ,
     OMX_AUDIO_32BIT_BURST_MULTI_WRITE = 0xFFFF     
 } OMX_AUDIO_HWOPERATIONTYPE;

 
 typedef enum OMX_AUDIO_HWCTRL_STATUSTYPE { 
     OMX_AUDIO_OK = 0,
     OMX_AUDIO_FAIL,
     /* if callback facility is somehow solved in OpenMAX IL for 
        getconfig/setconfig parameter calls, it is expected */
     /* to have here extra status information that can be returned 
        for e.g. multi-read/write commands */
     OMX_AUDIO_NOT_SUPPORTED = 0xFFFF     
 } OMX_AUDIO_HWCTRL_STATUSTYPE;



/* Configuration parameters */

typedef struct OMX_AUDIO_CONFIG_POWERTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_U32 nChannel;
     OMX_BOOL bPower;
} OMX_AUDIO_CONFIG_POWERTYPE;


typedef struct OMX_AUDIO_CONFIG_VOLUMERAMPTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_U32 nChannel;
     OMX_BOOL bLinear;
     OMX_BS32 sStartVolume;
     OMX_BS32 sEndVolume;
     OMX_TICKS nRampDuration;
     OMX_BOOL bRampTerminate;
     OMX_BS32 sCurrentVolume;
     OMX_TICKS nRampCurrentTime;
     OMX_TICKS nRampMinDuration;
     OMX_TICKS nRampMaxDuration;
     OMX_U32 nVolumeStep;
 } OMX_AUDIO_CONFIG_VOLUMERAMPTYPE;


 typedef struct OMX_AUDIO_CONFIG_BURSTCONTROLTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;            
     OMX_BOOL bBurstControl;
     OMX_BOOL bStatus;
 } OMX_AUDIO_CONFIG_BURSTCONTROLTYPE;

 typedef struct OMX_AUDIO_CONFIG_REGISTERBANKQUERYTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;   
     OMX_U16 nNumRegisterBanks;           
 } OMX_AUDIO_CONFIG_REGISTERBANKQUERYTYPE;


 typedef enum OMX_AUDIO_HWREGISTERTYPE { 
     OMX_AUDIO_IO = 0,
     OMX_AUDIO_I2C,
     OMX_AUDIO_SLIMBUS,
     OMX_AUDIO_CBUS = 0xFFFF     
 } OMX_AUDIO_HWREGISTERTYPE;
 
 
 typedef struct OMX_AUDIO_REGBANKDESCRIPTORTYPE { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nRegBankIndex;   
     OMX_U32 nLogicalStartAddr;
     OMX_U32 nLogicalEndAddr;
     OMX_AUDIO_HWREGISTERTYPE eRegBankType;
       
 } OMX_AUDIO_REGBANKDESCRIPTORTYPE;

 typedef struct OMX_AUDIO_CONFIG_REGISTERBANKTABLETYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;   
     OMX_U16 nNumRegisterBanks; 
     OMX_AUDIO_REGBANKDESCRIPTORTYPE RegBankDescriptorTable;     
 } OMX_AUDIO_CONFIG_REGISTERBANKTABLETYPE;


 typedef struct OMX_AUDIO_CONFIG_CUSTOMHWCONTROLTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;   
     OMX_AUDIO_HWCTRL_STATUSTYPE eStatus;
     OMX_AUDIO_HWOPERATIONTYPE eHwOperation;
     OMX_AUDIO_HWREGISTERTYPE eRegisterType;
     OMX_U16 nDataCount;
     OMX_U32 nLogicalAddress;
     OMX_U16 nData;     
 } OMX_AUDIO_CONFIG_CUSTOMHWCONTROLTYPE;

typedef struct OMX_AUDIO_CONFIG_HWLOOPSUPPORTTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;
     OMX_U32 nSupportedLoops;    
     OMX_AUDIO_HWLOOPSTYPE eLoopIndex;
         
 } OMX_AUDIO_CONFIG_HWLOOPSUPPORTTYPE;

typedef struct OMX_AUDIO_CONFIG_HWLOOPCONTROLTYPE  { 
     OMX_U32 nSize;                                    
     OMX_VERSIONTYPE nVersion;                   
     OMX_U32 nPortIndex;   
     OMX_AUDIO_HWLOOPSTYPE eLoopIndex;
     OMX_U32 nChannel;
     OMX_BOOL bControlSwitch;
     OMX_BOOL bLinear;
     OMX_BS32 sLoopVolume;
     
 } OMX_AUDIO_CONFIG_HWLOOPCONTROLTYPE;



/* End of OMX part */

/************  non-OMX interface definition **************/  

/* types and constants used by non-OMX APIs */

/* channel ID denoting special case of all channels being selected 
   where possible */       
#define AUDIO_COMMON_CHANNEL_ALL	0x7FFFFFFF

typedef enum AUDIO_COMMON_SWITCH { 
     AUDIO_COMMON_OFF = 0,
     AUDIO_COMMON_ON,  
     AUDIO_COMMON_UNSUPPORTED = 0xFFFF     
 } AUDIO_COMMON_SWITCH;


typedef enum AUDIO_COMMON_STATUS { 
     AUDIO_COMMON_OK = 0,
     AUDIO_COMMON_FAIL,  
     AUDIO_COMMON_UNSUPPORTED = 0xFFFF     
} AUDIO_COMMON_STATUS;
        
typedef enum AUDIO_HAL_HW_LOOPS { 
     AUDIO_NOLOOP = 0,
     AUDIO_SIDETONE_LOOP = 0xFFFF
     /* rest of HW loops are to be defined on a vendor specific basis */
     
} AUDIO_HAL_HW_LOOPS;
        
typedef enum AUDIO_HAL_HW_OPERATION{ 
     AUDIO_HAL_NOOP = 0,
     AUDIO_HAL_16BIT_SINGLE_READ,
     AUDIO_HAL_16BIT_SINGLE_WRITE,
     AUDIO_HAL_32BIT_SINGLE_READ,
     AUDIO_HAL_32BIT_SINGLE_WRITE,
     AUDIO_HAL_16BIT_MULTI_READ,
     AUDIO_HAL_16BIT_MULTI_WRITE,
     AUDIO_HAL_32BIT_MULTI_READ,
     AUDIO_HAL_32BIT_MULTI_WRITE,
     AUDIO_HAL_16BIT_BURST_MULTI_READ,
     AUDIO_HAL_16BIT_BURST_MULTI_WRITE,
     AUDIO_HAL_32BIT_BURST_MULTI_READ,
     AUDIO_HAL_32BIT_BURST_MULTI_WRITE = 0xFFFF     
} AUDIO_HAL_HW_OPERATION;

typedef enum AUDIO_HAL_HW_REGISTER_TYPE { 
     OMX_AUDIO_IO = 0,
     OMX_AUDIO_I2C,
     OMX_AUDIO_SLIMBUS,
     OMX_AUDIO_CBUS = 0xFFFF     
} AUDIO_HAL_HW_REGISTER_TYPE;


/** 16 bit unsigned quantity that is 16 bit word aligned */
typedef unsigned short uint16;

/** 16 bit signed quantity that is 16 bit word aligned */
typedef signed short int16;

/** 32 bit unsigned quantity that is 32 bit word aligned */
typedef unsigned long uint32;

/** signed quantity that is 32 bit word aligned */
typedef signed long int32;

typedef struct AUDIO_HAL_REGBANK_DESCRIPTOR{ 
     uint32 reg_bank_index;   
     uint32 logical_start_addr;
     uint32 logical_end_addr;
     AUDIO_HAL_HW_REGISTER_TYPE reg_bank_type;
} AUDIO_HAL_REGBANK_DESCRIPTOR;

typedef struct AUDIO_HAL_GAIN_DESCRIPTOR  { 
     uint32 channel_index; 
     uint16 gain_index;
     uint32 linear;
     int32 min_gain;
     int32 max_gain;
     uint32 gain_step;
     uint32 analog_gain;
     
} AUDIO_HAL_GAIN_DESCRIPTOR;

typedef struct AUDIO_TIMED_RAMP_INFO  { 

      uint32 linear,
      int32 ramp_start_volume;
      int32 ramp_end_volume;
      int32 current_volume;
      uint32 current_time_hi;
      uint32 current_time_lo;
      uint32 ramp_min_duration_hi;
      uint32 ramp_min_duration_lo;
      uint32 ramp_max_duration_hi;
      uint32 ramp_max_duration_lo;
      int32 min_volume;
      int32 max_volume;
      uint32 volume_step;
     
} AUDIO_TIMED_RAMP_INFO;


/* API functions */

/* The convention for the functions will be:       */
/* <supplier>_<component>_<API function name(...)>    */

/* HAL layer */

void audio_hal_mute_control (void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                             uint32 channel_index, 
                             AUDIO_COMMON_SWITCH mute_control);

AUDIO_COMMON_SWITCH audio_hal_mute_status (uint32 channel_index);

void audio_hal_power_control (void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                             uint32 channel_index, AUDIO_COMMON_SWITCH power_control);

AUDIO_COMMON_SWITCH audio_hal_power_status(uint32 channel_index);

void audio_hal_gain_capabilities_query(uint32* num_channels, uint16* max_num_gains);

void audio_hal_gains_descriptor_query(AUDIO_HAL_GAIN_DESCRIPTOR* gain_descriptor_table);

void audio_hal_loop_gain_capabilities_query(AUDIO_HAL_HW_LOOPS* num_loops, uint16* max_num_gains);

void audio_hal_supported_loops_query (uint16* supported_loop_indexes);

void audio_hal_loop_gains_descriptor_query (AUDIO_HAL_HW_LOOPS loop_index,
                                    AUDIO_HAL_GAIN_DESCRIPTOR* gain_descriptor_table);

AUDIO_COMMON_STATUS audio_hal_gain_control (uint32 channel_index, uint16 gain_index,
                                    uint32 linear, int32 gain_value);

AUDIO_COMMON_STATUS audio_hal_gain_query (uint32 channel_index, uint16 gain_index,
                                    uint32 linear, int32* gain_value);

AUDIO_COMMON_STATUS audio_hal_loop_control(AUDIO_HAL_HW_LOOPS loop_index, AUDIO_COMMON_SWITCH loop_switch,
                                    uint16 channel_index, uint16 gain_index, uint32 linear,
                                    int32 loop_gain_value);

															             
uint16 audio_hal_registerbank_query();

void audio_hal_regbank_descriptors_query(AUDIO_HAL_REGBANK_DESCRIPTOR* register_banks);

void audio_hal_custom_hw_control (void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status, uint32 extra_status_info), 
                                 AUDIO_HAL_HW_OPERATION hw_operation, AUDIO_HAL_HW_REGISTER_TYPE register_type,
                                 uint16 num_data, uint32* address_data_sequence);

                                 
/* Sequencer layer */
void audio_sequencer_mute_control(void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                                  uint32 channel_index, AUDIO_COMMON_SWITCH mute_control);

void audio_sequencer_power_control(void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                                  uint32 channel_index, AUDIO_COMMON_SWITCH power_control);
                                  
AUDIO_COMMON_STATUS audio_sequencer_burst_control(void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                                                  AUDIO_COMMON_SWITCH burst_control);

void audio_sequencer_volume_control(void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                                     uint32 channel_index, uint32 linear, int32 volume);

void audio_sequencer_volume_query(uint32 channel_index, uint32 linear, int32* min_volume,
                                   int32* max_volume, int32* current_volume);

/* Timing critical layer */
void audio_timed_mute_control(void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                              uint32 channel_index, AUDIO_COMMON_SWITCH mute_control);
                              
void audio_timed_volume_ramp_control (void (*call_back_fn_ptr)(AUDIO_COMMON_STATUS status), 
                             uint32 channel_index, uint32 linear, int32 start_volume,
                             int32 end_volume, uint32 ramp_duration_hi, uint32 ram_duration_lo,
                             AUDIO_COMMON_SWITCH ramp_terminate);

void audio_timed_volume_ramp_query (uint32 channel_index, AUDIO_TIMED_RAMP_INFO* volume_ramp_info);


                                     

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif