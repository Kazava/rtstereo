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
/**
\file
\brief    Declaration of the CChunkPort class.
\ingroup  Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_CHUNKPORT_H
#define SPINNAKER_GENAPI_CHUNKPORT_H

#include "Types.h"
#include "INodeMap.h"
#include "IPortConstruct.h"
#include "Pointer.h"

#pragma warning(push)
#pragma warning(disable: 4251) // GenApi::CChunkPort::m_ptrPort' : class 'GenApi::CPointer<T>' needs to have dll-interface
#pragma warning ( disable : 4068 ) // unknown pragma; refers to BullsEyeCoverage

namespace Spinnaker
{
	namespace GenApi
	{

		class PortAdapter;

		/**
		\brief Port attachable to a chunk in a buffer
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		class SPINNAKER_API CChunkPort : public IPortConstruct
		{

		public:

			//! Constructor; can attach to a port
			CChunkPort(IPort* pPort = NULL);

			//! Destructor; detaches from the port
			~CChunkPort();

			//-------------------------------------------------------------
			// IPortConstruct implementation
			//-------------------------------------------------------------

			//! Get the access mode of the node
			virtual EAccessMode GetAccessMode() const;

			//! Get the type of the main interface of a node
			virtual EInterfaceType GetPrincipalInterfaceType() const;

			//! Reads a chunk of bytes from the port
			virtual void Read(void *pBuffer, int64_t Address, int64_t Length);

			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length);

			//! Called from the port node to give the chunk port a pointer to itself
			virtual void SetPortImpl(IPort* pPort);

			//! Determines if the port adapter must perform an endianness swap
#pragma BullseyeCoverage off
			virtual EYesNo GetSwapEndianess()
			{
				return No;
			}
#pragma BullseyeCoverage on

			//---------------------------------------------------------------
			// Implementation
			//---------------------------------------------------------------

			// Invalidates the chunk port node
			void InvalidateNode();

			//-------------------------------------------------------------
			// Initializing
			//-------------------------------------------------------------

			//! Attaches the ChunkPort to the Port
			bool AttachPort(::Spinnaker::GenApi::IPort* pPort);

			//! Detaches the ChunkPort to the Port
			void DetachPort();

			//! Attaches the Chunk to the ChunkPort
			void AttachChunk(uint8_t *pBaseAddress, int64_t ChunkOffset, int64_t Length, bool Cache);

			//! Detaches the Chunk from the ChunkPort
			void DetachChunk();

			//! Gets the ChunkID length
			int GetChunkIDLength();

			//! Checks if a ChunkID matches
			bool CheckChunkID(uint8_t* pChunkIDBuffer, int ChunkIDLength);

			//! Checks if a ChunkID matches, version using uint64_t ID representation
			bool CheckChunkID(uint64_t ChunkID);

			//! Updates the base address of the chunk
			void UpdateBuffer(uint8_t *pBaseAddress);

			//! Clears the chunk cache
			void ClearCache();

		protected:

			CNodePtr m_pPort;

			std::shared_ptr<PortAdapter> m_pPortAdapter;

			void* m_pChunkPort;
		};

	}
}

#pragma warning(pop)

#endif // SPINNAKER_GENAPI_CHUNKPORT_H
