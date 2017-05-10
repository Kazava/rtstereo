//=============================================================================
// Copyright � 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
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
   
/* Auto-generated file. Do not modify. */
/* Generated Mon Feb 27 14:23:29 2017 */

#ifndef PGR_SPINNAKER_TRANSPORTLAYERINTERFACE_H
#define PGR_SPINNAKER_TRANSPORTLAYERINTERFACE_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "TransportLayerDefs.h"
#include <string>

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerQuickSpinClasses Spinnaker QuickSpin Classes
	*/
	/*@{*/

	/**
	* @defgroup TransportLayerInterface_h TransportLayerInterface Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerInterface
	{
	public:
		TransportLayerInterface(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerInterface();

	protected:
		TransportLayerInterface();

	private:
		TransportLayerInterface(const TransportLayerInterface&);
		TransportLayerInterface& operator=(const TransportLayerInterface&);
		TransportLayerInterface& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Transport layer Producer wide unique identifier of the selected interface.
		 * Visibility: Expert
		 */
		GenApi::IString &InterfaceID;

		/**
		 * Description: User readable name of the selected interface.
		 * Visibility: Expert
		 */
		GenApi::IString &InterfaceDisplayName;

		/**
		 * Description: Transport layer type of the interface.
		 * Visibility: Expert
		 */
		GenApi::IString &InterfaceType;

		/**
		 * Description: IP address of the selected gateway entry of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceGateway;

		/**
		 * Description: 48-bit MAC address of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceMACAddress;

		/**
		 * Description: IP address of the selected subnet of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceIPAddress;

		/**
		 * Description: Subnet mask of the selected subnet of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceSubnetMask;

		/**
		 * Description: Reports and controls the interface's power over Ethernet status.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<POEStatusEnum> &POEStatus;

		/**
		 * Description: Unlocks devices for internal use.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceUnlock;

		/**
		 * Description: Updates the internal device list.
		 * Visibility: Expert
		 */
		GenApi::ICommand &DeviceUpdateList;

		/**
		 * Description: Number of compatible devices detected on current interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceCount;

		/**
		 * Description: Selector for the different devices on this interface. This value only changes on execution of "DeviceUpdateList". The selector is 0-based in order to match the index of the C interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceSelector;

		/**
		 * Description: Interface wide unique identifier of the selected device. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceID;

		/**
		 * Description: Name of the device vendor. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceVendorName;

		/**
		 * Description: Name of the device model. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceModelName;

		/**
		 * Description: Gives the device's access status at the moment of the last execution of "DeviceUpdateList". This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceAccessStatusEnum> &DeviceAccessStatus;

		/**
		 * Description: Current IP address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceIPAddress;

		/**
		 * Description: Current subnet mask of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceSubnetMask;

		/**
		 * Description: 48-bit MAC address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceMACAddress;

		/**
		 * Description: Automatically forces any cameras on interface to an IP Address on the same subnet as the interface.
		 * Visibility: Expert
		 */
		GenApi::ICommand &AutoForceIP;

		/**
		 * Description: Number of incompatible devices detected on current interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleDeviceCount;

		/**
		 * Description: Selector for the devices that are not compatible with Spinnaker on this interface. This value only changes on execution of "DeviceUpdateList". The selector is 0-based in order to match the index of the C interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleDeviceSelector;

		/**
		 * Description: Interface wide unique identifier of the selected incompatible device. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceID;

		/**
		 * Description: Name of the incompatible device vendor. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceVendorName;

		/**
		 * Description: Name of the incompatible device model. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceModelName;


	protected:
		friend class Interface;
		friend class InterfaceInternal;

	};
	/*@}*/

	/*@}*/

}
#endif // PGR_SPINNAKER_TRANSPORTLAYERINTERFACE_H