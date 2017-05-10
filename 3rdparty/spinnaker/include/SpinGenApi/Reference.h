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
\brief    Definition of IReference and IEnumReference
\ingroup Spinnaker_GenApi_PublicImpl
*/

#ifndef SPINNAKER_GENAPI_REFERENCE_H
#define SPINNAKER_GENAPI_REFERENCE_H

#include "Types.h"
#include "SpinnakerPlatform.h"
#include "GCString.h"

namespace Spinnaker
{
	namespace GenApi
	{
		interface IBase;

		//*************************************************************
		// IReference interface
		//*************************************************************

		/**
		\brief Interface to construct a reference
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		interface SPINNAKER_API_ABSTRACT IReference
		{
			//! sets the implementation to a reference
			virtual void SetReference(INode* pBase) = 0;
		};

		//*************************************************************
		// IEnumReference interface
		//*************************************************************

		/**
		\brief Interface to construct an enum reference
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		interface SPINNAKER_API_ABSTRACT IEnumReference
		{
			//! sets the Enum value corresponding to a value
			virtual void SetEnumReference(int Index, GenICam::gcstring Name) = 0;

			//! sets the number of enum values
			virtual void SetNumEnums(int NumEnums) = 0;
		};

	}
}

#endif // ifndef SPINNAKER_GENAPI_REFERENCE_H
