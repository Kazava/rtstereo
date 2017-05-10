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
\brief   Definition of ICommand interface
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_ICOMMAND_H
#define SPINNAKER_GENAPI_ICOMMAND_H

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
		// ICommand interface
		//*************************************************************

		//! Interface for command like  properties
		//! \ingroup Spinnaker_GenApi_PublicInterface
		interface SPINNAKER_API_ABSTRACT ICommand : virtual public IValue
		{
		public:

			//! Execute the command
			/*!
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void Execute(bool Verify = true) = 0;

			//! Execute the command
			virtual void operator()() = 0;

			//! Query whether the command is executed
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\return True if the Execute command has finished; false otherwise
			*/
			virtual bool IsDone(bool Verify = true) = 0;


		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_ICOMMAND_H
