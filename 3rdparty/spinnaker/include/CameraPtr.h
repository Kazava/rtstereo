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

#ifndef PGR_SPINNAKER_CAMERA_PTR_H
#define PGR_SPINNAKER_CAMERA_PTR_H

#include "SpinnakerPlatform.h"
#include "BasePtr.h"
#include "Camera.h"


namespace Spinnaker
{
	/**
	*  @defgroup SpinnakerClasses Spinnaker Classes
	*/

	/*@{*/

	/**
	*  @defgroup CameraPtr_h CameraPtr Class
	*/

	/*@{*/

    /**
    * @brief A reference tracked pointer to a camera object. 
    */

	class SPINNAKER_API CameraPtr : public BasePtr<Camera,CameraBase>
	{

	public:
		//! Default constructor.
		CameraPtr() throw()
			: BasePtr<Camera,CameraBase>()
		{
		}

		//! Default constructor.
		CameraPtr(const int /*nMustBeNull*/) throw()
			: BasePtr<Camera, CameraBase>()
		{
		}

        //! Virtual destructor.
		virtual ~CameraPtr(void){};

        //! Assignment operator.
		virtual CameraPtr& operator=(const int nMustBeNull){ return dynamic_cast<CameraPtr&>(BasePtr<Camera, CameraBase>::operator=(nMustBeNull)); };
		
	};
}

#endif //PGR_SPINNAKER_CAMERA_PTR_H