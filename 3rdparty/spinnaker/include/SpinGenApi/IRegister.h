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
\brief    Definition of RegisterList_t type and the interface IRegister
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IREGISTER_H
#define SPINNAKER_GENAPI_IREGISTER_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IValue.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// IRegister interface
		//*************************************************************

		/**
		\brief Interface for registers
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IRegister : virtual public IValue
		{
			//! Set the register's contents
			/*!
			\param pBuffer The buffer containing the data to set
			\param Length The number of bytes in pBuffer
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void Set(const uint8_t *pBuffer, int64_t Length, bool Verify = true) = 0;

			//! Fills a buffer with the register's contents
			/*!
			\param pBuffer The buffer receiving the data to read
			\param Length The number of bytes to retrieve
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual void Get(uint8_t *pBuffer, int64_t Length, bool Verify = false, bool IgnoreCache = false) = 0;

			//! Retrieves the Length of the register [Bytes]
			virtual int64_t GetLength() = 0;

			//! Retrieves the Address of the register
			virtual int64_t GetAddress() = 0;
		};

	}
}
#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IREGISTER_H
