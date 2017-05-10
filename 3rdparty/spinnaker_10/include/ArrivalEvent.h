//=============================================================================
// Copyright � 2015 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of 
// Point Grey Research, Inc. ("Confidential Information"). You shall not
// disclose such Confidential Information and shall use it only in 
// accordance with the terms of the "License Agreement" that you 
// entered into with PGR in connection with this software.
//
// UNLESS OTHERWISE SET OUT IN THE LICENSE AGREEMENT, THIS SOFTWARE IS 
// PROVIDED ON AN �AS-IS� BASIS AND POINT GREY RESEARCH INC. MAKES NO 
// REPRESENTATIONS OR WARRANTIES ABOUT THE SOFTWARE, EITHER EXPRESS 
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OR 
// CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR 
// NON-INFRINGEMENT. POINT GREY RESEARCH INC. SHALL NOT BE LIABLE FOR ANY 
// DAMAGES, INCLUDING BUT NOT LIMITED TO ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, PUNITIVE, OR CONSEQUENTIAL DAMAGES, OR ANY LOSS OF PROFITS, 
// REVENUE, DATA OR DATA USE, ARISING OUT OF OR IN CONNECTION WITH THIS 
// SOFTWARE OR OTHERWISE SUFFERED BY YOU AS A RESULT OF USING, MODIFYING 
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef PGR_SPINNAKER_ARRIVALEVENT_H
#define PGR_SPINNAKER_ARRIVALEVENT_H

#include "Event.h"
#include "SpinnakerPlatform.h"

namespace Spinnaker
{
	/**
	 *  @defgroup SpinnakerEventClasses Spinnaker Event Classes
	 */

	/*@{*/

	/**
	 *  @defgroup ArrivalEvent_h ArrivalEvent Class
	 */

	/*@{*/
	
	/**
	 * @brief An event handler for capturing the device arrival event.
	 */

	class SPINNAKER_API ArrivalEvent : public virtual Event
	{
	public:
		/**
		* Default constructor.
		*/
		ArrivalEvent();

		/**
		* Virtual destructor.
		*/
		virtual ~ArrivalEvent();

		/**
		* Callback to the device arrival event.		
		*/
		virtual void OnDeviceArrival() = 0;

	protected:
		/**
		* Copy constructor.
		*/
		ArrivalEvent( const ArrivalEvent& );

		/**
		* Assignment operator.
		*/
		ArrivalEvent& operator=( const ArrivalEvent& );
	};

	/*@}*/

	/*@}*/
}

#endif //PGR_SPINNAKER_ARRIVALEVENT_H