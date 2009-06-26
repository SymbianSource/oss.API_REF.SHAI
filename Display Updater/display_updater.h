/*
  display_updater.h

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

  <p>This is adaptation component which hides hw-drivers from users.
     Because this is adaptation API, and user is also adaptation, this
     API is not binary compatible, only source compatible.

     Following tags definities the category where method/member/enum causes:
     [@Update]    Display updating
     [@Rotate]    Display rotation
     [@Overlay]   Display Hw made overlay/composition
     [@Variation] Dynamic variation of display Hw
     </p>

*/
/** @file

API for updating and controlling display.

*/


#ifndef __DISPLAY_UPDATER_H__
#define __DISPLAY_UPDATER_H__


//- Include Files  ----------------------------------------------------------

#ifndef __KERNEL_MODE__
 #include <e32base.h>
#else
 #include <e32cmn.h>
#endif //__KERNEL_MODE__

//- Enumerations and consts -------------------------------------------------

//API version number
// 3:  ARGB4444
// 2:  Pre-multiplied alpha modes
// 1:  First version
const TUint KDisplayUpdaterApiVersion = 3;

/** Display rotation */
enum TDispRotation
    {
    EInvalidDeg   = 0x0000,    /**< Initialisation value, don't use */
    ERotate0Deg   = ( 1 << 0 ),/**< No rotation */
    ERotate90Deg  = ( 1 << 1 ),/**< 90 degree   */
    ERotate180Deg = ( 1 << 2 ),/**< 180 degree  */
    ERotate270Deg = ( 1 << 3 ),/**< 270 degree  */
    };

/** Color formats */
const TUint32 KDispLittleEndian = 0x0;
const TUint32 KDispBigEndian    = 0x1;
enum TDisplayPixelFormats
    {
    EPixelFormatInvalid     = 0,                               /**< Initialisation value, don't use */
    EPixelFormatXRgb8888Le  = ( 1 << 1 )  | KDispLittleEndian, /**< = EColor16MU */
    EPixelFormatXRgb8888Be  = ( 1 << 1 )  | KDispBigEndian,
    EPixelFormatARgb8888Le  = ( 1 << 2 )  | KDispLittleEndian, /**< = EColor16MA */
    EPixelFormatARgb8888Be  = ( 1 << 2 )  | KDispBigEndian,
    EPixelFormatARgb8888LeP = ( 1 << 3 )  | KDispLittleEndian, /**< = EColor16MAP, Pre-multiplied */
    EPixelFormatARgb8888BeP = ( 1 << 3 )  | KDispBigEndian,
    EPixelFormatRgb888Le    = ( 1 << 4 )  | KDispLittleEndian,
    EPixelFormatRgb888Be    = ( 1 << 4 )  | KDispBigEndian,
    EPixelFormatRgb565Le    = ( 1 << 5 )  | KDispLittleEndian, /**< = EColor64K */
    EPixelFormatRgb565Be    = ( 1 << 5 )  | KDispBigEndian,
    EPixelFormatARgb1555Le  = ( 1 << 6 )  | KDispLittleEndian,
    EPixelFormatARgb1555Be  = ( 1 << 6 )  | KDispBigEndian,
    EPixelFormatARgb1555LeP = ( 1 << 7 )  | KDispLittleEndian, /**< Pre-multiplied */
    EPixelFormatARgb1555BeP = ( 1 << 7 )  | KDispBigEndian,
    EPixelFormatARgb4444Le  = ( 1 << 8 )  | KDispLittleEndian,
    EPixelFormatARgb4444Be  = ( 1 << 8 )  | KDispBigEndian,
    EPixelFormatARgb4444LeP = ( 1 << 9 )  | KDispLittleEndian, /**< Pre-multiplied */
    EPixelFormatARgb4444BeP = ( 1 << 9 )  | KDispBigEndian,
    EPixelFormatYCbCr422Le  = ( 1 << 10 ) | KDispLittleEndian, /** 422 is assumed to be interleaved (as pixel pairs) */
    EPixelFormatYCbCr422Be  = ( 1 << 10 ) | KDispBigEndian,
    EPixelFormatYCbCr420Le  = ( 1 << 11 ) | KDispLittleEndian, /** 420 is assumed to be planar */
    EPixelFormatYCbCr420Be  = ( 1 << 11 ) | KDispBigEndian,
    EPixelFormatPlatform    = ( 1 << 12 ),                     /**< Non standard, platform specific format */
    };

/** YCbCr standard bit mask */
enum TDisplayYCbCrBitMask
    {
    EYCbCrBitMaskInvalid      = 0x0000,    /**< Can be set when RGB */
    EYCbCrBitMaskFullRange    = ( 1 << 0 ),/**< Full range 0-255 */
    EYCbCrBitMaskLimitedRange = ( 1 << 1 ),/**< Limited range 16-235 */
    };

/** Colorspace */
enum TDisplayColorSpace
    {
    EColorSpaceNone               = 0x0000,     /**< Initialisation value, don't use */
    EColorSpaceSRgb               = ( 1 << 0 ), /**< sRGB */
    EColorSpaceLinear             = ( 1 << 1 ), /**< Linear color space */
    EColorSpaceFixedDisplayLinear = ( 1 << 2 ), /**< Fixed display color space - Buffer pixels are linearised RGB for Fixed colorspace */
    EColorSpaceFixedDisplay       = ( 1 << 3 ), /**< Fixed display color space, one fixed colorspace, case-by-case */
    EColorSpaceColorCoordinates   = ( 1 << 4 ), /**< Free color coordinates definition. @see TColorCoordinates */
    };

/** Advanced feature bit masks - Used for capability query */
enum TDisplayFeatures
    {
    EFeatureNone        = 0x0000,     /**< Initialisation value */
    EFeatureScaling     = ( 1 << 0 ), /**< Scaling */
    EFeatureRotation    = ( 1 << 1 ), /**< 90, 180 or 270 rotation */
    EFeatureOverlay     = ( 1 << 2 ), /**< Overlay without colorkey and alpha */
    EFeatureYCbCr       = ( 1 << 3 ), /**< YCbCr support */
    EFeatureYCbCrPlanar = ( 1 << 4 ), /**< YCbCr planar */
    EFeatureAlphaBlend  = ( 1 << 5 ), /**< Overlay with alpha */
    EFeatureInternalBuf = ( 1 << 6 ), /**< Internal buffers (display driver's own) */
    EFeatureExternalBuf = ( 1 << 7 ), /**< External buffers */
    };

/** Buffer purpose - TODO are these enough */
enum TBufferPurpose
    {
    EPurposeNone     = 0x0000,     /**< Initialisation value, don't use */
    EPurposeUi       = ( 1 << 0 ), /**< UI graphics */
    EPurposeOpenGlVg = ( 1 << 1 ), /**< OpenGl|ES or OpenVg. Game or pure graphics, not UI. */
    EPurposeVideo    = ( 1 << 2 ), /**< Video playback */
    EPurposeCamera   = ( 1 << 3 ), /**< Camera viewfinder */
    EPurposeImage    = ( 1 << 4 ), /**< Still image */
    EPurposeCompose  = ( 1 << 5 ), /**< Composition destination buffer */
    };

//- Structs -----------------------------------------------------------------

/**
[@Variation]

CIE 1931 color space coordinates. To be defined if EColorSpaceColorCoordinates is used.
Fixed point is 10th bit.
E.g. If iRed.iY=625, it should be divided by 1024 (2^10) for getting real value 0.61035...
*/
class TColorCoordinates
    {
    public:
        TColorCoordinates():iRed(0,0),
                            iGreen(0,0),
                            iBlue(0,0),
                            iWhite(0,0)
                            {}
        ///Red chromaticity coordinates (X,Y)
        TPoint iRed;
        ///Green chromaticity coordinates
        TPoint iGreen;
        ///Blue chromaticity coordinates
        TPoint iBlue;
        ///White chromaticity coordinates
        TPoint iWhite;
    };

/**
[@Update]

Describes display buffer informations.

One of four to be set, iLinearAddress, iPhysicalAddress, iBufferAdaptationId or iBufferRChunkHandle.
It means that if iBufferAdaptationId is only set member, adaptation to have rights and access to use
only that ID for doing update, and e.g. addresses are not needed.
*/
class TBufferInfo
    {
    public:
        TBufferInfo():iLinearAddress(NULL),
                      iPhysicalAddress(NULL),
                      iBufferAdaptationId(0),
                      iBufferRChunkHandle(0),
                      iStride(0),
                      iOffsetToY(0),
                      iOffsetToCb(0),
                      iOffsetToCr(0),
                      iBufferWidth(0),
                      iBufferHeight(0),
                      iBufferFormat(EPixelFormatInvalid),
                      iYCbCrBitMask(EYCbCrBitMaskInvalid),
                      iColorSpace(EColorSpaceSRgb),
                      iColorCoordinates()
                      {}
        ///Linear address to begin of the pixels
        TAny* iLinearAddress;
        ///Physical address to begin of the pixels. If missing, physical address will be converted from iLinearAddress
        TUint32 iPhysicalAddress;
        ///Buffer ID for adaptation internal use
        TUint32 iBufferAdaptationId;
        ///RChunk handle ID for this buffer (RHandleBase::Handle()). Can be set 0 if not needed.
        TInt iBufferRChunkHandle;

        ///The color buffer stride in bytes. With 420 planar, this tells one line Y-components stride.
        TUint16 iStride;

        ///Offset from iLinearAddress to Y-components (needed if planar, otherwise can be set 0)
        TUint32 iOffsetToY;
        ///Offset from iLinearAddress to Cb-components (needed if planar, otherwise can be set 0)
        TUint32 iOffsetToCb;
        ///Offset from iLinearAddress to Cr-components (needed if planar, otherwise can be set 0)
        TUint32 iOffsetToCr;

        ///Buffer width in pixels
        TInt16 iBufferWidth;
        ///Buffer height in pixels
        TInt16 iBufferHeight;

        ///Pixel format
        TDisplayPixelFormats iBufferFormat;
        ///Full/limited range. Required if YCbCr defined in iBufferFormat
        TDisplayYCbCrBitMask iYCbCrBitMask;
        ///Buffer colorspace, most used is EColorSpaceSRgb
        TDisplayColorSpace iColorSpace;
        ///Buffer colorspace, this is used if iColorSpace = EColorSpaceColorCoordinates
        TColorCoordinates iColorCoordinates;
    };

/**
[@Update][@Overlay]

Describes display scaling, cropping, etc. view settings
*/
class TDisplayViewSettings
    {
    public:
        TDisplayViewSettings():iPerLayerAlphaValue(0xFF),
                               iMainBackgroundColor(0x000000),//Black
#ifndef __KERNEL_MODE__
                               iSourceScissor(0,0,0,0),//startCol, startRow, lastCol, lastRow
                               iDestinationScaledRect(0,0,0,0),
#endif //__KERNEL_MODE__
                               iLayerRotation(EInvalidDeg),
                               iUsageHint(EPurposeNone),
                               iTearingFree(EFalse)
                               {}
    public:
        ///Per layer alpha if supported, 0x00-0xFF
        TUint8 iPerLayerAlphaValue;
        ///RGB888 background color. Farest layer in the view. Valid only when layer number 0.
        TUint32 iMainBackgroundColor;
#ifndef __KERNEL_MODE__
        /** Inputcrop (viewport) from source buffer.
            To be <= than iBufferWidth&iBufferHeight */
        TRect iSourceScissor;
        /** This is scaled resolution to destination (to display) (extent).
            Set to same with iSourceScissor if scaling is disabled.
            To be <= than display panel native resolution and are given in current
            global orientation resolution (SetRotation()). */
        TRect iDestinationScaledRect;
#endif //__KERNEL_MODE__
        /** Per layer orientation. This to be given compared to global orientation (SetRotation()).
            If global orienation is ERotate90Deg and this has ERotate270Deg -> no rotation.
            Sequence for all view operations is:
            iSourceScissor->SetRotation()->iLayerRotation->iDestinationScaledRect */
        TDispRotation iLayerRotation;
        ///Bit mask - Purpose of buffer
        TBufferPurpose iUsageHint;
        ///ETrue when tearing free needed. Remember that TE-logic increases power consumption.
        TBool iTearingFree;
    };

/**
[@Variation]

Describes the display driver capabilities and properties
*/
class TDisplayDrvInfo
    {
    public:
        inline TDisplayDrvInfo():iPanelResolution(),
                                 iPanelRefreshRateHz(0),
                                 iNumberOfBuffers(0),
                                 iSupportedFormats(EPixelFormatInvalid),
                                 iPixelAspectRNumerator(1),//Square pixel by default (1/1)
                                 iPixelAspectRDenominator(1),
                                 iSupportedRotations(EInvalidDeg),
                                 iSupportedPerLayerRotations(EInvalidDeg),
                                 iRotationWorksWithTheseFeatures(EFeatureNone),
                                 iScalingWorksWithTheseFeatures(EFeatureNone),
                                 iScalingMinDenominator(0),
                                 iScalingMaxNumerator(0),
                                 iNumberOfOverlays(0),
                                 iDestinationColorSpace(EColorSpaceNone),
                                 iDestinationColorCoordinates(),
                                 iGivenBufferWorksAsFrameBuffer(EFalse),
                                 iVariableResolution(EFalse),
                                 iOverscanToBeDrawn(EFalse),
                                 iDisplayOn(EFalse)
                                 {}
    public:
        ///Display panel resolution. Parameters will not swap when rotated.
        TSize iPanelResolution;
        ///Display panel twips. 0 when unknown (TV). Parameters will not swap when rotated.
        TSize iPanelTwips;
        ///Display panel refresh rate. E.g. if 60Hz, then this is 6000 (iPanelRefreshRateHz / 100). 29.97Hz = 2997.
        TUint iPanelRefreshRateHz;
        ///How many composition buffers (internal) are reserved for display. @see GetCompositionBuffer().
        TUint8 iNumberOfBuffers;

        ///Bit mask of supported pixel formats for external buffers
        TDisplayPixelFormats iSupportedFormats;
        ///Display pixel aspect ratio numerator (AR=iPixelAspectRNumerator/iPixelAspectRDenominator)
        TUint16 iPixelAspectRNumerator;
        ///Display pixel aspect ratio denominator (@see iPixelAspectRNumerator)
        TUint16 iPixelAspectRDenominator;

        ///Bit mask of supported global rotations (SetRotation()) [@Rotate]
        TDispRotation iSupportedRotations;
        ///Bit mask of supported per layer rotations (TDisplayViewSettings::iLayerRotation) [@Rotate]
        TDispRotation iSupportedPerLayerRotations;
        ///Bitmask for features when display driver can do rotation [@Rotate]
        TDisplayFeatures iRotationWorksWithTheseFeatures;

        ///Bitmask for features when display driver can do scaling
        TDisplayFeatures iScalingWorksWithTheseFeatures;
        ///Minimum scaling factor. E.g. if 1/2x is min, then this is 200 (100 / iScalingMinDenominator). 1x = 100. 0xFFFF = infinity
        TUint16 iScalingMinDenominator;
        ///Maximum scaling factor. E.g. if 2.5x is max, then this is 250 (iScalingMaxNumerator / 100). 1x = 100. 0xFFFF = infinity
        TUint16 iScalingMaxNumerator;

        ///Value how many layers can be set to display driver (overlays). Minimum is 0, if overlays are not supported. [@Overlay]
        TUint8 iNumberOfOverlays;

        /** Destination display colorspace - buffers can be delivered in these formats. Bit mask.
            If EColorSpaceColorCoordinates is set, then display driver has capability to convert
            input (TBufferInfo.iColorCoordinates/iColorSpace) to needed space (iDestinationColorCoordinates),
            otherwise GCE has this responsibility */
        TDisplayColorSpace iDestinationColorSpace;
        ///Destination display colorspace coordinates, valid if non-zeroes.
        TColorCoordinates iDestinationColorCoordinates;

        ///If ETrue, given buffers works as frame buffer and display panel gets refresh from that (video display)
        TBool iGivenBufferWorksAsFrameBuffer;

        ///If ETrue, display supports many resolutions and those can be set dynamically
        TBool iVariableResolution;

        ///ETrue when composition should draw overscan (inc. position) to destination buffer
        TBool iOverscanToBeDrawn;

        ///ETrue when display panel is ON, EFalse when OFF
        TBool iDisplayOn;
    };

///Typedef for layer order, like a z-order. 0 is farest, and bigger is more nearest. @see TDisplayDrvInfo.iNumberOfLayers [@Overlay]
typedef TUint TLayerNumber;

//- Macros ------------------------------------------------------------------


//- External Data -----------------------------------------------------------


//- Variables ---------------------------------------------------------------


//- Forward Declarations ----------------------------------------------------


//- Class Definitions -------------------------------------------------------

#ifndef __KERNEL_MODE__

/**
Adaptation API for display updating purpose
*/
class CDisplayUpdater : public CBase
    {
    public:
        /** [@Variation] Gets API version number. Compare this to KDisplayUpdaterApiVersion, must match.
            @return  KDisplayUpdaterApiVersion which is used for display driver */
        IMPORT_C static TUint ApiVersion();


        /** Creates object. Only one client can be registered (hold the object) for one display.
            @param   aDisplayNumber  Which display is connected, primary display is 0
            @return  new CDisplayUpdater,  NULL if there is error, otherwise CDisplayUpdater */
        IMPORT_C static CDisplayUpdater* NewL(TInt aDisplayNumber);
        ///Object destructor
        virtual ~CDisplayUpdater(){};


        /** [@Variation] Returns API provided properties to parameter
            @param  aInfo     Supported features, filled by driver */
        virtual void GetDisplayProperties(TDisplayDrvInfo& aInfo) = 0;
        /** [@Variation] Listener for changing display configuration. When this listener is completed,
            GetDisplayProperties and needed actions to be executed.
            @see GetDisplayProperties
            @see CancelConfigurationListener
            @param  aCompletedWhenReady  Will be completed when configuration is changed.
            @return KErrNone if success */
        virtual TInt ConfigurationListener(TRequestStatus& aCompletedWhenReady) = 0;
        /** [@Variation] Cancels pending of ConfigurationListener.
            @return KErrNone if success */
        virtual TInt CancelConfigurationListener() = 0;


        /** [@Update] Get method for DSA UI-buffer. This is same buffer what can be fetched from HAL.
            This call may allocate DSA-buffer, so to be called only when DSA-buffer is needed.
            @see FreeDsaBuffer
            @param  aBuffer   Buffer settings, filled by driver
            @return KErrNone if success */
        virtual TInt GetDsaBuffer(TBufferInfo& aBuffer) = 0;
        /** [@Update] This will be called when DSA buffer is not anymore needed/used by compositor.
            After this call, DSA-buffer memory may be de-allocated.
            @see GetDsaBuffer
            @return KErrNone if success */
        virtual TInt FreeDsaBuffer() = 0;
        /** [@Update] Get method for composition engine's destination buffer.
            Needed if configuration has display driver allocated composition buffers.
            @see TDisplayDrvInfo.iNumberOfBuffers
            @see FreeCompositionBuffer
            @param  aBufferNumber  Buffer number which to be get (first is 0, @see TDisplayDrvInfo.iNumberOfBuffers)
            @param  aBuffer        Returned buffer info for caller
            @return KErrNone if success */
        virtual TInt GetCompositionBuffer(TUint32 aBufferNumber, TBufferInfo& aBuffer) = 0;
        /** [@Update] This will be called when composition buffer is not anymore needed/used by compositor,
            then the display is disconnected or shut down. Used when display driver allocated composition buffers
            are used. After this call, the buffer may be de-allocated.
            @see GetCompositionBuffer
            @param  aBufferNumber  Buffer number which to be freed
            @return KErrNone if success */
        virtual TInt FreeCompositionBuffer(TUint32 aBufferNumber) = 0;


        /** [@Update] If external buffers are used (display driver does not own),
            those must be bound in here before use.
            @param  aBuffer  New buffer for display driver knowledge
            @return KErrNone if success */
        virtual TInt BindExternalBuffer(const TBufferInfo& aBuffer) = 0;
        /** [@Update] Unbinds buffer if that is not wanted use anymore for displaying use.
            Buffer should not be visible on screen when unbinding happens.
            @pre Buffer is not "on screen" anymore, and display driver does not work with that.
            @pre BindExternalBuffer is called for this buffer, without errors.
            @param  aBuffer  Buffer to be removed from display driver knowledge
            @return KErrNone if success */
        virtual TInt UnbindExternalBuffer(const TBufferInfo& aBuffer) = 0;


        /** [@Update][@Overlay] Constructs view on the display. Layer parameter tells which layer is set, and layernumber
            means z-order of view. 0 to be always defined before Flush. Layer 0 is on background of layer 1.
            If is needed to remove e.g. layer 1, then replace default (clear) TDisplayViewSettings object.
            @param  aLayer         Z-order where layer to be set. 0 must be always defined. [@Overlay]
            @param  aViewSettings  This layer view information, including changed areas [@Update at least for layer 0][@Overlay]
            @param  aBuffer        Buffer which matching to this layer settings [@Update at least for layer 0][@Overlay]
            @return KErrNone if success */
        virtual TInt SetView(TLayerNumber aLayer, const TDisplayViewSettings& aViewSettings, const TBufferInfo& aBuffer) = 0;
        /** [@Update] Changes TBufferInfo settings of layer. Settings will be taken use in next flush.
            @param  aLayer             Z-order where layer to be set. 0 must be always defined. [@Overlay]
            @param  aLatestChangedRect Changed area rectangle. Set fullscreen if disabled. Driver can ignore these.
                                       To be smaller than iBufferWidth&iBufferHeight, and 0,0,0,0 means full screen [@Update]
            @param  aBuffer            New buffer which matching to this layer settings [@Update]
            @return KErrNone if success */
        virtual TInt SetBuffer(TLayerNumber aLayer, const TRect& aLatestChangedRect, const TBufferInfo& aBuffer) = 0;


        /** [@Update] Flushes current view to display. Asynchronous method.
            TDisplayDrvInfo.iGivenBufferWorksAsFrameBuffer==EFalse:
              TRequestStatus will be completed when display buffer is transferred to the display.
            TDisplayDrvInfo.iGivenBufferWorksAsFrameBuffer==ETrue:
              TRequestStatus will be completed when display buffer is starting to be visible. So when request is completed
              any pixel of flush is not yet shown. And after that, given buffer works as framebuffer
              until next's flush TRequestStatus will be completed. So caller should be aware of that,
              to avoiding tearing (no draw to buffer if that is still work as framebuffer).
            @param  aCompletedWhenReady  Will be completed when transfer is ready (or just begun, see above)
            @return KErrNone if success
                    KErrInUse if SetOrientation or other settings are changing */
        virtual TInt Flush(TRequestStatus& aCompletedWhenReady) = 0;
        /** [@Update] Cancels all pending Flush operations. Should not be called normally at all, correct way is to wait
            that both pending Flush TRequestStatuses are completed.
            @return KErrNone if success */
        virtual TInt FlushCancelAll() = 0;


        /** [@Rotate] Changes orientation of full screen. New flushes are not welcome before TRequestStatus is completed.
            Got buffers should not be under read/write while this mehtod is ongoing.
            All buffers should be read (GetDsaBuffer & GetCompositionBuffer & GetDisplayProperties) again after completed and ready.
            SetView to be called with valid parameters after rotation.
            @param  aNewOrientation      New orientation
            @param  aCompletedWhenReady  Will be completed when orientation is changed
            @return KErrNone if success, KErrNotSupported if driver cannot handle orientation */
        virtual TInt SetRotation(TDispRotation aNewOrientation, TRequestStatus& aCompletedWhenReady) = 0;
        /** [@Update] Changes resolution of full screen. New flushes are not welcome before TRequestStatus is completed.
            To be called every time before first SetView().
            Got buffers should not be under read/write while this mehtod is ongoing.
            All buffers should be read (GetDsaBuffer & GetCompositionBuffer & GetDisplayProperties) again after completed and ready.
            SetView to be called with valid parameters after rotation.
            @param  aNewResolution       New resolution in 0deg
            @param  aCompletedWhenReady  Will be completed when resolution is changed
            @return KErrNone if success
                    KErrNotSupported if display cannot change resolution (TDisplayDrvInfo.iVariableResolution==EFalse)
                    KErrArgument if display resolution is not supported (aNewResolution) */
        virtual TInt SetResolution(TSize aNewResolution, TRequestStatus& aCompletedWhenReady) = 0;

    protected:
        ///Constructor
        CDisplayUpdater(){};
        ///Second phase constructor
        virtual void ConstructL(TInt aDisplayNumber) = 0;
    };

#endif //__KERNEL_MODE__

//- Global Function Prototypes ----------------------------------------------


//- Inline Functions --------------------------------------------------------


#endif //__DISPLAY_UPDATER_H__

// End of File


