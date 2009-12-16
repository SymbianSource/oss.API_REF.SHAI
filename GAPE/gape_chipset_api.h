/*
Nokia/Devices/R&D/SD/SSS
CONFIDENTIAL
Deliverable software



            GAPE_CHIPSET_API.H
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
@brief gape_chipset_api.h

This a header file of gape_chipset_api.h

@publishedDeviceAbstraction
*/

#ifndef __GAPE_H__
#define __GAPE_H__

// Include files

#include <kern_priv.h>
#include <gape_descriptors.h>
// Constants
// defined in gape_descriptors.h

// Macros

// Data types

// Function prototypes

// Forward declarations

// Class declaration

/**
@brief Class description
/**

Generic APE-side library for kernel side clients.

*/
class GApe
    {
    public:
        /**
            Return an instance to GApe interface. This method returns the
            only GApe instance system can have, it is not possible to create
            new instances of this class.

            @return GApe* An instance to GApe class
            @pre Pre-condition: do not call from an ISR
        */
        static GApe* Instance();

        /**
            Save pointer to internal array e.g.

            @param  aName   Name used for registering pointer
            @param  aPtr    Pointer to be saved

            @return KErrNone, if successful. KErrAlreadyExists, if the pointer
                    is already registered. KErrNotFound, if the 'aName' is not
                    a valid name.
            @pre Pre-condition: Call in any context        
        */
        IMPORT_C static TInt SetPtr(const TDesC8& aName, TAny* const aPtr);

        /**
            Get pointer from internal array e.g.

            @param  aName   Name of the registered pointer

            @return Pointer to requested item. May also return NULL, which
                    indicates that the pointer is not registered or the name
                    is not valid.
            @pre Pre-condition: Call in any context          
        */
        IMPORT_C static TAny* GetPtr(const TDesC8& aName);

    private:
        /**
            Defined as a private to prevent clients to create own instances
            from this class.
        */
        GApe();

        /**
            Defined as a private to prevent clients to delete the instance of
            this class.
        */
        ~GApe();

    private:
        /** Array where the registered pointers are stored */
        TAny* iPtrArray[ KPtrArraySize ];

        /** Internal instance to allow static methods to access instance
            data. */
        static GApe* GApePtr;
    };

// Global Function Prototypes

// Inline Functions

// Namespace

#endif // __GAPE_H__

// End of File
