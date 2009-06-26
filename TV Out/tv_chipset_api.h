/*
  tv_chipset_api.h

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

  <p>This is the tv chipset driver API document.</p>
  <p>This API hides HW differencies from display (and other users) driver.
  API is not kept as binary compatible.</p>
  <p>Get API pointer:
  API pointer (API_POINTER) will be found from Interface Storage.
  CVBS is found with bus name DISP_BUS_CVBS and HDMI with DISP_BUS_HDMI</p>
  <p></p>

*/
/** @file

Declaration of TV chipset driver API

@publishedDeviceAbstraction
*/

#ifndef TV_CHIPSET_API_H
#define TV_CHIPSET_API_H

/*- Include Files  ----------------------------------------------------------*/

#include "display_chipset_os.h"  /* OS specific header file, typedef etc. */
#include "display_chipset_api.h" /* Fetch enumeration etc */

/*- Namespace ---------------------------------------------------------------*/

/*- Enumerations ------------------------------------------------------------*/

/** Pixel repetation bit masks for TSupportedHdmiDviMode::pixelRepeatBitMask */
const uint32 KPixelRepeatOnce    = 0;         /**< No repetation, pixel sent once */
const uint32 KPixelRepeat2Times  = ( 1 << 0 );
const uint32 KPixelRepeat3Times  = ( 1 << 1 );
const uint32 KPixelRepeat4Times  = ( 1 << 2 );
const uint32 KPixelRepeat5Times  = ( 1 << 3 );
const uint32 KPixelRepeat6Times  = ( 1 << 4 );
const uint32 KPixelRepeat7Times  = ( 1 << 5 );
const uint32 KPixelRepeat8Times  = ( 1 << 6 );
const uint32 KPixelRepeat9Times  = ( 1 << 7 );
const uint32 KPixelRepeat10Times = ( 1 << 8 );
typedef enum
    {
    /** CEA mode, TCeaFixedMode */
    DISP_CEA = 0x00,
    /** Dmt mode, TDmtFixedMode */
    DISP_DMT = 0x01,
    } DISPE_STANDARD_MODE_TYPE;

/** Television broadcast standard */
typedef enum
    {
    DISP_UNDEF_SYSTEM = 0x0, /**< Invalid */
    DISP_NTSCJ        = 0x1,
    DISP_NTSCM        = 0x2,
    DISP_NTSC443      = 0x3,
    DISP_SECAM        = 0x4,
    DISP_PAL60        = 0x5,
    DISP_PALB         = 0x6,
    DISP_PALD         = 0x7,
    DISP_PALG         = 0x8,
    DISP_PALH         = 0x9,
    DISP_PALI         = 0xA,
    DISP_PALM         = 0xB,
    DISP_PALN         = 0xC,
    DISP_PALNC        = 0xD,
    } DISPE_TV_STANDARD;

/** HDMI/DVI source type */
typedef enum
    {
    DISP_SRC_TYPE_UNKN       = 0x00, /**< Invalid */
    DISP_SRC_TYPE_DIG_STB    = 0x01,
    DISP_SRC_TYPE_DVD        = 0x02,
    DISP_SRC_TYPE_DVHS       = 0x03,
    DISP_SRC_TYPE_HDD_VIDEO  = 0x04,
    DISP_SRC_TYPE_DVC        = 0x05,
    DISP_SRC_TYPE_DSC        = 0x06,
    DISP_SRC_TYPE_VIDEO_CD   = 0x07,
    DISP_SRC_TYPE_GAME       = 0x08,
    DISP_SRC_TYPE_PC_GENERAL = 0x09,
    } DISPE_HDMI_SOURCE_TYPE;

/** Analog Protection System (APS) levels */
typedef enum
    {
    DISP_ANALOG_PROTECTION_OFF     = 0,         /**< APS off */
    DISP_ANALOG_PROTECTION_AGC     = ( 1 << 0 ),/**< Automatic Gain Control */
    DISP_ANALOG_PROTECTION_AGC_2CS = ( 1 << 1 ),/**< Automatic Gain Control + 2-line Color Stripe */
    DISP_ANALOG_PROTECTION_AGC_4CS = ( 1 << 2 ),/**< Automatic Gain Control + 4-line Color Stripe */
    } DISPE_ANALOG_PROTECTION_LEVELS;

/** Copy Generation Management System - Analog (CGMS-A) levels.
    In conflict case, highest bit value will be taken in use.
    @see DISPE_CGMSA_CAPABILITIES */
typedef enum
    {
    DISP_CGMSA_COPY_FREELY  = 0x0,/**< Copying is allowed without restrictions */
    DISP_CGMSA_COPY_NO_MORE = 0x1,/**< Condition not to be used */
    DISP_CGMSA_COPY_ONCE    = 0x2,/**< One generation of copies is allowed */
    DISP_CGMSA_COPY_NEVER   = 0x3,/**< No copying is allowed */
    } DISPE_CGMSA_LEVELS;

/** Copy Generation Management System - Analog (CGMS-A) capabilities
    @see DISPE_CGMSA_LEVELS */
typedef enum
    {
    DISP_CGMSA_IEC_61880       = ( 1 << 0 ),/**< IEC 61880 */
    DISP_CGMSA_ETSI_EN_300_294 = ( 1 << 1 ),/**< ETSI EN 300 294 */
    DISP_CGMSA_CEA_608         = ( 1 << 2 ),/**< CEA 608 B */
    } DISPE_CGMSA_CAPABILITIES;

/** Type of executed selftest */
typedef enum
    {
    DISP_CONTROLLER = 0x0, /**< Tests tv controller hw (inside source device), e.g. host<->controller busses. */
    DISP_CONNECTOR  = 0x1, /**< Tests tv output connector, e.g. source<->HDMI-Tv */
    } DISPE_SELFTEST_TYPE;

/*- Data Structs ------------------------------------------------------------*/

/* CONTROL ->>>>>> */

/**
Current tv-out mode resolutions and aspect ratios
*/
typedef struct
    {
    /** Number of rows of frame (full rows) */
    uint32 linesPerFrame;
    /** Number of rows of field, interlaced. Same as linesPerFrame if progressive */
    uint32 linesPerField;
    /** Number of columns of frame */
    uint32 columns;
    /** Pixel aspect ratio = pixelAspectNumerator/pixelAspectDenominator */
    uint32 pixelAspectNumerator;
    /** @see pixelAspectNumerator */
    uint32 pixelAspectDenominator;
    } DISPS_TV_RESOLUTION;

/** The maximum length for the product name on TMDS bus */
const uint32 KProductNameSize = 8;
/** The maximum length for the product description on TMDS bus */
const uint32 KProductDescriptorsSize = 16;
/**
HDMI/DVI timings and settings. See detailed values of standard formats from OutputModes_X.xls
*/
typedef struct
    {
    /** @see ceaModeSetInsteadOfDmtMode. This is 0 if no any fixed modes set. */
    uint32 fixedMode;
    /** True=fixedMode is CEA mode. False=fixedMode is DMT mode. @see fixedMode */
    uint32 ceaModeSetInsteadOfDmtMode;

    /** True when HDCP is enabled on source output. False when HDCP disabled. @see dispCopyProtectionStatus()*/
    bool8 enableHdcp;

    /** Tv physical size in millimetres. Can be 0 if tvPhysicalImageAspectRatioNumerator is used. */
    uint32 tvPhysicalImageWidthMm;
    /** @see tvPhysicalImageWidthMm */
    uint32 tvPhysicalImageHeightMm;
    /** Tv physical aspect ratio. Can be NULL if tvPhysicalImageWidthMm is defined. Read from EDID.
        AR=tvPhysicalImageAspectRatioNumerator/tvPhysicalImageAspectRatioDenominator */
    uint16 tvPhysicalImageAspectRatioNumerator;
    /** @see tvPhysicalImageAspectRatioNumerator */
    uint16 tvPhysicalImageAspectRatioDenominator;

    /** Pixel clock. With CEA mode 1 and 59.94Hz this is 25175KHz */
    uint32 pixelClockKHz;

    /** Horizontal image width (resolution, columns).
        With CEA mode 1 this is 640 */
    uint16 horizontalActivePixels;
    /** Horizontal blanking time in pixels. Total HTime=horizontalActivePixels+horizontalBlankingPixels.
        With CEA mode 1 this is 160. Presented always as in CEA-model. */
    uint16 horizontalBlankingPixels;
    /** Vertical image height (resolution, lines). With CEA mode 1 this is 480 */
    uint16 verticalActiveLines;
    /** Vertical blanking time in lines. Total VTime=verticalActiveLines+verticalBlankingLines.
        With CEA mode 1 this is 45 */
    uint16 verticalBlankingLines;

    /** Horizontal pulse frontporch in pixels. With CEA mode 1 this is 16 */
    uint16 horizontalSyncOffsetPixels;
    /** Horizontal pulse duration in pixels. With CEA mode 1 this is 96 */
    uint16 horizontalSyncPulseWidthPixels;
    /** Horizontal border (decreases addressable area). With CEA mode 1 this is 0. */
    uint16 horizontalBorderPixels;
    /** Vertical pulse frontporch in lines. Fixed point with 10x, 1=10. 1.5=15.
        With CEA mode 1 this is 100 (actual value = 10).
        Presented always as CEA-model handle porches. For example E1024x768i87HzRB this is 00 */
    uint16 verticalSyncOffsetLinesField1;
    /** Vertical pulse duration in lines. With CEA mode 1 this is 2.
        With E1024x768i87HzRB this is 4. */
    uint16 verticalSyncPulseWidthLinesField1;
    /** Vertical border (decreases addressable area). With CEA mode 1 this is 0. */
    uint16 verticalBorderLinesField1;
    /** @see verticalSyncOffsetLinesField1. With progressive mode, this is unused.
        With E1024x768i87HzRB this is 10 (value 1). */
    uint16 verticalSyncOffsetLinesField2;
    /** @see verticalSyncPulseWidthLinesField1. With progressive mode, this is unused.
        With E1024x768i87HzRB this is 4. */
    uint16 verticalSyncPulseWidthLinesField2;
    /** @see verticalBorderLinesField1. With progressive mode, this is unused. */
    uint16 verticalBorderLinesField2;

    /** Left border (decreases addressable area). With CEA mode 1 this is 0. */
    uint16 leftBorderPixels;
    /** Right border (decreases addressable area). With CEA mode 1 this is 0. */
    uint16 rightBorderPixels;

    /** Horizontal sync polarity, false=Negative, true=Positive.
        With CEA mode 1 this is false. */
    bool8 horizontalSyncPolarity;
    /** Vertical sync polarity, false=Negative, true=Positive.
        With CEA mode 1 this is false. */
    bool8 verticalSyncPolarity;
    /** Wanted pixel repeat, can be used if mode supports.
        Otherwise horisontal resolution can be increased also.
        0 when repeat is disabled. With CEA mode 1 this is 0. */
    uint8 pixelRepeat;

    /** True if overscan is enabled (if Tv supports underscan). False otherwise */
    bool8 underscanEnabled;

    /** Pixel aspect ratio (PAR) numerator. PAR=pixelAspectRatioNumerator/pixelAspectRatioDenominator.
        With CEA mode 1 PAR=1/1. */
    uint8 pixelAspectRatioNumerator;
    /** @see pixelAspectRatioNumerator */
    uint8 pixelAspectRatioDenominator;

    /** True=HDMI, False=DVI. */
    bool8 hdmiConnector;

    /** Tv color coordinates (read from EDID) */
    DISPS_COLOR_COORDINATES tvColorCoordinates;

    /** HDMI version what Tv supports. Version combination is tvHdmiVersion.tvHdmiRevision.
        Zeroes if DVI. */
    uint8 tvHdmiVersion;
    /** @see tvHdmiVersion */
    uint8 tvHdmiRevision;

    /** Product name which to be sent to Tv in "Source Product Infoframe".
        Cell 0 contains first letter. All unused characters should be Null. */
    uint8 productName[ KProductNameSize ];
    /** Product Description which to be sent to Tv in "Source Product Infoframe".
        Cell 0 contains first letter. All unused characters should be Null. */
    uint8 productDescription[ KProductDescriptorsSize ];
    /** Source type which to be sent to Tv in "Source Product Infoframe". */
    DISPE_HDMI_SOURCE_TYPE sourceType;
    } DISPS_HDMI_SETTINGS;

/**
Configure object for analogue TV-Out, such as CVBS
*/
typedef struct
    {
    /** Analogue signal type */
    DISPE_TV_STANDARD tvSystem;
    /** Set analog protection system */
    DISPE_ANALOG_PROTECTION_LEVELS analogProtection;
    /** Set CGMS-A level */
    DISPE_CGMSA_LEVELS cgmsaLevel;
    } DISPS_ANALOGUE_SETTINGS;

/**
Configure object for TV-Out. Has all common between CVBS and HDMI and connector specific structs.
@code
__________________________ __________________________
|                        | |                        |
|   DISPS_HDMI_SETTINGS  | |DISPS_ANALOGUE_SETTINGS |
|                        | |                        |
¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯ ¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯¯¯¯
            `--------------------------´
             ____________|_____________
             |                        |
             |DISPS_TV_CONFIG_SETTINGS|
             |                        |
             ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
@endcode
*/
typedef struct
    {
    /** True=Interlaced scanning, False=Progressive scanning. */
    bool8 interlaced;
    /** Tv aspect ratio = imageRatioNumerator/imageRatioDenominator */
    uint8 imageRatioNumerator;
    /** @see imageRatioNumerator */
    uint8 imageRatioDenominator;
    /** True=flicker filter is enabled. False=disabled */
    bool8 flickerFilter;
    /** True=autodetect. False=cable is detected outside of this driver.
        Even True is set, Tv-out will not be enabled automatically, just cable detected. */
    bool8 autoDetection;

    /** Overscan in pixels. Set Left Top corner point. Zero when Tv supports overscan (0=underscan enabled)
        This should be "point" to active image area. Cannot point out of active image area.
        Cannot across with rightBottomCorner. And this allows overscan and position tuning. */
    uint16 leftTopCornerX;
    uint16 leftTopCornerY;
    /** Overscan in pixels. Set Right Bottom corner point. @see leftTopCornerX
        If driver supports centralizing only, then this has to be same as leftTopCornerX. */
    uint16 rightBottomCornerX;
    uint16 rightBottomCornerY;

    /** Settings for HDMI, used when DISPS_TV_CAPABILITIES::hdmiSettingsNeeded is true */
    DISPS_HDMI_SETTINGS hdmiSettings;
    /** Settings for analog Tv, used when DISPS_TV_CAPABILITIES::hdmiSettingsNeeded is false */
    DISPS_ANALOGUE_SETTINGS analogueSettings;

    /** Parameter which will be given in callbacks (DISPT_READY_CB). This-pointer for example. */
    void* cbParameter;

    /** Tv updating method. True when dispTvFlush() is used,
        False when Tv gets updating with other method (platform) */
    bool8 setBufferForTvInUsed;
    } DISPS_TV_CONFIG_SETTINGS;

/* <<<<<<- CONTROL */

/* CAPABILITY ->>>>>> */

/**
One mode struct for making capability query of own HW (phone capabilities).
*/
typedef struct
    {
    /** Standard CEA or DMT mode number. @see standardModeType */
    uint8 standardMode;
    /** Type of DISPE_STANDARD_MODE_TYPE. DISP_CEA if standardMode is CEA mode, DISP_DMT when DMT mode. */
    uint8 standardModeType;
    /** @see lowerRefreshRateSupported. If this is True (1), then higher frequency is supported. */
    bool8 higherRefreshRateSupported;
    /** If mode has two refresh rates. If is True (1), then lower frequency is supported.
        If mode has only one refresh rate, then this has to be True (1).
        E.g. CEA mode 1: 640x480p @59.94/60Hz, so this defines is 59.94Hz supported (lower) or not.
        Don't care if mode has only one refresh rate (e.g. CEA 17 720x576p @50Hz)
        lowerRefreshRateSupported  = 1 = Lower refresrate supported (e.g. 59.94Hz).
        higherRefreshRateSupported = 1 = Higher refreshrate supported (e.g. 60Hz) */
    bool8 lowerRefreshRateSupported;
    /** Bit mask of supported pixel repetation. 0=no repetation=KPixelSentOnce. */
    uint16 pixelRepeatBitMask;
    } DISPS_SUPPORTED_HDMI_MODE;

/**
Struct for own TV HW capabilities query.
*/
typedef struct
    {
    /** Own source HW supports HDCP (or compatible) */
    bool8 hdcpSupported;
    /** Own source HW supported APS levels. (bit mask) */
    DISPE_ANALOG_PROTECTION_LEVELS analogProtectionLevels;
    /** Supported CGMS-A WSS bits */
    DISPE_CGMSA_CAPABILITIES supportedCgmsa;

    /** Number of supported modes what to be called with dispGetSupportedHdmiMode */
    uint8 numberOfHdmiModes;

    /** HDMI version what (own) Hw supports. Version combination is sourceHdmiVersion.sourceHdmiRevision. */
    uint8 sourceHdmiVersion;
    /** @see sourceHdmiVersion */
    uint8 sourceHdmiRevision;

    /** True when DISPS_TV_CONFIG_SETTINGS::hdmiSettings is needed to be filled */
    bool8 hdmiSettingsNeeded;

    /** True when dispSetHdcpKey-call is needed. @see dispSetHdcpKey */
    bool8 hdcpKeysNeeded;

    /* CONTENT UPDATE -> */

    /** This tells to tv-out-driver client, is the sent buffer free after DISPT_READY_CB
        or is that buffer that buffer where tv-out gets updating all the time. Normally
        if tv-out-hw is external, and tv-buffer will be sent over some bus, this method returns
        False. Otherwise, when DMA reads all the time given buffer, and tv-out gets refresh
        directly from that buffer, then this returns True. */
    bool8 requiresFrameBuffer;
    /** This is true when pixel data to be updated with dispTvFlush().
        If this is false, then Tv-out HW can transfer/refresh Tv-out signal itself,
        without dispTvFlush() */
    bool8 contentUpdateNeeded;
    /** How many backbuffers Tv-out driver has. 0 when none */
    uint8 numberOfBackBuffers;

    /** Minimum scaling factor. E.g. if 1/2x is min, then this is 200 (100 / scalingMinDenominator). 1x = 100. 0xFFFF = infinity */
    uint16 scalingMinDenominator;
    /** Maximum scaling factor. E.g. if 2.5x is max, then this is 250 (scalingMaxNumerator / 100). 1x = 100. 0xFFFF = infinity */
    uint16 scalingMaxNumerator;

    /** True when position of Tv-out cannot be change, image is always centralized.
        False when position can be changed. @see rightBottomCorner */
    bool8 centralizingOnly;

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

    /** Rotation represents supported rotation capablities of HW. */
    DISPE_ROTATION rotations;
    /** True if HW can rotate each layer separately. False if only whole view can be rotated.
        (Hopefully will not be needed in NGA) */
    bool8 separateRotationPerLayer;

    /** All the possible colorkey modes supported by the interface */
    DISPE_COLORKEYMODE colorKeyModes;

    /** How many layers supported, at least 1 */
    uint8 layers;
    /** True when per layer alpha supported */
    bool8 perLayerAlpha;

    /** Color buffer formats natively supported by HW */
    DISPE_COLOR_FORMAT pixelFormats;
    /** Bit mask for features, which works with 24bpp aligned color mode */
    DISPE_FEATURE packedPixelsSupported;
    /** True if DMA buffers must be physically linear */
    bool8 requiresPhysicallyLinearBuffer;
    } DISPS_TV_CAPABILITIES;

/* <<<<<<- CAPABILITY */

/* TESTS ->>>>>> */

/**
Struct for output signal test
*/
typedef struct
    {
    /** Output color in RGB888 format */
    uint32 outColorRgb888;
    /** True when amplifier is disabled even Tv-out is ON */
    bool8 amplifierDisabled;
    } DISPS_TV_OUT_TEST_COLOR;

/* <<<<<<- TESTS */

/*- Constants ---------------------------------------------------------------*/

/** API version number. @see dispTvApiVersion().
    2:  Aspect ratio with enum/denom. SRM + HDCP structs and hdcpKeysNeeded.
    1:  First version */
const uint32 KTvApiVersionNumber = 2;

/** Chipset driver calls this, when something is executed.
    Callback must not be called in the API user thread context.
    @param  error       An error code
    @param  parameter   Given parameter (@see DISPS_TV_CONFIG_SETTINGS::cbParameter)
    @param  status      Listener status
    @param  isrContext  True when callback is called in interrupt context */
typedef void (*DISPF_LISTENER_CB)(DISPE_ERROR error, void* parameter, uint32 status, bool8 isrContext);

/*- Macros ------------------------------------------------------------------*/

/*- External Data -----------------------------------------------------------*/

/*- Variables ---------------------------------------------------------------*/

/*- Forward Declarations ----------------------------------------------------*/

/*- Functional Prototypes ---------------------------------------------------*/

/* VERSION -> */

/** Gets implemented chipset API version. Verify the return value to KTvApiVersionNumber.
    @param  api  API interface pointer, fetched from dispGetInterface()
    @see KTvApiVersionNumber
    @return Implemented Tv chipset API version, KTvApiVersionNumber (should match to client version) */
inline uint32 dispTvApiVersion(API_POINTER api);

/* <- VERSION */

/* CAPABILITY -> */

/** Returns Tv-out HW capabilities for caller.

    @param  api             API interface pointer, fetched from dispGetInterface()
    @param  tvCapabilities  Capability struct filled for caller
    @return an error code */
inline DISPE_ERROR dispGetTvCapabilities(API_POINTER api, DISPS_TV_CAPABILITIES* tvCapabilities);

/** Reads supported modes of HDMI hardware

    @see DISPS_TV_CAPABILITIES::numberOfHdmiModes
    @param  api               API interface pointer, fetched from dispGetInterface()
    @param  capabilityNumber  Mode number, begins from 0, up to dispGetTvCapabilities.
    @param  readMode          Method fills these for caller
    @return an error code */
inline DISPE_ERROR dispGetSupportedHdmiMode(API_POINTER api, uint32 capabilityNumber, DISPS_SUPPORTED_HDMI_MODE* readMode);

/* <- CAPABILITY */


/* CONTROL -> */

/** Before Tv-out using, dispSetTvConfig() must be called during boot and always
    when user is changed configurations.

    Fill correct values to DISPS_TV_CONFIG_SETTINGS object and give it by parameter.

    If driver can set settings without dispDisableTvOut()/dispEnableTvOut() it does that.
    Driver checks only changed members in DISPS_TV_CONFIG_SETTINGS, so if only overscan
    is changing, then rest of members are same. If just overscan is different,
    and driver can change that on the fly, method returns DISP_ERROR_NONE, if driver
    requires dispDisableTvOut/dispEnableTvOut sequence, it returns DISP_ERROR_HW_IS_BUSY.
    After DISP_ERROR_HW_IS_BUSY next dispEnableTvOut() enables new settings.
    callback will be called even in error case.

    Settings what has to be changed during Tv-out is enabled are at least copy protections,
    DISPS_HDMI_SETTINGS::enableHdcp and DISPE_ANALOG_PROTECTION_LEVELS::analogProtectionLevels.
    See that copy protection enable might be delayed, or even never enabled. dispCopyProtectionStatusListener()
    will be completed when protection status changes on Tv-output. If the API client
    wants to enable e.g. HDCP, Tv-driver tries to enable it ASAP. In case where 1st phase
    of authentication will fail, Tv-driver will continuously try to enable it, without
    timeout (but period can be long). Status listener will be completed if success.

    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  tvSettings  Struct which contains wanted setting (e.g. PAL/NTSC/...)
    @param  callback    Callback when ready
    @return an error code */
inline DISPE_ERROR dispSetTvConfig(API_POINTER api, const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPT_READY_CB callback);

/** Calculates DISPS_TV_RESOLUTION members but do not any HW configurations, so this is
    just calculator service for client use and does not anything else.

    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  tvSettings  Struct which contains wanted setting (e.g. PAL/NTSC/...)(user fills)
    @param  resolution  Driver fills resolutions for user
    @return an error code */
inline DISPE_ERROR dispResolutionQuery(API_POINTER api, const DISPS_TV_CONFIG_SETTINGS* tvSettings, DISPS_TV_RESOLUTION* resolution);

/** Enables Tv-out. Callback will be called even in error case.

    @pre dispSetTvConfig() is called without errors.
    @param  api       API interface pointer, fetched from dispGetInterface()
    @param  callback  Callback when enabled
    @return an error code */
inline DISPE_ERROR dispEnableTvOut(API_POINTER api, DISPT_READY_CB callback);

/** Disables Tv-out. Callback will be called even in error case.

    @pre dispEnableTvOut() is called without errors.
    @param  api       API interface pointer, fetched from dispGetInterface()
    @param  callback  Callback when disabled
    @return an error code */
inline DISPE_ERROR dispDisableTvOut(API_POINTER api, DISPT_READY_CB callback);

/** Asks is TV-out enabled or not
    @param  api  API interface pointer, fetched from dispGetInterface()
    @return State of TV-out, False=TV-out is disabled or if not supported (or error),
                             True=TV-out is enabled */
inline bool8 dispIsTvOutEnabled(API_POINTER api);

/** This method makes possible to send some messages for whole chipset driver stack
    When chipset drivers will get the message call and name does not match for that driver,
    then it has to forward message for next driver in same driver stack through dispDriverMessage.

    If message==DISP_MSG_PING:
    Chipset driver will forward same message for
    next chipset drivers in the stack (dispDriverMessage), then all drivers call 'callback' with
    their own name (CHIPSET_DRV_NAME) and got message (DISP_MSG_PING). With this, topmost
    driver can make query, what components stack has. Topmost caller sets param=0, when chipset
    driver calls this forward, it increases param by one (param=1). If chipset driver uses to
    separated chipset drivers, both will to be called with param=1. Then 'param' means stack level.
    In callback chipset drivers will set given param to DISPT_MSG_CB's value-parameter.

    If message=DISP_MSG_SELFTEST:
    If given name (receiver) matches to driver name, then the
    driver will execute self test. When self test is ready, it reports test result with 'callback'
    for caller. Chipset drivers will forward the same message, if name (receiver) and their own
    name doesn't match. param is type of the DISPE_SELFTEST_TYPE.

    If message=DISP_MSG_PRODTEST:
    Production tests of TV-out, see more information from each platform's specifications.
    Sets test figure on TV, e.g. white display.
    When production tests are completed, remember close Tv-Out by calling dispDisableTvOut().
    param is pointer to DISPS_TV_OUT_TEST_COLOR.

    @see dispDriverMessage in display chipset API

    @param  api  API interface pointer, fetched from dispGetInterface()
    @param  receiver    Message receiver name (same what is stored in Interface Storage)
    @param  message     Message identifier
    @param  param       Optional, has different meaning per message
    @param  callback    Callback when message actions are executed
    @return an error code */
inline DISPE_ERROR dispTvMessage(API_POINTER api, CHIPSET_DRV_NAME receiver, DISPE_DRV_MSG message, uint32 param, DISPT_MSG_CB callback);

/* <- CONTROL */


/* LISTENERS AND COPY PROTECTION -> */

/** Registers listener for Tv-out cable. (does not enable Tv, only listener for cable).
    When dispCableListener listener is added, listener will be completed immediatelly,
    that makes possible to read boot time status.

    If cable is attached, DISPF_LISTENER_CB's status==1
    If cable is detach, DISPF_LISTENER_CB's status==0

    @param  api       API interface pointer, fetched from dispGetInterface()
    @param  callback  Function pointer to user callback.
                      callback which to be called when cable is attached/detach
    @param  add       True=callback will be added. False=callback will be removed.
    @return an error code */
inline DISPE_ERROR dispCableListener(API_POINTER api, DISPF_LISTENER_CB callback, bool8 add);

/** Listener for status of copyprotection (e.g. HDCP). After this, check newest status with dispCopyProtectionStatus()
    or check the callback value.

    If protection is handshaked and enabled, DISPF_LISTENER_CB's status==1
    If protection is disabled, DISPF_LISTENER_CB's status==0

    @see dispCopyProtectionStatus()
    @param  api                  API interface pointer, fetched from dispGetInterface()
    @param  copyProtectionChangedCb  Will be called when protection is disabled/enabled in output signal.
                                     Second parameter of callback is status of copy protection (bool)
    @param  add                  True=callback will be added. False=callback will be removed.
    @return an error code */
inline DISPE_ERROR dispCopyProtectionStatusListener(API_POINTER api, DISPF_LISTENER_CB copyProtectionChangedCb, bool8 add);

/** Asks is HDCP/macrovision enabled or not at the moment in Tv-output.
    If HDCP is available, it can be enabled with DISPS_HDMI_SETTINGS::enableHdcp using
    dispSetTvConfig().

    @param  api  API interface pointer, fetched from dispGetInterface()
    @return status of copy protection (True=enabled, False=disabled) */
inline bool8 dispCopyProtectionStatus(API_POINTER api);

/** Sets newest SRM list to the Tv-driver. Has to be done before dispEnableTvOut if digital
    Tv-output. Tv-driver has to parse SRM open, it is in the same form what HDCP specification
    describes.

    If copy protection authentication is already executed, the SRM-list can be still
    updated, and Tv-driver has to re-check the revocation list (without 1st phase of reauthentication).

    @param  api        API interface pointer, fetched from dispGetInterface()
    @param  srmData    Pointer to SRM. Tv-driver stores the SRM and client
                       can delete the SRM after function call.
    @param  srmInBytes SRM size in bytes.
    @return an error code */
inline DISPE_ERROR dispSetSrm(API_POINTER api, void* srmData, uint32 srmInBytes);

/** Sets the unique HDCP and KSV for Tv-driver knowledge. Has to be done before dispEnableTvOut if digital
    Tv-output. Tv-driver has to parse HDCP data (hdcpData) open, it is in platform specific form.

    All instances who handle the HDCP and KSV -keys, has to overwrite HDCP data (zeroes) in registers, stacks
    and heaps after this call (and perhaps even before this call, in all SW levels) and when HW is initialised.

    Depending of HW, HDCP+KSV can be burned with "eFuses" in Tv-HW. Thus, Tv-driver requires to get the keys
    only once in production line.
    When/if eFuses are burned, DISPS_TV_CAPABILITIES::hdcpKeysNeeded can be false on next time
    when capabilities will be read, and the API client will not call this function anymore.
    DISPS_TV_CAPABILITIES::hdcpKeysNeeded is true when Tv-HW needs to get HDCP+KSV.
    The reason for this mechanism is to avoid to hold the HDCP-keys in system RAM.

    @param  api         API interface pointer, fetched from dispGetInterface()
    @param  hdcpData    Pointer to HDCP. Tv-driver stores the HDCP and client
                        can delete the HDCP after function call. Data is in platform specific form.
    @param  hdcpInBytes HDCP struct (hdcpData) size in bytes.
    @return an error code */
inline DISPE_ERROR dispSetHdcpKey(API_POINTER api, void* hdcpData, uint32 hdcpInBytes);

/* <- LISTENERS AND COPY PROTECTION */


/* CONTENT UPDATE -> */

/** Content update to be used if DISPS_TV_CAPABILITIES::contentUpdateNeeded=True */

/** Sets all per layer settings for chipset driver. Settings will be used on next dispFlush()-call.
    In double buffered case, this method to be call every time before dispTvFlush, with different buffer
    addresses. Tv driver is responsible to optimise unneeded reinitialisation. It should store
    previous settings and compare changed settings of DISPS_FINAL_VIEW, and use that result
    for HW reinitialisation.

    @see dispTvFlush
    @param  api  API interface pointer, fetched from dispGetInterface()
    @param  finalView   Source buffer and final composition settings
    @return an error code */
inline DISPE_ERROR dispSetTvFinalView(API_POINTER api, const DISPS_FINAL_VIEW* finalView);

/** Prepares Tv update according to latest dispSetTvFinalView parameters.
    After this, if DISPS_TV_CAPABILITIES.requiresFrameBuffer is false, work buffer is ready.

    DISPS_TV_CAPABILITIES.requiresFrameBuffer==false:
      callback will be called when display buffer is transferred to the display.
    DISPS_CAPABILITIES.requiresFrameBuffer==true:
      callback will be called when display buffer starting to be visible. So when callback is called
      any pixel of flush is not yet shown. And after that given buffer works as framebuffer
      until next's flush callback will be called. So caller should be aware of that
      to avoiding tearing (no draw to buffer if that is still work as framebuffer).

    @see dispFlush
    @see dispSetFinalView
    @param  api  API interface pointer, fetched from dispGetInterface()
    @param  changedArea Changed areas, rectangle per layer. Chipset driver can ignore and transfer bigger part.
    @param  callback    To be called when preparation is ready, even error occured. Can be NULL.
    @return an error code */
inline DISPE_ERROR dispTvFlush(API_POINTER api, const DISPS_UPDATE* changedArea, DISPT_READY_CB callback);

/* <- CONTENT UPDATE */


/*- Inline Functions --------------------------------------------------------*/

#include "tv_chipset_api.inl"

#endif /* TV_CHIPSET_API_H */

/* End of File */

