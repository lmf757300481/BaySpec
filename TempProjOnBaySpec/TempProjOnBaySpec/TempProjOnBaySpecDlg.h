
// TempProjOnBaySpecDlg.h : ͷ�ļ�
//

#pragma once


#include "Sense2020Dll.h"

#define PIXEL_COUNT		512
#define DEVICE_COUNT	4	

// CTempProjOnBaySpecDlg �Ի���
class CTempProjOnBaySpecDlg : public CDialogEx
{
// ����
public:
	CTempProjOnBaySpecDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEMPPROJONBAYSPEC_DIALOG };
	
	//���ڽ�������õı���
	DWORD	m_dwIntegrationTime;
	DWORD	m_dwLineRate;
	DWORD	m_dwLineIndex;
	double	m_dblNoiseThreshold;
	int		m_nDeviceIndex;
	BOOL	m_bThresholdProfile;
	int		m_nExtTimingMode;
	int		m_nExtTriggeringMode;
	BYTE	m_byteGPIO;
	CString GetModuleDir() ;
	CString GetWorkDir();



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;


	//
	CListBox	m_ctrlListData;
	//���ڽ�������õĳ�Ա����
	int		m_nPixelCount;
	int		m_nDeviceCount;
	BOOL	m_bDeviceOK;
	BOOL	m_bLoadCalib;
	WORD	m_wProcessMode;
	double	m_pdblWL[PIXEL_COUNT];
	double	m_pdblNoiseThresholdProfile[PIXEL_COUNT];
	CString m_pstrSN[DEVICE_COUNT];

	double	temperature;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButInitialize();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeListData();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnButtonGetDevInfo();
	afx_msg void OnButtonLoadCalib();
	afx_msg void OnButtonInit() ;
	afx_msg void OnButtonSetTime() ;
	afx_msg void OnButtonGetWL();
	afx_msg void OnEnChangeEditIntegrationTime();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEditTemperature();

	afx_msg double getTemperature(double targetWL,double slope,double givenTemp, double givenWL);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedRadio1();
//	CButton m_Radio1;
	afx_msg void OnBnClickedRadio2();
	int m_Radio1;
	afx_msg void OnBnClickedButton7();
};
