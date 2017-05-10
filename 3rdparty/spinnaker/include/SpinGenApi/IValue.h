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
\brief   Definition of the interface IValue.
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IVALUE_H
#define SPINNAKER_GENAPI_IVALUE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "INode.h"
#include "GCString.h"
#include <memory>

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		interface INode;

		//*************************************************************
		// IValue interface
		//*************************************************************

		/**
		\brief Interface for value properties
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IValue : virtual public INode
		{
			//! Get the INode interface of the node
			virtual INode* GetNode() { return dynamic_cast<INode*>(this); }

			//! Get content of the node as string
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual GenICam::gcstring ToString(bool Verify = false, bool IgnoreCache = false) = 0;

			//! Set content of the node as string
			/*!
			\param ValueStr The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void FromString(const GenICam::gcstring& ValueStr, bool Verify = true) = 0;

			//! Checks if the value comes from cache or is requested from another node
			virtual bool IsValueCacheValid() const = 0;
		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IVALUE_H
