//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
/*!
\file
\brief   Definition of interface INodeMap
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_DEVICEINFO_H
#define SPINNAKER_GENAPI_DEVICEINFO_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "GCString.h"
#include "GCTypes.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{

		//*************************************************************
		// IDeviceInfo interface
		//*************************************************************

		/**
		\brief Interface to get information about the device (= nodemap)
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IDeviceInfo
		{
			//! Get the model name
			virtual GenICam::gcstring GetModelName() = 0;

			//! Get the vendor name
			virtual GenICam::gcstring GetVendorName() = 0;

			//! Get tool tip
			virtual GenICam::gcstring GetToolTip() = 0;

			//! Get the standard name space
			virtual GenICam::gcstring GetStandardNameSpace() = 0;

			//! Get the version of the DLL's GenApi implementation
			virtual void GetGenApiVersion(GenICam::Version_t &Version, uint16_t &Build) = 0;

			//! Get the schema version number
			virtual void GetSchemaVersion(GenICam::Version_t &Version) = 0;

			//! Get the version of the device description file
			virtual void GetDeviceVersion(GenICam::Version_t &Version) = 0;

			//! Get the Guid describing the product
			virtual GenICam::gcstring GetProductGuid() = 0;

			//! Get the Guid describing the product version
			virtual GenICam::gcstring GetVersionGuid() = 0;
		};
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IDEVICEINFO_H
