// MyDllTester.h : main header file for the MYDLLTESTER application
//

#if !defined(AFX_MYDLLTESTER_H__52779975_BC68_4D83_BE52_9F04ABE23D25__INCLUDED_)
#define AFX_MYDLLTESTER_H__52779975_BC68_4D83_BE52_9F04ABE23D25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyDllTesterApp:
// See MyDllTester.cpp for the implementation of this class
//

class CMyDllTesterApp : public CWinApp
{
public:
	CMyDllTesterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDllTesterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyDllTesterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLLTESTER_H__52779975_BC68_4D83_BE52_9F04ABE23D25__INCLUDED_)
