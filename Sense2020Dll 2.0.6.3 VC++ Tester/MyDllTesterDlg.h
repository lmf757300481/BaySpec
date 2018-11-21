// MyDllTesterDlg.h : header file
//

#if !defined(AFX_MYDLLTESTERDLG_H__5D731A6E_CBCB_4473_9EEA_9B3FE1AD11FB__INCLUDED_)
#define AFX_MYDLLTESTERDLG_H__5D731A6E_CBCB_4473_9EEA_9B3FE1AD11FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sense2020Dll.h"

#define PIXEL_COUNT		512
#define DEVICE_COUNT	4				


/////////////////////////////////////////////////////////////////////////////
// CMyDllTesterDlg dialog

class CMyDllTesterDlg : public CDialog
{
// Construction
public:
	CMyDllTesterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDllTesterDlg)
	enum { IDD = IDD_MYDLLTESTER_DIALOG };
	CComboBox	m_ctrlComboOpSwState;
	CComboBox	m_ctrlComboAcqMode;
	CListBox	m_ctrlListData;
	DWORD	m_dwIntegrationTime;
	DWORD	m_dwLineRate;
	DWORD	m_dwLineIndex;
	double	m_dblNoiseThreshold;
	int		m_nDeviceIndex;
	BOOL	m_bThresholdProfile;
	int		m_nExtTimingMode;
	int		m_nExtTriggeringMode;
	BYTE	m_byteGPIO;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDllTesterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	//ÐÙÑÀÀûÃüÃû·¨
	int		m_nPixelCount;
	int		m_nDeviceCount;
	BOOL	m_bDeviceOK;
	BOOL	m_bLoadCalib;
	WORD	m_wProcessMode;
	double	m_pdblWL[PIXEL_COUNT]; 
	double	m_pdblNoiseThresholdProfile[PIXEL_COUNT];
	CString m_pstrSN[DEVICE_COUNT];

	// Generated message map functions
	//{{AFX_MSG(CMyDllTesterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonInit();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonSetTime();
	afx_msg void OnButtonGetDevInfo();
	afx_msg void OnButtonGetTemp();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonGetWL();
	afx_msg void OnButtonLoadCalib();
	afx_msg void OnButtonGetSpectrum();
	afx_msg void OnButtonStartRun();
	afx_msg void OnButtonStopRun();
	afx_msg void OnDestroy();
	afx_msg void OnButtonGetPeak();
	afx_msg void OnButtonGetCurrentSpectra();
	afx_msg void OnButtonGetIndexSpectra();
	afx_msg void OnButtonSelectDevice();
	afx_msg void OnCheckThresholdProfile();
	afx_msg void OnButtonSetOpSw();
	afx_msg void OnButtonSetGPIO();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnEnChangeEditDeviceIndex();
	afx_msg void OnEnChangeEditIntegrationTime();
	afx_msg void OnLbnSelchangeListData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLLTESTERDLG_H__5D731A6E_CBCB_4473_9EEA_9B3FE1AD11FB__INCLUDED_)
