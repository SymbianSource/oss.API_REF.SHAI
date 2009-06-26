/*
  asicinfo_chipset_api.h

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
@brief ASIC info Chipset API H

@publishedDeviceAbstraction
*/

#ifndef __ASICINFO_CHIPSET_API_H__
#define __ASICINFO_CHIPSET_API_H__


// Include files
#include <kern_priv.h>

// Class declaration

/**
@brief ASIC information class

Delivers ASIC related informations to clients
*/
class AsicInfo
    {
    public:
        /**
        returns the ASIC version
       
        the return value is MMmmxxyy where
        MM------ is the major version
        --mm---- is the minor version
        ----xx-- is the major revision
        ------yy is the minor revision
        */
        IMPORT_C static TUint GetAsicVersion();
    };




#endif // __ASICINFO_CHIPSET_API_H__
