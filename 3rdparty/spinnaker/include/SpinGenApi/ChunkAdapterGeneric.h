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
\brief    Declaration of the CChunkAdapterGeneric class.
\ingroup  Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H
#define SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H

#include "ChunkAdapter.h"
#include "GCString.h"

namespace Spinnaker
{
	namespace GenApi
	{
		/* ------------------------------------------- */
		// Single chunk info

		// make sure everything is properly packed
#pragma pack(push, 1)

		typedef struct SingleChunkData_t
		{
			uint64_t ChunkID;
			ptrdiff_t ChunkOffset;
			size_t ChunkLength;
		} SingleChunkData_t;

		// the extended version holding ChunkID as string should be used only in special cases
		// when the ChunkID does not fit into a 64-bit integer
		typedef struct SingleChunkDataStr_t
		{
			GenICam::gcstring ChunkID;
			ptrdiff_t ChunkOffset;
			size_t ChunkLength;
		} SingleChunkDataStr_t;

		// restore the previous packing
#pragma pack(pop)
		/* ------------------------------------------- */


		//! Connects a generic chunked buffer to a node map
		class SPINNAKER_API CChunkAdapterGeneric : public CChunkAdapter
		{

		public:
			//! Constructor
			
			CChunkAdapterGeneric(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

			//! Destructor
			virtual ~CChunkAdapterGeneric();

			// Does not have implementation, use the version with EventID
			virtual bool CheckBufferLayout(uint8_t *pBuffer, int64_t BufferLength);

			// Does not have implementation, use the generic version
			virtual void AttachBuffer(uint8_t *pBuffer, int64_t BufferLength, AttachStatistics_t *pAttachStatistics = NULL);

			virtual void AttachBuffer(uint8_t *pBuffer, SingleChunkData_t *ChunkData, int64_t NumChunks, AttachStatistics_t *pAttachStatistics = NULL);

			virtual void AttachBuffer(uint8_t *pBuffer, SingleChunkDataStr_t *ChunkData, int64_t NumChunks, AttachStatistics_t *pAttachStatistics = NULL);
		};
	}
}

#endif // SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H
