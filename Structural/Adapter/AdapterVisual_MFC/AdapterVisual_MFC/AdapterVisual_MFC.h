
// AdapterVisual_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAdapterVisualMFCApp:
// See AdapterVisual_MFC.cpp for the implementation of this class
//

class CAdapterVisualMFCApp : public CWinApp
{
public:
	CAdapterVisualMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAdapterVisualMFCApp theApp;
