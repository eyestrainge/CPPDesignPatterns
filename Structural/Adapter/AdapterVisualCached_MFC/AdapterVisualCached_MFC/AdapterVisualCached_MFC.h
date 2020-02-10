
// AdapterVisualCached_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAdapterVisualCachedMFCApp:
// See AdapterVisualCached_MFC.cpp for the implementation of this class
//

class CAdapterVisualCachedMFCApp : public CWinApp
{
public:
	CAdapterVisualCachedMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAdapterVisualCachedMFCApp theApp;
