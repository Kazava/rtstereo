//=============================================================================
// Copyright � 2016 Point Grey Research, Inc. All Rights Reserved.
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
/*!
\file
\brief   Definition of template CPointer
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_POINTER_H
#define SPINNAKER_GENAPI_POINTER_H

#include "Base.h"
#include "INode.h"
#include "IValue.h"
#include "ICategory.h"
#include "IInteger.h"
#include "IFloat.h"
#include "IRegister.h"
#include "IEnumeration.h"
#include "IEnumEntry.h"
#include "IBoolean.h"
#include "IPort.h"
#include "IPortRecorder.h"
#include "IPortConstruct.h"
#include "IChunkPort.h"
#include "IString.h"
#include "INodeMap.h"
#include "INodeMapDyn.h"
#include "IDestroy.h"
#include "IDeviceInfo.h"
#include "ISelector.h"
#include "ICommand.h"
#include "GCString.h"
#include "Exception.h"
#include <stdio.h>

// Windows-specific.
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
// Linux specific.
#else
// End of OS-specific code.
#endif


namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// CPointer class
		//*************************************************************

		/**
		\brief Encapsulates a GenApi pointer dealing with the dynamic_cast automatically
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		template <class T, class B = IBase>
        class CPointer
		{

		public:
		 //! Default constructor.
        CPointer(void) 
            : m_pT( NULL )
        {
        }

        //! Constructor from INode pointer type.
        CPointer( B *pB )
            : m_pT( dynamic_cast<T*>(pB) )
        {
        }

        virtual ~CPointer(void)
        {
        }

		//! Assign INode Pointer
        void operator=( B *pB )
        {
            m_pT = dynamic_cast<T*>(pB);
        }

		//! Dereferencing
        operator T*(void) const
        {
            if (NULL == m_pT)
			{
				throw Spinnaker::Exception(__LINE__, __FILE__, __FUNCTION__, __DATE__, __TIME__, "LogicalErrorException NULL pointer dereferenced", GENICAM_ERR_LOGICAL);
			}
            return m_pT;
        }

        //! Dereferencing
        T& operator*(void) const
        {
            if (NULL == m_pT)
            {
                throw Spinnaker::Exception(__LINE__, __FILE__, __FUNCTION__, __DATE__, __TIME__, "LogicalErrorException NULL pointer dereferenced", GENICAM_ERR_LOGICAL);
			}
            return *m_pT;
        }

        //! Dereferencing
        T& operator()(void) const
        {
            if (NULL == m_pT)
             {
                throw Spinnaker::Exception(__LINE__, __FILE__, __FUNCTION__, __DATE__, __TIME__, "LogicalErrorException NULL pointer dereferenced", GENICAM_ERR_LOGICAL);
			}
            return *m_pT;
        }

        //! Dereferencing
        T* operator->(void) const
        {
            if (NULL == m_pT)
            {
                throw Spinnaker::Exception(__LINE__, __FILE__, __FUNCTION__, __DATE__, __TIME__, "LogicalErrorException NULL pointer dereferenced", GENICAM_ERR_LOGICAL);
			}
            return m_pT;
        }

        //! true if the pointer is valid
        bool IsValid() const throw()
        {
            return m_pT != NULL;
        }

        //! true if the pointer is valid
        operator bool(void) const throw()
        {
            return m_pT != NULL;
        }

        //! pointer equal
        bool operator==(T* pT) const 
        {
            return m_pT == pT;
        }

        //! pointer equal
        bool operator==(const CPointer<T,B> &rT) const 
        {
            return m_pT == rT.m_pT;
        }

        //! pointer equal
        bool operator==(int nMustBeNull) const
        {
            if (0 != nMustBeNull)
            {
				throw Spinnaker::Exception(__LINE__, __FILE__, __FUNCTION__, __DATE__, __TIME__, "LogicalErrorException argument must be NULL", GENICAM_ERR_LOGICAL);
			}
            return NULL == m_pT;
        }


    protected:

        //! Underlying raw pointer.
        T* m_pT;
    };
	
	//*************************************************************
		// Smartpointer for all interface
		//*************************************************************

		//! \addtogroup Spinnaker_GenApi_PublicUtilities
		//! \{
		
		//! SmartPointer for IBase interface pointer
		typedef CPointer<IBase> CBasePtr;

		//! SmartPointer for INode interface pointer
		typedef  CPointer<INode, IBase> CNodePtr;

		//! SmartPointer for IValue interface pointer
		typedef CPointer<IValue> CValuePtr;

		//! SmartPointer for ICategory interface pointer
		typedef CPointer<ICategory> CCategoryPtr;

		//! SmartPointer for IBoolean interface pointer
		typedef CPointer<IBoolean> CBooleanPtr;

		//! SmartPointer for IInteger interface pointer
		typedef CPointer<IInteger> CIntegerPtr;

		//! SmartPointer for IString interface pointer
		typedef CPointer<IString> CStringPtr;

		//! SmartPointer for IRegister interface pointer
		typedef CPointer<IRegister> CRegisterPtr;

		//! SmartPointer for IEnumeration interface pointer
		typedef CPointer<IEnumeration> CEnumerationPtr;

		//! SmartPointer for IEnumEntry interface pointer
		typedef CPointer<IEnumEntry> CEnumEntryPtr;

		//! SmartPointer for IPort interface pointer
		typedef CPointer<IPort> CPortPtr;

		//! SmartPointer for IPortReplay interface pointer
		typedef CPointer<IPortReplay> CPortReplayPtr;

		//! SmartPointer for IPortRecorder interface pointer
		typedef CPointer<IPortRecorder> CPortRecorderPtr;

		//! SmartPointer for IPortWriteList interface pointer
		typedef CPointer<IPortWriteList, IPortWriteList> CPortWriteListPtr;

		//! SmartPointer for IChunkPort interface pointer
		typedef CPointer<IChunkPort> CChunkPortPtr;

		//! SmartPointer for INodeMap interface pointer
		typedef CPointer<INodeMap, INodeMap> CNodeMapPtr;

		//! SmartPointer for INodeMapDyn interface pointer
		typedef CPointer<INodeMapDyn, INodeMap> CNodeMapDynPtr;

		//! SmartPointer for IDeviceInfo interface pointer
		typedef CPointer<IDeviceInfo, INodeMap> CDeviceInfoPtr;

		//! SmartPointer for ISelector interface pointer
		typedef CPointer<ISelector> CSelectorPtr;

		//! SmartPointer for ICommand interface pointer
		typedef CPointer<ICommand> CCommandPtr;

		//! SmartPointer for IFloat interface pointer
        class CFloatPtr : public CPointer < IFloat, IBase >
		{
			public:
			  //! Default constructor.
			CFloatPtr() throw()
				: CPointer<IFloat, IBase>(  )
			{
			}
			
			 //! Constructor from IBase pointer type.
			CFloatPtr( IBase *pB )
				: CPointer<IFloat, IBase>( pB )
			{
			}

			//! Assign IBase Pointer
			void operator=( IBase *pB )
			{
				CPointer<IFloat, IBase>::operator =(pB);
			}

			//! gets the interface of an integer alias node.
			IInteger *GetIntAlias()
			{
				return dynamic_cast<IInteger*>(m_pT->GetNode()->GetCastAlias());
			}

			//! gets the interface of an enum alias node.
			IEnumeration *GetEnumAlias()
			{
				return dynamic_cast<IEnumeration*>(m_pT->GetNode()->GetCastAlias());
			}
		};

		//! \}

		//! \addtogroup Spinnaker_GenApi_PublicImpl
		//! \{

		//! SmartPointer for IPortConstruct interface pointer
		typedef CPointer<IPortConstruct> CPortConstructPtr;


		//! Returns the name of the main interface as string
		//! DEPRICATED, use IBase::GetPrincipalInterfaceType() instead
		inline GenICam::gcstring GetInterfaceName(IBase* pBase)
		{
#pragma warning (push) // icc -W4 complains: controlling expression is constant
#pragma warning (disable : 279)
			assert(pBase && "don't call this with a NULL pointer");
#pragma warning (pop)
			CNodePtr ptrNode(pBase);
			switch (ptrNode->GetPrincipalInterfaceType())
			{
			case intfIValue:
				return GenICam::gcstring("IValue");
			case intfIInteger:
				return GenICam::gcstring("IInteger");
			case intfIBoolean:
				return GenICam::gcstring("IBoolean");
			case intfICommand:
				return GenICam::gcstring("ICommand");
			case intfIFloat:
				return GenICam::gcstring("IFloat");
			case intfIString:
				return GenICam::gcstring("IString");
			case intfIRegister:
				return GenICam::gcstring("IRegister");
			case intfICategory:
				return GenICam::gcstring("ICategory");
			case intfIEnumeration:
				return GenICam::gcstring("IEnumeration");
			case intfIEnumEntry:
				return GenICam::gcstring("IEnumEntry");
			case intfIPort:
				return GenICam::gcstring("IPort");
			case intfIBase:
			default:
				return GenICam::gcstring("IBase");
			}
		}

		//! Checks if a node is readable
		template <class T, class B>
		inline bool IsReadable(const Spinnaker::GenApi::CPointer<T, B>& ptr)
		{
			return ptr.IsValid() && IsReadable(ptr->GetAccessMode());
		}

		//! Checks if a node is Writable
		template <class T, class B>
		inline bool IsWritable(const Spinnaker::GenApi::CPointer<T, B>& ptr)
		{
			return ptr.IsValid() && IsWritable(ptr->GetAccessMode());
		}

		//! Checks if a node is Implemented
		template <class T, class B>
		inline bool IsImplemented(const Spinnaker::GenApi::CPointer<T, B>& ptr)
		{
			return ptr.IsValid() && IsImplemented(ptr->GetAccessMode());
		}

		//! Checks if a node is Available
		template <class T, class B>
		inline bool IsAvailable(const Spinnaker::GenApi::CPointer<T, B>& ptr)
		{
			return ptr.IsValid() && IsAvailable(ptr->GetAccessMode());
		}


		//! \}


	}
}

#endif // ifndef SPINNAKER_GENAPI_POINTER_H