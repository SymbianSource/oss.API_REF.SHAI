/*
  display_chipset_api.h

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

/**

  @mainpage
  @section intro_sec Introduction

  <p>This is the display chipset driver API document.</p>
  <p>This API hides HW differences from display (and other users) driver.
  API is not kept as binary compatible.</p>
  <p></p>
  <p>Multiclient:
  API is purposed for multiclient use. Same chipset driver should take care
  more than one client in same time. Common HW (bus) will be shared
  for two clients, that way that they cannot detect sharing.</p>
  <p></p>
  <p>Resource managing:
  Chipset driver is responsible to allocate needed power resources. Chipset driver
  should deallocate resources immediately when those are not needed. Display
  driver (top of chipset driver) does not need allocate any of power resources for
  chipset driver.</p>
  <p></p>
  <p>DVFS (Dynamic Voltage and Frequency Scaling):
  Chipset driver is responsible to allocate needed clock state and
  listening if clock will change. It is better if display driver does not
  listening (top of chipset driver) DVFS at all, for avoiding death locks.</p>
  <p></p>
  <p>Structs:
  Always when some of any struct is created, creator is responsible to fill it
  with zeroes, and should use sizeof() operator. </p>
  <p></p>
  <p>Identifier:
  Functions where is not IDENTIFIER given, and chipset driver still need to detect
  the client, it has to implement couple of methods for same function, to getting
  difference using different function pointer.
  <p></p>
  <p>Image processing stages:
  Image processing should happen in order (or output should look like this):
  [Source image] -> [Color space conversion] -> [InputScissor] -> [Mirror] ->
  [Rotate] -> [TargetArea(Scaling)] -> [Offset] -> [Blend] -> [Output]</p>
  <p></p>
*/
/** @file

Declaration of display chipset driver API

@publishedDeviceAbstraction
*/

#ifndef DISPLAY_CHIPSET_API_H
#define DISPLAY_CHIPSET_API_H

/*- Include Files  ----------------------------------------------------------*/

#include "display_chipset_os.h" /* OS specific header file, typedef etc. */

/*- Data Types --------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Error codes */
typedef enum  
    {
    DISP_ERROR_NONE,                    /**< OK */
    DISP_ERROR_FATAL,                   /**< Restart needed. Fatal error. */
    DISP_ERROR_INVALID_PARAMETER,       /**< Given parameter is not ok */
    DISP_ERROR_BUS_TIMEOUT,             /**< Possible Hw jam */
    DISP_ERROR_INVALID_BUFFER_FORMAT,   /**< Unknown buffer format */
    DISP_ERROR_BUFFER_FORMAT_MISMATCH,  /**< when target device has different format than the input hal_buffer and Hw is not capable to perform conversion */
    DISP_ERROR_OUT_OF_MEMORY,           /**< Chipset driver operation is not made, because out of memory */
    DISP_ERROR_NO_DEVICE,               /**< Device not found */
    DISP_ERROR_INVALID_SIZE,            /**< Given size parameters are too small or too big */
    DISP_ERROR_HW_IS_BUSY,              /**< Operation is not allowed, because Hw is reserved for another use */
    DISP_ERROR_USER_IS_NOT_RECOGNISED,  /**< User is not detected (parameter: identifier), or initialisiation is not done */
    DISP_ERROR_CANNOT_CLONE,            /**< If clone combination is impossible. @see dispCloneOutput() */
    DISP_ERROR_NOT_SUPPORTED,           /**< Given operation is not supported by Hw */
    DISP_ERROR_NOT_IMPLEMENTED,         /**< Given operation is not supported by Sw */
    DISP_ERROR_INVALID_NAME,            /**< Invalid name */
    DISP_ERROR_ALREADY_EXISTS,          /**< E.g.: Set twice */
    DISP_ERROR_NOT_FOUND,               /**< Something missing */
    DISP_ERROR_ALIGNMENT,               /**< Data alignment error */
    DISP_ERROR_NOT_READY,               /**< Device is not ready for operation */
    DISP_ERROR_CANCELLED,               /**< Operation cancelled */
    DISP_ERROR_NO_CLOCK,                /**< Bad clock signal */
    DISP_ERROR_BLUE,                    /**< Blue color error */
    DISP_ERROR_GREEN,                   /**< Green color error */
    DISP_ERROR_RED,                     /**< Red color error */
    DISP_ERROR_NOT_IDENTIFIED,          /**< Cannot identify HW */
    DISP_ERROR_TE_MISSED,               /**< Tearing Effect line is not detected */
    DISP_ERROR_RESET,                   /**< Reset line error */
    DISP_ERROR_DATA_LINES,              /**< Data lines error */
    DISP_ERROR_AUDIO,                   /**< HDMI audio error */
    DISP_ERROR_CEC,                     /**< CEC error */
    DISP_ERROR_DDC,                     /**< DDC error */
    DISP_ERROR_HPD,                     /**< Hot Plug Detection */
    DISP_ERROR_NO_POWER,                /**< Not powered */
    DISP_ERROR_NACK,                    /**< Not acknowledged */
    DISP_ERROR_CRC,                     /**< CRC error */
    } DISPE_ERROR;

/** Rotation and flipping */
typedef enum
    {
    DISP_ROTATION_INVALID           = 0x0000,    /**< Initialisation value, don't use */
    DISP_ROTATION_0                 = ( 1 << 0 ),/**< No rotation      */
    DISP_ROTATION_90                = ( 1 << 1 ),/**< 90 degree        */
    DISP_ROTATION_180               = ( 1 << 2 ),/**< 180 degree       */
    DISP_ROTATION_270               = ( 1 << 3 ),/**< 270 degree       */
    DISP_ROTATION_MIRROR_VERTICAL   = ( 1 << 4 ),/**< Upside down/flip */
    DISP_ROTATION_MIRROR_HORIZONTAL = ( 1 << 5 ),/**< Mirrored         */
    } DISPE_ROTATION;

/** Color format */
const uint32 KLittleEndian = 0x0;
const uint32 KBigEndian    = 0x1;
typedef enum
    {
    DISP_COLOR_FORMAT_INVALID      = 0,                          /**< Initialisation value, don't use */
    DISP_COLOR_FORMAT_XRGB8888_LE  = ( 1 << 1 )  | KLittleEndian,
    DISP_COLOR_FORMAT_XRGB8888_BE  = ( 1 << 1 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB8888_LE  = ( 1 << 2 )  | KLittleEndian,
    DISP_COLOR_FORMAT_ARGB8888_BE  = ( 1 << 2 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB8888P_LE = ( 1 << 3 )  | KLittleEndian, /** Pre-multiplied */
    DISP_COLOR_FORMAT_ARGB8888P_BE = ( 1 << 3 )  | KBigEndian,
    DISP_COLOR_FORMAT_RGB888_LE    = ( 1 << 4 )  | KLittleEndian,
    DISP_COLOR_FORMAT_RGB888_BE    = ( 1 << 4 )  | KBigEndian,
    DISP_COLOR_FORMAT_RGB565_LE    = ( 1 << 5 )  | KLittleEndian,
    DISP_COLOR_FORMAT_RGB565_BE    = ( 1 << 5 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB1555_LE  = ( 1 << 6 )  | KLittleEndian,
    DISP_COLOR_FORMAT_ARGB1555_BE  = ( 1 << 6 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB1555P_LE = ( 1 << 7 )  | KLittleEndian, /** Pre-multiplied */
    DISP_COLOR_FORMAT_ARGB1555P_BE = ( 1 << 7 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB4444_LE  = ( 1 << 8 )  | KLittleEndian,
    DISP_COLOR_FORMAT_ARGB4444_BE  = ( 1 << 8 )  | KBigEndian,
    DISP_COLOR_FORMAT_ARGB4444P_LE = ( 1 << 9 )  | KLittleEndian, /** Pre-multiplied */
    DISP_COLOR_FORMAT_ARGB4444P_BE = ( 1 << 9 )  | KBigEndian,
    DISP_COLOR_FORMAT_YCBCR422_LE  = ( 1 << 10 ) | KLittleEndian,
    DISP_COLOR_FORMAT_YCBCR422_BE  = ( 1 << 10 ) | KBigEndian,
    DISP_COLOR_FORMAT_YCBCR420_LE  = ( 1 << 11 ) | KLittleEndian,
    DISP_COLOR_FORMAT_YCBCR420_BE  = ( 1 << 11 ) | KBigEndian,
    DISP_COLOR_FORMAT_PLATFORM     = ( 1 << 12 ),                /**< Non standard, platform specific format */
    } DISPE_COLOR_FORMAT;

/** YCbCr standard bit mask */
typedef enum
    {
    DISP_COLOR_FORMAT_YCBCR_INVALID  = 0x0000,    /**< Can be set when RGB */
    DISP_COLOR_FORMAT_FULL_RANGE     = ( 1 << 0 ),/**< Full range 0-255 */
    DISP_COLOR_FORMAT_LIMITED_RANGE  = ( 1 << 1 ),/**< Limited range 16-235 */
    } DISPE_COLOR_YCBCR_BIT_MASK;

/** Colorspace - API supports one case-by-case fixed conversion matrix (FIXED) for one most used conversion */
typedef enum
    {
    DISP_COLOR_SPACE_NONE              = 0x0000,     /**< Initialisation value, don't use */
    DISP_COLOR_SPACE_LINEAR_RGB        = ( 1 << 0 ), /**< Linear color space */
    DISP_COLOR_SPACE_STANDARD_RGB      = ( 1 << 1 ), /**< sRGB, Red[0.6400, 0.3300] Green[0.3000, 0.6000] Blue[0.1500, 0.0600] White[0.3127,0.3290] */
    DISP_COLOR_FIXED_DISPLAY_CS_LINEAR = ( 1 << 2 ), /**< Fixed display color space - Buffer pixels are linearised RGB for FIXED */
    DISP_COLOR_FIXED_DISPLAY_CS        = ( 1 << 3 ), /**< Fixed display color space */
    DISP_COLOR_COORDINATES             = ( 1 << 4 ), /**< With this, Chipset driver does the conversion, according to input and output coordinates */
    DISP_COLOR_MATRIX_CONV             = ( 1 << 5 ), /**< Free 3x3 matrix conversion. @see DISPS_COLOR_SPACE_CONV_MATRIX */
    } DISPE_COLOR_SPACE;

/** Scaling */
typedef enum
    {
    DISP_SCALING_NO                 = 0x0000,    /**< No HW support for scaling */
    DISP_SCALING_NEAREST_NEIGHBOUR  = ( 1 << 0 ),/**< Style: Plain pixel copy */
    DISP_SCALING_BILINEAR_OR_BEST   = ( 1 << 1 ),/**< Style: Bilinear or better*/
    } DISPE_SCALING;

/** Display Interface Types */
const uint32 KMeSSIBus         = 0x1; /**< MIPI DBI-2 type B */
const uint32 KLoSSIBus         = 0x2; /**< MIPI DBI-2 type C option 1 */
const uint32 KViSSIBus         = 0x3; /**< MIPI DPI-2 */
const uint32 KCDPBus           = 0x4; /**< CDP (HiSSI-V)=No corresponding MIPI standard. LoSSI works as control bus. */
const uint32 KDSIVideoBus      = 0x5; /**< DSI (HiSSI-M)=MIPI DSI1.1, Videobus */
const uint32 KDSICmdBus        = 0x6; /**< DSI (HiSSI-M)=MIPI DSI1.1, Commandbus */
const uint32 KOffscreenDisplay = 0x7; /**< Offscreen display, for possible USB, WLAN, etc. purpose */
const uint32 KCvbsBus          = 0x8;
const uint32 KHdmiBus          = 0x9;
const uint32 KDdcBus           = 0xA;
const uint32 KCecBus           = 0xB;

const uint32 KInterfaceNumberShift = 5;
typedef enum
    {
    DISP_BUS_NONE   = 0,                                              /**< Initialisation value */

    DISP_BUS_MESSI0 = (  0 << KInterfaceNumberShift ) | KMeSSIBus,    /**< MeSSI bus ID:0 */
    DISP_BUS_MESSI1 = (  1 << KInterfaceNumberShift ) | KMeSSIBus,
    DISP_BUS_MESSI2 = (  2 << KInterfaceNumberShift ) | KMeSSIBus,
    DISP_BUS_MESSI3 = (  3 << KInterfaceNumberShift ) | KMeSSIBus,
    DISP_BUS_MESSI4 = (  4 << KInterfaceNumberShift ) | KMeSSIBus,

    DISP_BUS_LOSSI0 = (  0 << KInterfaceNumberShift ) | KLoSSIBus,    /**< LoSSI bus ID:0 */
    DISP_BUS_LOSSI1 = (  1 << KInterfaceNumberShift ) | KLoSSIBus,
    DISP_BUS_LOSSI2 = (  2 << KInterfaceNumberShift ) | KLoSSIBus,
    DISP_BUS_LOSSI3 = (  3 << KInterfaceNumberShift ) | KLoSSIBus,
    DISP_BUS_LOSSI4 = (  4 << KInterfaceNumberShift ) | KLoSSIBus,

    DISP_BUS_VISSI0 = (  0 << KInterfaceNumberShift ) | KViSSIBus,    /**< ViSSI ID:0 */
    DISP_BUS_VISSI1 = (  1 << KInterfaceNumberShift ) | KViSSIBus,
    DISP_BUS_VISSI2 = (  2 << KInterfaceNumberShift ) | KViSSIBus,
    DISP_BUS_VISSI3 = (  3 << KInterfaceNumberShift ) | KViSSIBus,
    DISP_BUS_VISSI4 = (  4 << KInterfaceNumberShift ) | KViSSIBus,

    DISP_BUS_CDP0   = (  0 << KInterfaceNumberShift ) | KCDPBus,      /**< CDP ID:0 */
    DISP_BUS_CDP1   = (  1 << KInterfaceNumberShift ) | KCDPBus,
    DISP_BUS_CDP2   = (  2 << KInterfaceNumberShift ) | KCDPBus,
    DISP_BUS_CDP3   = (  3 << KInterfaceNumberShift ) | KCDPBus,
    DISP_BUS_CDP4   = (  4 << KInterfaceNumberShift ) | KCDPBus,

    DISP_BUS_DSIV0  = (  0 << KInterfaceNumberShift ) | KDSIVideoBus, /**< HiSSI-M ID:0. ID maps to Virtual Channel */
    DISP_BUS_DSIV1  = (  1 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV2  = (  2 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV3  = (  3 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV4  = (  4 << KInterfaceNumberShift ) | KDSIVideoBus, /**< ID:0 in second physical layer */
    DISP_BUS_DSIV5  = (  5 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV6  = (  6 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV7  = (  7 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV8  = (  8 << KInterfaceNumberShift ) | KDSIVideoBus, /**< ID:0 in third physical layer */
    DISP_BUS_DSIV9  = (  9 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV10 = ( 10 << KInterfaceNumberShift ) | KDSIVideoBus,
    DISP_BUS_DSIV11 = ( 11 << KInterfaceNumberShift ) | KDSIVideoBus,

    DISP_BUS_DSIC0  = (  0 << KInterfaceNumberShift ) | KDSICmdBus,   /**< HiSSI-M ID:0. ID maps to Virtual Channel */
    DISP_BUS_DSIC1  = (  1 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC2  = (  2 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC3  = (  3 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC4  = (  4 << KInterfaceNumberShift ) | KDSICmdBus,   /**< ID:0 in second physical layer */
    DISP_BUS_DSIC5  = (  5 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC6  = (  6 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC7  = (  7 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC8  = (  8 << KInterfaceNumberShift ) | KDSICmdBus,   /**< ID:0 in third physical layer */
    DISP_BUS_DSIC9  = (  9 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC10 = ( 10 << KInterfaceNumberShift ) | KDSICmdBus,
    DISP_BUS_DSIC11 = ( 11 << KInterfaceNumberShift ) | KDSICmdBus,

    DISP_BUS_OFFSCR = KOffscreenDisplay,                              /**< Offscreen display */

    DISP_BUS_CVBS   = KCvbsBus,                                       /**< Composite Tv-out */
    DISP_BUS_HDMI   = KHdmiBus,                                       /**< Hdmi Tv-out */
    DISP_BUS_DDC    = KDdcBus,                                        /**< DDC bus (HDMI and DVI) */
    DISP_BUS_CEC    = KCecBus,                                        /**< CEC bus (HDMI) */
    } DISPE_BUS;

/** Transfer mode */
typedef enum
    {
    DISP_BUS_0BIT  = 0x0000,    /**< Initialisation value, don't use */
    DISP_BUS_1BIT  = ( 1 << 0 ),/**< 1bit width bus, bidirectional LoSSI */
    DISP_BUS_2BIT  = ( 1 << 1 ),/**< LoSSI with separate read and write signals */
    DISP_BUS_3BIT  = ( 1 << 2 ),/**< E.g. DSI 3 lanes */
    DISP_BUS_4BIT  = ( 1 << 3 ),/**< E.g. DSI 4 lanes */
    DISP_BUS_8BIT  = ( 1 << 4 ),/**< E.g. MeSSI-8 */
    DISP_BUS_12BIT = ( 1 << 5 ),
    DISP_BUS_16BIT = ( 1 << 6 ),
    DISP_BUS_18BIT = ( 1 << 7 ),
    DISP_BUS_24BIT = ( 1 << 8 ),
    DISP_BUS_32BIT = ( 1 << 9 ),
    } DISPE_BUS_WIDTH;

/** Power control */
typedef enum
    {
    DISP_PWR_MODE_INVALID           = 0x0000,   /**< Initialisation value, don't use */
    DISP_PWR_MODE_ANALOG_POWER_ON   = 0x0011,   /**< External analogue voltages */
    DISP_PWR_MODE_ANALOG_POWER_OFF  = 0x0010,
    DISP_PWR_MODE_DIGITAL_POWER_ON  = 0x0021,   /**< External digital voltages */
    DISP_PWR_MODE_DIGITAL_POWER_OFF = 0x0020,
    DISP_PWR_MODE_RESET_ACTIVE      = 0x0041,   /**< Activate external reset signal. With DSI, RAR will be listened. */
    DISP_PWR_MODE_RESET_INACTIVE    = 0x0040,
    DISP_PWR_MODE_DISPLAY_ON        = 0x0081,   /**< Pixel clock for memoryless displays (ViSSI/HiSSI). LP/HS when DSI. */
    DISP_PWR_MODE_DISPLAY_OFF       = 0x0080,   /**< Ultra Low Power State (ULPS) mode when DSI */
    } DISPE_PWR_MODE;

/** Driver messages - @see dispDriverMessage */
typedef enum
    {
    DISP_MSG_PING      = 0x00000000,  /**< Ping for all drivers. All drivers forwards this msg and
                                           gives callback. Doesn't matter what is the 'receiver'-parameter. */
    DISP_MSG_SELFTEST  = 0x00000001,  /**< Selftest */
    DISP_MSG_PRODTEST  = 0x00000002,  /**< Production test */
    DISP_MSG_LAST      = 0xFFFFFFFF,  /**< Not in use */
    } DISPE_DRV_MSG;

/** Colorkey handling */
typedef enum
    {
    DISP_COLORKEYMODE_NONE       = 0x0000,      /**< No colorkey */
    DISP_COLORKEYMODE_SINGLE_KEY = ( 1 << 0 ),  /**< One color is colorkey (simplest) */
    DISP_COLORKEYMODE_KEY_MASK   = ( 1 << 1 ),  /**< Colorkey mask. If (pixel_color & mask) -> transparent pixel */
    DISP_COLORKEYMODE_ALPHA      = ( 1 << 2 ),  /**< To utilize alphachannel of source buffer for transparency, 
                                                     works with followings as ARGB : DISP_COLOR_FORMAT_ARGB8888, DISP_COLOR_FORMAT_ARGB1555 */
    } DISPE_COLORKEYMODE;

/** Tearing synchronisation type */
typedef enum
    {
    DISP_TE_SYNC_NO              = 0x0000,    /**< No HW support for tearing synchronization */
    DISP_TE_SYNC_VS_RAISING_EDGE = ( 1 << 0 ),/**< Vertical synchronization when raising edge */
    DISP_TE_SYNC_VS_FALLING_EDGE = ( 1 << 1 ),/**< Vertical synchronization when falling edge */
    DISP_TE_SYNC_HS_VS           = ( 1 << 2 ),/**< Horisontal and vertical tearing synchronization */
    DISP_TE_SYNC_VS_BUS_TRIGGER  = ( 1 << 3 ),/**< In DSI mode only (TEE) */
    } DISPE_TE_SYNC;

/** Advanced feature bit masks - Used for capability query */
typedef enum
    {
    DISP_FEATURE_NONE        = 0x0000,     /**< Initialisation value */
    DISP_FEATURE_SCALING     = ( 1 << 0 ), /**< Scaling */
    DISP_FEATURE_ALL_CASES   = ( 1 << 1 ), /**< No matter what is the used feature */
    DISP_FEATURE_ROTATION    = ( 1 << 2 ), /**< 90, 180 or 270 rotation */
    DISP_FEATURE_OVERLAY     = ( 1 << 3 ), /**< Overlay without colorkey and alpha */
    DISP_FEATURE_COLOR_KEY   = ( 1 << 4 ), /**< Overlay with colorkey */
    DISP_FEATURE_ALPHA_BLEND = ( 1 << 5 ), /**< Overlay with alpha */
    DISP_FEATURE_YCBCR       = ( 1 << 6 ), /**< YCbCr support */
    } DISPE_FEATURE;

/** Buffer's cache and MMU settings - Write buffers to be always enabled - Chipset driver is responsible to syncronise caches */
typedef enum
    {
    DISP_CACHE_NOTHING                = 0x0000,     /**< Only writebuffers */
    DISP_CACHE_WRITE_THROUGH          = ( 1 << 0 ), /**< Write through caches (writes to cache (if hit) and to memory) */
    DISP_CACHE_WRITE_ALLOCATION_L1    = ( 1 << 1 ), /**< Cache level 1 -line will be allocated for write access */
    DISP_CACHE_WRITE_ALLOCATION_L2    = ( 1 << 2 ), /**< Cache level 2 -line will be allocated for write access */
    DISP_CACHE_READ_ALLOCATION_L1     = ( 1 << 3 ), /**< Cache level 1 -line will be allocated for read access */
    DISP_CACHE_READ_ALLOCATION_L2     = ( 1 << 4 ), /**< Cache level 2 -line will be allocated for read access */
    DISP_CACHE_USER_READ_PRIVILEGE    = ( 1 << 5 ), /**< User code (user mode) have read accesses to buffer */
    DISP_CACHE_USER_WRITE_PRIVILEGE   = ( 1 << 6 ), /**< User code (user mode) have write accesses to buffer */
    DISP_CACHE_KERNEL_READ_PRIVILEGE  = ( 1 << 7 ), /**< Kernel code (supervisor undefined mode) have read accesses to buffer */
    DISP_CACHE_KERNEL_WRITE_PRIVILEGE = ( 1 << 8 ), /**< Kernel code (supervisor undefined mode) have write accesses to buffer */
    DISP_CACHE_ARM_ACCESSIBLE         = ( 1 << 9 ), /**< To be always defined if ARM can see the buffer. Otherwise can be allocated only for HW. */
    } DISPE_CACHE_SETTINGS;

/*- Data Structs ------------------------------------------------------------*/

/** Color Space Converter 3x3 matrix. To be defined if DISP_COLOR_MATRIX_CONV is used.
    Output conversion formula:
    Red Out   = (red[0]   * Rin) + (red[1]   * Gin) + (red[2]   * Bin) + red[3]
    Green Out = (green[0] * Rin) + (green[1] * Gin) + (green[2] * Bin) + green[3]
    Blue Out  = (blue[0]  * Rin) + (blue[1]  * Gin) + (blue[2]  * Bin) + blue[3] */
typedef struct
    {
    /** Fixed point position. E.g: value = ( red.cell1 >> fixedPoint ). E.g: fixedPoint=2 -> b0.00 */
    uint8 fixedPoint;
    /** Conversion matrixes per color component */
    int16 red[ 4 ];
    int16 green[ 4 ];
    int16 blue[ 4 ];
    } DISPS_COLOR_SPACE_CONV_MATRIX;

/** CIE 1931 color space coordinates. To be defined if DISP_COLOR_COORDINATES is used.
    When chipset driver knows source and destination coordinates, it can operate
    conversion from source to destination. Fixed point is 10th bit.
    E.g. If redX=625, it should be divided by 1024 (2^10) for getting real value 0.61035... */
typedef struct
    {
    /** Red chromaticity coordinates */
    uint16 redX;
    uint16 redY;
    /** Green chromaticity coordinates */
    uint16 greenX;
    uint16 greenY;
    /** Blue chromaticity coordinates */
    uint16 blueX;
    uint16 blueY;
    /** White chromaticity coordinates */
    uint16 whiteX;
    uint16 whiteY;
    } DISPS_COLOR_COORDINATES;

/** Rectangle */
typedef struct
    {
    /** Begin line (first line is 0) */
    uint16 startRow;
    /** Begin column (first column is 0) */
    uint16 startColumn;
    /** Rectangle height in pixels */
    uint16 rows;
    /** Rectangle width in pixels */
    uint16 columns;
    } DISPS_RECTANGLE;

/** Source buffer dimensions and format */
typedef struct
    {
    /** Local memory linear address */
    void* bufferLinearAddress;
    /** Local memory physical address */
    uint32 bufferPhysicalAddress;
    /** Can be zero. Required if not-local memory, then addresses can be NULL */
    uint32 bufferId;
    /** Physically linear */
    bool8 physicallyLinear;
    /** Cache/MMU features - bit mask */
    DISPE_CACHE_SETTINGS caches;
    /** Features what to be used for this buffer - This is like usage-hint for chipset driver, and can be ignored */
    DISPE_FEATURE bufferUseCases;

    /** Offset from bufferPhysicalAddress to Y-components (needed if planar, otherwise can be set 0) */
    uint32 offsetToY;
    /** Offset from bufferPhysicalAddress to Cb-components (needed if planar, otherwise can be set 0) */
    uint32 offsetToCb;
    /** Offset from bufferPhysicalAddress to Cr-components (needed if planar, otherwise can be set 0) */
    uint32 offsetToCr;

    /** Source buffer pixel format */
    DISPE_COLOR_FORMAT pixelFormat;
    /** Source buffer color space (normally = DISP_COLOR_SPACE_STANDARD_RGB) */
    DISPE_COLOR_SPACE sourceColorSpace;
    /** Source buffer color space (free) to be defined if sourceColorSpace=DISP_COLOR_COORDINATES */
    DISPS_COLOR_COORDINATES sourceColorCoordinates;
    /** Used if API user wants to use free conversion table, to be defined if sourceColorSpace=DISP_COLOR_MATRIX_CONV */
    DISPS_COLOR_SPACE_CONV_MATRIX colorSpaceConversion;
    /** Required if YCbCr format used */
    DISPE_COLOR_YCBCR_BIT_MASK yCbCrBitMask;

    /** Buffer width in pixels */
    uint32 width;
    /** Buffer height in pixels */
    uint32 height;
    /** One line in bytes. With 420 planar, this tells one line Y-components stride. */
    uint32 stride;
    } DISPS_BUFFER;

/** Colorkey - Makes hole to layer */
typedef struct
    {
    /** Only one colorkeymode can be defined */
    DISPE_COLORKEYMODE mode;
    /** If DISP_COLORKEYMODE_SINGLE_KEY -> Defines transparency key when needed. Planar not supported.
        If DISP_COLORKEYMODE_KEY_MASK -> if (pixel_color & colorkey) -> transparent pixel. Then colorkey defines maskColor. */
    uint32 colorkey;
    } DISPS_COLORKEY;

/** Layer - one visible layer information */
typedef struct
    {
    /** True when this layer is enabled */
    bool8 enabled;
    /** True if forces transfer to display. Forcing means that chipset drv logic cannot do any own decisions
        (optimising/buffer changes/buffer manipulation) for the transfers. When this is true, buffer content must be
        visible on display panel after transfer. Normally can be false. */
    bool8 forceView;

    /** Source buffer struct */
    DISPS_BUFFER sourceBuffer;

    /** Input crop. Max size < sourceBuffer.width & height. */
    DISPS_RECTANGLE inputScissor;
    /** Target area coordinates. if source area is different size than target up/downscaling will need to be 
        performed  by HW. Return Error if scaling requested but no HW capability. */
    DISPS_RECTANGLE targetArea;
    /* If inputScissor!=targetArea sizes mismatch, then scaling method need to be defined here */
    DISPE_SCALING scalingMethod;

    /** Layer rotation information */
    DISPE_ROTATION rotate;

    /** Colorkey struct which is used in this buffer */
    DISPS_COLORKEY colorkey;

    /** Brightness value on screen, [-100,100]%, may be ignored by the driver.
        If chipset driver can control only one brightness (not for each layer),
        then first layer settings are used. */
    int16 brightness;
    /** Contrast value on screen, [-100,100]%
        If chipset driver can control only one contrast (not for each layer),
        then first layer settings are used. */
    int16 contrast;
    /** Gamma value on screen, e.g.: 1.00=100, 2.20=220.
        If chipset driver can control only one gamma (not for each layer),
        then DISPS_FINAL_VIEW::topLayer settings are used.

        Formula: output_signal = intensity^( 1 / gamma )

        In the C++ language this can be represented as follows:
         output_signal = pow( double( intensity ), double( 1.0 ) / ( double( gamma ) / 100 ) );

        Gamma-correction lookup table can be constructed like this:
         int32 lut[ 256 ];
         for ( int32 intensity = 0; intensity < 256; intensity++ )
             lut[ i ] = pow( double( intensity ), double( 1.0 ) / ( double( gamma ) / 100 ) );

        Loading this table into the hardware lookup table at the output side of
        framebuffer will cause RGB intensity values with integer components
        between 0 and 255 to be gamma-corrected by the hardware as if by the following code:
         red_signal   = lut[ r ];
         green_signal = lut[ g ];
         blue_signal  = lut[ b ]; */
    uint16 gamma;
    /** True when dithering is enabled (if HW does not support, then ignore this without error) */
    bool8 enableDithering;
    /** Per layer alpha if supported, 0x00-0xFF (if HW does not support, then ignore this without error) */
    uint8 perLayerAlphaValue;
    } DISPS_LAYER;

/**
Final view - composed view information

@code
__________________________ __________________________ __________________________
|                        | |                        | |                        |
|    DISPS_COLORKEY (1)  | |   DISPS_RECTANGLE (2)  | |     DISPS_BUFFER (1)   |
|                        | |                        | |                        |
¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯ ¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯ ¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯
            `--------------------------|--------------------------´
                           ____________|_____________
                           |                        |
                           |      DISPS_LAYER (5)   |
                           |                        |
                           ¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯
                           ____________|_____________
                           |                        |
                           |    DISPS_FINAL_VIEW    |
                           |                        |
                           ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
@endcode
*/
typedef struct /* TODO can be done for n-amount of layers somehow else - perhaps not needed */
    {
    DISPS_LAYER topLayer;    /**< top most layer (nearest), normally UI-layer and always defined (but not for pure control bus) */
    DISPS_LAYER secondLayer; /**< 2nd */
    DISPS_LAYER thirdLayer;  /**< 3rd */
    DISPS_LAYER fourthLayer; /**< 4th */
    DISPS_LAYER fifthLayer;  /**< 5th */
    uint32 backgroundColor;  /**< Latest layer (farthermost). Background color in URGB8888 format. */
    } DISPS_FINAL_VIEW;

/**
Update - Gives changed areas what to be updated. Chipset driver can ignore parameters, if hw cannot handle.

@code
__________________________
|                        |
|     DISPS_RECTANGLE    |
|                        |
¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯
____________|_____________
|                        |
|      DISPS_UPDATE      |
|                        |
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
@endcode
*/
typedef struct
    {
    /** Changed area of layers - Coordinate space in DISPS_LAYER::sourceBuffer - Shall be inside DISPS_LAYER::inputScissor */
    DISPS_RECTANGLE topLayerRect;
    DISPS_RECTANGLE secondLayerRect;
    DISPS_RECTANGLE thirdLayerRect;
    DISPS_RECTANGLE fourthLayerRect;
    DISPS_RECTANGLE fifthLayerRect;

    /** Tearing remove use */
    DISPE_TE_SYNC teSync;
    /** If DISP_TE_SYNC_HS_VS sync method chosen, the sync line needs to be defined here */
    uint32 hsSyncLine;
    } DISPS_UPDATE;

/** Target device and bus definition */
typedef struct
    {
    /** System display number. Normally primary display has 0, secondary 1, etc. Set to 0xFF if unknown. */
    uint8 systemDisplayNumber;

    /** Bus color format */
    DISPE_COLOR_FORMAT busColorFormat;
    /** Native resolution of display */
    uint16 panelHeight;
    /** Native resolution of display */
    uint16 panelWidth;
    /** Destination color space, HW converts space to another if this is not DISP_COLOR_SPACE_NONE 
        If DISPS_BUFFER.sourceColorSpace is same, then conversion is disabled.
        This operations can be defined platform specific, perhaps similar behavior is not possible for all platforms. */
    DISPE_COLOR_SPACE destinationColorSpace;
    /** Destination color coordinates. With this and sourceColorCoordinates chipset driver should do the conversion.
        to be defined if destinationColorSpace=DISP_COLOR_COORDINATES */
    DISPS_COLOR_COORDINATES destinationColorCoordinates;
    /** Used for DSI command packet mode. Continue command if pixel data to be splitted for several parts.
        (normally: Memory Write Continue = 0x3C) If not used at all, then this is 0. */
    uint8 memoryWriteContinueCmd;
    /** Used for DSI. Continue command if read data to be splitted for several parts.
        (normally: Memory Read Continue = 0x3E) If not used at all, then this is 0. */
    uint8 memoryReadContinueCmd;

    /* Timing and polarities -> */

    /** Used bus width. max is DISPS_CAPABILITIES.busWidth. E.g. with MeSSI-8 this is DISP_BUS_8BIT. */
    DISPE_BUS_WIDTH outputBusWidth;
    /** How many clock cycles are used per pixel. E.g. with MeSSI-8 and 24bpp, this is 30 (3 bytes per pixel).
        1 cycle = 10. 1.5 cycles = 15. 3 cycles = 30 */
    uint8 cyclesPerPixel;
    /** Specifies how many LSB bits will be taken from dispAppendCommand() 'command' -parameter. Normally byte alignment only 8/16/24/32 */
    uint8 bitsPerGivenCommand;
    /** Specifies how many LSB bits will be taken from dispAppendParameter() 'parameter' -parameter. Normally byte alignment only 8/16/24/32 */
    uint8 bitsPerGivenParameter;

    /** (Pixel data) Clock write cycle high time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement.
        -In DSI case, chipset driver has to detect speed mode according to the timing parameters. High Speed (HS) >= 80Mb/s,
         Low Power mode (LP) 1Mb/s <= 10Mb/s. @see DISP_PWR_MODE_DISPLAY_OFF. These DSI timings are used for dispFlush() + combined commands.
        -In ViSSI/CDP-case, these tells max ViSSI/CDP pixel clock speed. */
    uint32 clockHighDataWriteNs;
    /** (Pixel data) Clock write cycle low time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement */
    uint32 clockLowDataWriteNs;
    /** (Pixel data) Clock write cycle total time */
    uint32 clockCycleDataWriteNs;

    /** (Command data) Clock write cycle high time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement.
        -In DSI case, chipset driver has to detect speed mode according to the timing parameters. High Speed (HS) >= 80Mb/s,
         Low Speed (LP) 1Mb/s <= 10Mb/s. @see DISP_PWR_MODE_DISPLAY_OFF. These DSI timings are used for dispProcessList().
        -In ViSSI/CDP-case, these tells max LoSSI write speed. */
    uint32 clockHighCmdWriteNs;
    /** (Command data) Clock write cycle low time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement */
    uint32 clockLowCmdWriteNs;
    /** (Command data) Clock write cycle total time */
    uint32 clockCycleCmdWriteNs;

    /** Clock read cycle high time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement.
        -In DSI case, chipset driver has to detect speed mode according to the timing parameters.
         According to DSI-specification, read is normally LP. These DSI timings are used when dispAppendRead()/dispAppendReadRaw().
        -In ViSSI/CDP-case, these tells max LoSSI read speed. */
    uint32 clockHighReadNs;
    /** Clock read cycle low time in ns -> chipset HW should adjust highest possible clockrate to meet the requirement */
    uint32 clockLowReadNs;
    /** Clock read cycle total time */
    uint32 clockCycleReadNs;

    /** Video display: vertical sync polarity */
    bool8 vSyncPolarityLow;
    /** Video display: horisontal sync polarity */
    bool8 hSyncPolarityLow;
    /** Video display: pixel clock polarity */
    bool8 pClkActiveFalling;
    /** Video display: in pixel clock cycles */
    uint16 hFrontPorch;
    /** Video display: in pixel clock cycles */
    uint16 hBackPorch;
    /** Video display: in pixel clock cycles */
    uint16 hPulseWidth;
    /** Video display: in horisontal clock cycles */
    uint16 vFrontPorch;
    /** Video display: in horisontal clock cycles */
    uint16 vBackPorch;
    /** Video display: in horisontal clock cycles */
    uint16 vPulseWidth;

    /** TE-signal GPIO line number. 0 means HW block controlled */
    int32 teSignalGpioNumber;

    /** Chip Select -signal GPIO line number. 0 means HW block controlled */
    int32 csSignalGpioNumber;

    /** Reset signal GPIO line number. 0 means HW block controlled */
    int32 resetSignalGpioNumber;
    /** True when target reset is active low */
    bool8 resetActiveLow;

    /** TE vertical pulse in microseconds (Needed for TE-line detection) */
    uint32 vsPulseUs;
    /** TE horizontal pulse in microseconds (Needed for TE-line detection) */
    uint32 hsPulseUs;
    } DISPS_HW_SETTINGS;

/** Defines HW capabilities for one interface */
typedef struct
    {
    /** For what interface the capability is defined */
    DISPE_BUS busInterface;

    /** Control bus width */
    DISPE_BUS_WIDTH controlBusWidth;
    /** Data (pxl) bus width */
    DISPE_BUS_WIDTH dataBusWidth;

    /** Scaling represents supported scaling capabilities of the HW interface.  
    --> if HW support for scaling is not available buffer transfer for different viewport dimensions should 
    return  DISP_ERROR_NO_HW_CAPABILITY */
    DISPE_SCALING scalingMethods;
    /** Minimum scaling factor.
        E.g. if 1/2x is min, then this is 200 (100 / scalingMinDenominator). 1x = 100. 0xFFFF = infinity. */
    uint16 scalingMinDenominator;
    /** Maximum scaling factor.
        E.g. if 2.5x is max, then this is 250 (scalingMaxNumerator / 100). 1x = 100. 0xFFFF = infinity. */
    uint16 scalingMaxNumerator;

    /** Source resolution parameters must be even, if following features are used (bit mask) */
    DISPE_FEATURE evenSourceResolution;
    /** Destination resolution parameters must be even, if following features are used (bit mask) */
    DISPE_FEATURE evenDestinationResolution;

    /** Supported color space conversions from sRGB to DISPE_COLOR_SPACE (bit mask) */
    DISPE_COLOR_SPACE supportedColorSpaceConversion;
    /** True when brightness tuning is supported */
    bool8 supportsBrightnessControl;
    /** True when contrast tuning is supported */
    bool8 supportsContrastControl;
    /** True when gamma tuning is supported */
    bool8 supportsGammaControl;
    /** True when (at least one layer) dithering is supported */
    bool8 supportsDithering;

    /** Rotation represents supported rotation capabilities of HW. */
    DISPE_ROTATION rotations;
    /** True if HW can rotate each layer separately. False if only whole view can be rotated.
        (Hopefully will not be needed in NGA) */
    bool8 separateRotationPerLayer;
    /** Bitmask for features which needs bound buffers. If 0, then can be done for any input buffer */
    DISPE_FEATURE featuresNeedsBindedBuffers;

    /** All the possible colorkey modes supported by the interface */
    DISPE_COLORKEYMODE colorKeyModes;

    /** How many layers supported, at least 1 */
    uint8 layers;
    /** True when per layer alpha supported */
    bool8 perLayerAlpha;

    /** Partial update can transfer separate rows */
    bool8 rowPartialUpdate;
    /** Partial update can transfer separate columns */
    bool8 columnPartialUpdate;

    /** Supported TE modes for the Hw-block controlled (e.g. DIF module TE capabilities) */
    DISPE_TE_SYNC teSyncMethodsHwBlock;
    /** Supported TE modes for the GPIO controlled (If TE line is connected to GPIO-pin) */
    DISPE_TE_SYNC teSyncMethodsGpio;

    /** Color buffer formats natively supported by HW */
    DISPE_COLOR_FORMAT pixelFormats;
    /** Bit mask for features, which works with 24bpp aligned color mode */
    DISPE_FEATURE packedPixelsSupported;

    /** True when given buffer(s) works as frame buffer (memoryless displays). False when buffer is free after transfer (MeSSI=False) */
    bool8 requiresFrameBuffer;

    /** Bit mask for features, which needs work buffer from host memory - TODO is needed to get sizes for those */
    DISPE_FEATURE requiresWorkBuffer;
    /** True if DMA buffers must be physically linear */
    bool8 requiresPhysicallyLinearBuffer;

    /** True when interface can carry pixel data */
    bool8 carryData;
    /** True when interface can carry control data. Typically this can be false if driver implements ViSSI only, but not LoSSI. */
    bool8 carryControl;
    } DISPS_CAPABILITIES;

/*- Constants ---------------------------------------------------------------*/

/** API version number. @see dispApiVersion().
    7:  memoryReadContinueCmd added
    6:  systemDisplayNumber. ARGB4444. dispDriverMessage.
    5:  Pre-multiplied alpha modes
    4:  Free colorspace
    3:  Callback parameter for DISPT_READY_CB. fetchedArea added to dispGetWorkBuffer().
    2:  forceView and DISP_CACHE_ARM_ACCESSIBLE added
    1:  First version where dispApiVersion-method exists */
const uint32 KApiVersionNumber = 7;

/** Fixed Chipset driver name char array. Name ends to '0', so max name length is 9 + '\0'. */
typedef char CHIPSET_DRV_NAME[ 10 ];

/** Chipset driver calls this, when something is executed.
    Callback must not be called in the API user thread context.
    @see dispProcessList
    @param  error  An error code
    @param  parameter  Given parameter (@see dispBindDisplayNumber())
    @param  isrContext  True when callback is called in interrupt context */
typedef void (*DISPT_READY_CB)(DISPE_ERROR error, void* parameter, bool8 isrContext);

/** Chipset driver calls this, when message (dispDriverMessage) is sent and executed.
    Callback must not be called in the API user thread context.
    @see dispDriverMessage
    @param  error       An error code
    @param  parameter   Given parameter (@see dispBindDisplayNumber())
    @param  receiverForThisMsg  Driver name who responded for this message
    @param  responseForThisMsg  dispDriverMessage's 'message'-parameter for this message
    @param  value       Message specific return value, unique meaning per DISPE_DRV_MSG
    @param  isrContext  True when callback is called in interrupt context */
typedef void (*DISPT_MSG_CB)(DISPE_ERROR error, void* parameter, CHIPSET_DRV_NAME receiverForThisMsg,
                             DISPE_DRV_MSG responseForThisMsg, uint32 value, bool8 isrContext);

/** Chipset API interface type */
typedef uint32* API_POINTER;

/** Identifier type */
typedef uint32 IDENTIFIER;

/*- Macros ------------------------------------------------------------------*/

/*- External Data -----------------------------------------------------------*/

/*- Variables ---------------------------------------------------------------*/

/*- Forward Declarations ----------------------------------------------------*/

/*- Functional Prototypes ---------------------------------------------------*/

/* VERSION -> */
/** Gets implemented chipset API version. Verify the return value to KApiVersionNumber.
    @param  api  Api interface pointer, fetched from dispGetInterface()
    @see KApiVersionNumber
    @return Implemented display chipset API version, KApiVersionNumber (should match to client version) */
inline uint32 dispApiVersion(API_POINTER api);
/* <- VERSION */

/* CAPABILITY -> */
/** Gets number of supported capabilities (DISPS_CAPABILITIES).
    @param  api  Api interface pointer, fetched from dispGetInterface()
    @see dispGetCapabilities
    @return Max value for getCapabilities() */
inline uint32 dispGetNumberOfCapabilities(API_POINTER api);

/** Capability query. Capability list has struct for all the supported devices.
    @see dispGetNumberOfCapabilities
    @param  api               Api interface pointer, fetched from dispGetInterface()
    @param  capabilityNumber  Capability number, max value is got from dispGetNumberOfCapabilities()
    @param  capability        Returned capability for user
    @return an error code */
inline DISPE_ERROR dispGetCapabilities(API_POINTER api, uint32 capabilityNumber, DISPS_CAPABILITIES* capability);
/* <- CAPABILITY */

/* CONTROL -> */
/** Binds display number to Hw (constructor). This method initialises and reserved this DISPE_BUS for this client.
    This method can be called if settings of bus are wanted to change, so can be called in any time.
    Settings will be take in use immediately.
    If client calls this method multiple times, chipset driver should return same identifier each time.
    @param  api              Api interface pointer, fetched from dispGetInterface()
    @param  busInterface     Wanted busInterface, which to be initialised and reserved
    @param  cbParam          Callback parameter, returned in callbacks. Normally can be 'this' pointer in C++.
    @param  identifier       Method fills this for user, and user will be recognised with this parameter.
    @param  displaySettings  Target settings
    @return an error code */
inline DISPE_ERROR dispBindDisplayNumber(API_POINTER api, DISPE_BUS busInterface, void* cbParam, IDENTIFIER* identifier, const DISPS_HW_SETTINGS* displaySettings);

/** Unbinds and deallocates display Hw (destuctor). After this HW is free for another client use.
    After call identifier is undefined. Pending callbacks will be completed with DISP_ERROR_CANCELLED-error.
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @return an error code */
inline DISPE_ERROR dispUnbindDisplayNumber(API_POINTER api, IDENTIFIER identifier);

/** Sets all per layer settings for chipset driver. Settings will be used on next dispFlush()-call.
    In double buffered case, this method to be call every time before dispFlush, with different buffer
    addresses. Chipset driver is responsible to optimise unneeded reinitialisation. It should store
    previous settings and compare changed settings of DISPS_FINAL_VIEW, and use that result
    for HW reinitialisation.
    @see dispFlush
    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  finalView   Source buffer and final composition settings
    @return an error code */
inline DISPE_ERROR dispSetFinalView(API_POINTER api, IDENTIFIER identifier, const DISPS_FINAL_VIEW* finalView);

/** Clones output (dispFlush()) to given destination bus.
    Source buffer information is fetched from (this client's) dispSetFinalView()-parameters.
    Bus speed settings are fetched from 'destinationBus' client's dispBindDisplayNumber()-parameters.
    Commands (control) are still coming from 'destinationBus' client.
    Stop cloning with DISP_BUS_NONE-parameter.
    @param  api              API interface pointer, fetched from dispGetInterface()
    @param  identifier       Chipset driver uses this parameter for detecting client (source)
    @param  destinationBus   This client's source buffer is cloned to this bus (destination)
    @return an error code */
inline DISPE_ERROR dispCloneOutput(API_POINTER api, IDENTIFIER identifier, DISPE_BUS destinationBus);

/** Power control. Chipset API handles own resources, e.g. HW-block clock resources.
    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  powerMode   New wanted power states
    @param  callback    To be called when power change is ready, even error occurred. (especially needed when pixelclock). Synchronic call if NULL.
    @return an error code */
inline DISPE_ERROR dispPowerControl(API_POINTER api, IDENTIFIER identifier, DISPE_PWR_MODE powerMode, DISPT_READY_CB callback);

/** This method makes possible to send some messages for whole chipset driver stack.
    When chipset drivers will get the message call and name does not match for that driver,
    then it has to forward message for next driver in same driver stack.

    If message==DISP_MSG_PING: Chipset driver will forward same message for
    next chipset drivers in the stack, then all drivers call 'callback' with
    their own name (CHIPSET_DRV_NAME) and got message (DISP_MSG_PING). With this, topmost
    driver can make query, what components stack has. Topmost caller sets param=0, when chipset
    driver calls this forward, it increases param by one (param=1). If chipset driver uses to
    separated chipset drivers, both will to be called with param=1. Then 'param' means stack level.
    In callback chipset drivers will set given param to DISPT_MSG_CB's 'value'-parameter.

    If message==DISP_MSG_SELFTEST: If given name (receiver) matches to driver name, then the
    driver will execute selftest. When selftest is ready, it reports test result with 'callback'
    for caller. Chipset drivers will forward the same message, if name (receiver) and their own
    name doesn't match. Doesn't care what is the 'param'-parameter with this message.

    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  receiver    Message receiver name (same what is stored in Interface Storage)
    @param  message     Message identifier
    @param  param       Optional, has different meaning per 'message'
    @param  callback    Callback when message actions are executed. Cannot be NULL.
    @return an error code */
inline DISPE_ERROR dispDriverMessage(API_POINTER api, IDENTIFIER identifier, CHIPSET_DRV_NAME receiver,
                                     DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback);
/* <- CONTROL */


/* DISPLAY UPDATE -> */
/** Prepares DMA-transfer according to latest dispSetFinalView parameters.
    After this, if DISPS_CAPABILITIES.requiresWorkBuffer is true (some bit is set), work buffer is ready.
    This method can be called multiple times, before dispFlush().
    @see dispFlush
    @see dispSetFinalView
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  changedArea Changed areas, rectangle per layer. Chipset driver can ignore and transfer bigger part.
    @param  callback    To be called when preparation is ready, even error occurred. Synchronic call if NULL.
    @return an error code */
inline DISPE_ERROR dispPrepareFlush(API_POINTER api, IDENTIFIER identifier, const DISPS_UPDATE* changedArea, DISPT_READY_CB callback);
/** Display flush (real DMA-transfer) according to latest not flushed dispPrepareFlush parameters.
    Special case if is wanted to flush once for ViSSI output. Keep DISP_PWR_MODE_DISPLAY_OFF always, so if
    power state DISP_PWR_MODE_DISPLAY_OFF is set, and Flush is called, then Hw flushes one frame through ViSSI.

    DISPS_CAPABILITIES.requiresFrameBuffer==false:
      callback will be called when display buffer is transferred to the display.
    DISPS_CAPABILITIES.requiresFrameBuffer==true:
      callback will be called when display buffer starting to be visible. So when callback is called
      any pixel of flush is not yet shown. And after that given buffer works as framebuffer
      until next's flush callback will be called. So caller should be aware of that
      to avoiding tearing (no draw to buffer if that is still work as framebuffer).

    If there is pending appended commands+parameters (e.g. dispAppendCommand) the list to be sent before
    actual image flush. With this method, only dispFlush() callback will be called after ready.

    If display has TE-line, and TE-line is enabled with DISPS_UPDATE::teSync, chipset driver
    shall avoid death lock with backup timer if TE will never detected (TE line may be broken).
    When TE-line is not detected and backup timer is triggered DMA, then DISP_ERROR_TE_MISSED error
    is reported in return value and/or with callback.

    @see dispSetFinalView
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  callback    To be called when transfer (DMA) is ready, even error occurred. Synchronic call if NULL.
    @return an error code */
inline DISPE_ERROR dispFlush(API_POINTER api, IDENTIFIER identifier, DISPT_READY_CB callback);
/* <- DISPLAY UPDATE */


/** COMMANDS/PARAMETERS -> 
    Commands and parameters are collected to dynamic size table or array (linked list or compatible).
    List is collected with dispAppendXX()-methods, in that order what is called. When display driver
    is appended all needed commands and parameters, then it calls dispProcessList(), which sends appended data
    to display bus. After next use, display driver is responsible to clear previous list by dispClearList().
*/
/** Clears/resets list. This to be called every time before new list will be collected for chipset driver.
    Don't ever call if callback waiting is ongoing (between dispProcessList->callback)
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @return an error code */
inline DISPE_ERROR dispClearList(API_POINTER api, IDENTIFIER identifier);

/** Appends command to the list.
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  command     Command to be sent to display bus (LSB bits taken only, @see bitsPerGivenCommand)
    @return an error code */
inline DISPE_ERROR dispAppendCommand(API_POINTER api, IDENTIFIER identifier, uint32 command);

/** Appends parameter to the list.
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  parameter   Parameter to be sent to display bus (LSB bits taken only, @see bitsPerGivenParameter)
                        If e.g. dispAppendParameter=16, at least with MeSSI-8 then MSB byte is sent before LSB-byte.
                        E.g. with MeSSI-16, some devices may require 16bit parameters, then dispAppendParameter=16. (See MIPI)
    @return an error code */
inline DISPE_ERROR dispAppendParameter(API_POINTER api, IDENTIFIER identifier, uint32 parameter);

/** Appends read data amount in bytes to given buffer.
    With DSI: Each read operation shall generate "Set Maximum Return Packet Size" (SMRPS)
    command for display (before last DCS command), according to lengthInBytes or max HW read fifo size.
    @param  api            Api interface pointer, fetched from dispGetInterface()
    @param  identifier     Chipset driver uses this parameter for detecting client
    @param  lengthInBytes  How many bytes will be read from display bus
    @param  readBuffer     Destination where chipset driver writes data after read
    @return an error code */
inline DISPE_ERROR dispAppendRead(API_POINTER api, IDENTIFIER identifier, uint32 lengthInBytes, void* readBuffer);

/** Reads raw data (e.g. pixels) to wanted place.
    @see dispAppendRead
    @param  api               Api interface pointer, fetched from dispGetInterface()
    @param  identifier        Chipset driver uses this parameter for detecting client
    @param  lengthInBytes     How many bytes will be read from display bus
    @param  readBuffer        Destination where chipset driver writes data after read
    @param  readBufferOneLine Read buffer one line in bytes (after this will be skipped according to stride)
    @param  readBufferStride  Read buffer stride in bytes. Must be => readBufferOneLine
    @return an error code */
inline DISPE_ERROR dispAppendReadRaw(API_POINTER api, IDENTIFIER identifier, uint32 lengthInBytes, void* readBuffer, uint32 readBufferOneLine, uint32 readBufferStride);

/** Sends list. Send list in same order than it is filled. Can be skipped if next operation is dispFlush().
    Then dispFlush() prepares flush with sending appended commands before flush.
    @param  api         Api interface pointer, fetched from dispGetInterface()
    @param  identifier  Chipset driver uses this parameter for detecting client
    @param  callback    To be called when the list is sent, even error occurred. Synchronic call if NULL.
    @return an error code */
inline DISPE_ERROR dispProcessList(API_POINTER api, IDENTIFIER identifier, DISPT_READY_CB callback);
/* <- COMMANDS/PARAMETERS */


/** MEMORY MANAGING -> 
    Memory allocation is needed for hiding all hardwares, and all special buffer modes, like tiled buffers.
    Here is couple of use cases, and how they should be handled.

    Use case #1 - Display driver allocated buffer from chipset driver (chipset driver allocates):
    -Display driver fills all members, except addresses to bufferInfo.
    -Display driver calls dispAllocateBuffer()
    -Chipset driver fills allocatedBuffer-struct, and display driver uses that for work

    Use case #2 - Display driver wants allocate buffers by itself:
    -Display driver fills all members, except addresses to bufferInfo.
    -Display driver calls dispCalculateMemorySize()
    -Display driver allocates buffer using OS-services, according to returned neededMemorySize value
    -Display driver binds allocated buffer to chipset driver, using dispInitialiseBuffer()-method
    -Chipset driver fills allocatedBuffer-struct, and display driver uses that for work

    Use case #3 - Display color mode changed dynamically:
    -Display driver gets requirement to change ARGB8888 mode to RGB565
    -Display driver waits that all DMA and other accesses to the buffer are ready (no accesses)
    -Display driver calls dispInitialiseBuffer()
    -Chipset driver fills allocatedBuffer-struct, and display driver uses that for work

    Use case #4 - Free buffer:
    -Display driver waits that all DMA and other accesses to the buffer are ready (no accesses)
    -Display driver calls dispDeallocateBuffer()
    -Chipset driver deallocates given buffer (buffer must be allocated or bound in chipset driver)

    API client has to fill following parameters before give the buffer for dispAllocateBuffer(),
    dispCalculateMemorySize() or dispInitialiseBuffer():
    -At least one of these: bufferLinearAddress, bufferPhysicalAddress, bufferId
    -physicallyLinear required or not
    -caches
    -bufferUseCases
    -pixelFormat and yCbCrBitMask
    -width and height
    Chipset driver has to fill rest data members

*/
/** Allocates buffer for user. This method makes allocation and display driver does not need do any buffer allocation anymore.
    @param  api             Api interface pointer, fetched from dispGetInterface()
    @param  identifier      Chipset driver uses this parameter for detecting client
    @param  bufferInfo      Display driver gives buffer size and format requirements to chipset driver (not all members filled)
    @param  allocatedBuffer Chipset driver fills all data members for display driver use
    @return an error code */
inline DISPE_ERROR dispAllocateBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer);

/** If display driver wants to allocate buffers itself, it can make query from chipset driver, that how much it requires memory
    for doing memory allocation. This is needed e.g. if buffer must have some extra alignment for tiling.
    After own allocation, display driver must to initialise buffer using dispInitialiseBuffer().
    @see dispInitialiseBuffer()
    @param  api              Api interface pointer, fetched from dispGetInterface()
    @param  identifier       Chipset driver uses this parameter for detecting client
    @param  bufferInfo       Display driver gives new buffer information to chipset driver
    @param  neededMemorySize Chipset driver fills needed buffer size to display driver (in bytes)
    @return an error code */
inline DISPE_ERROR dispCalculateMemorySize(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, uint32* neededMemorySize);

/** If user settings are changed, e.g. colormode or DISPS_BUFFER.bufferUseCases changed, chipset driver can do some changes to buffer settings.
    It can change tile size, or re-allocate new version of buffer for user.
    This to be called every time when some of bufferInfo or DISPS_BUFFER.bufferUseCases is changed.
    Display driver should be aware that any transfer or access to old buffer is not ongoing when this method is called.
    If display driver is allocated buffer by itself, it should give allocated buffer to chipset driver using this method. Then
    returned buffer (allocatedBuffer) will be used for update and draw purpose (this method binds the buffer).

    @note Any buffer can be tried to give directly to chipset driver (for flush), but if e.g. rotation
    requires some special buffer type, chipset driver cannot do all operations for "not initalised" buffers.
    So-called external buffers can be tried to flush directly without dispInitialiseBuffer, but then error may occur.

    @see dispCalculateMemorySize()
    @param  api             Api interface pointer, fetched from dispGetInterface()
    @param  identifier      Chipset driver uses this parameter for detecting client
    @param  bufferInfo      Display driver gives new buffer information to chipset driver
    @param  allocatedBuffer Chipset driver fills all data members for display driver use
    @return an error code */
inline DISPE_ERROR dispInitialiseBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferInfo, DISPS_BUFFER* allocatedBuffer);

/** Deallocates and unbinds the buffer. If display driver is allocated buffer itself, this must be done
    before the real memory deallocation.
    So-called external buffers will not be deallocated with this function.
    @param  api               Api interface pointer, fetched from dispGetInterface()
    @param  identifier        Chipset driver uses this parameter for detecting client
    @param  bufferToBeRemoved Display driver gives new buffer information to chipset driver
    @return an error code */
inline DISPE_ERROR dispDeallocateBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_BUFFER* bufferToBeRemoved);

/** Fetchs chipset driver workbuffer (if exists, DISPS_CAPABILITIES.requiresWorkBuffer)
    Work buffer is available when dispPrepareFlush() is called. To be called separately for each dispPrepareFlush() call.
    Can fetch also partial buffer, and then can be faster operation, and peek memory consumption will be smaller.
    @param  api               Api interface pointer, fetched from dispGetInterface()
    @param  identifier        Chipset driver uses this parameter for detecting client
    @param  fetchedArea       Rectangle which to be fetched
    @param  fetchedWorkBuffer Chipset driver fills own work buffer information to this buffer (if in host memory)
    @return an error code */
inline DISPE_ERROR dispGetWorkBuffer(API_POINTER api, IDENTIFIER identifier, const DISPS_RECTANGLE* fetchedArea, DISPS_BUFFER* fetchedWorkBuffer);

/* <- MEMORY MANAGING */

/*- Inline Functions --------------------------------------------------------*/

#include "display_chipset_api.inl"

#endif /* DISPLAY_CHIPSET_API_H */

/* End of File */

