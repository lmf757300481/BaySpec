// MyDllTesterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyDllTester.h"
#include "MyDllTesterDlg.h"
#include "iostream"
#include "fstream"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDllTesterDlg dialog

CMyDllTesterDlg::CMyDllTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDllTesterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDllTesterDlg)
	m_dwIntegrationTime  = 0;
	m_dwLineRate		 = 200;
	m_dwLineIndex		 = 0;
	m_dblNoiseThreshold  = 2000.0;
	m_nDeviceIndex		 = 0;
	m_bThresholdProfile  = FALSE;
	m_nExtTimingMode	 = 2;
	m_nExtTriggeringMode = 1;
	m_byteGPIO = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDllTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDllTesterDlg)
	DDX_Control(pDX, IDC_COMBO_OP_SW, m_ctrlComboOpSwState);
	DDX_Control(pDX, IDC_COMBO_ACQUISITION_MODE, m_ctrlComboAcqMode);
	DDX_Control(pDX, IDC_LIST_DATA, m_ctrlListData);
	DDX_Text(pDX, IDC_EDIT_INTEGRATION_TIME, m_dwIntegrationTime);
	DDV_MinMaxDWord(pDX, m_dwIntegrationTime, 0, 38749999);
	DDX_Text(pDX, IDC_EDIT_LINE_RATE, m_dwLineRate);
	DDX_Text(pDX, IDC_EDIT_LINE_INDEX, m_dwLineIndex);
	DDX_Text(pDX, IDC_EDIT_NOISE_THRESHOLD, m_dblNoiseThreshold);
	DDX_Text(pDX, IDC_EDIT_DEVICE_INDEX, m_nDeviceIndex);
	DDX_Check(pDX, IDC_CHECK_THRESHOLD_PROFILE, m_bThresholdProfile);
	DDX_Radio(pDX, IDC_RADIO_EXT_TRIG_SYNCH, m_nExtTimingMode);
	DDX_Radio(pDX, IDC_RADIO_EXT_TRIG_LEVEL, m_nExtTriggeringMode);
	DDX_Text(pDX, IDC_EDIT_GPIO, m_byteGPIO);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDllTesterDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDllTesterDlg)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SET_TIME, OnButtonSetTime)
	ON_BN_CLICKED(IDC_BUTTON_GET_DEV_INFO, OnButtonGetDevInfo)
	ON_BN_CLICKED(IDC_BUTTON_GET_TEMP, OnButtonGetTemp)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_GET_WL, OnButtonGetWL)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_CALIB, OnButtonLoadCalib)
	ON_BN_CLICKED(IDC_BUTTON_GET_SPECTRUM, OnButtonGetSpectrum)
	ON_BN_CLICKED(IDC_BUTTON_START_RUN, OnButtonStartRun)
	ON_BN_CLICKED(IDC_BUTTON_STOP_RUN, OnButtonStopRun)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_GET_PEAK, OnButtonGetPeak)
	ON_BN_CLICKED(IDC_BUTTON_GET_CURRENT_SPECTRA, OnButtonGetCurrentSpectra)
	ON_BN_CLICKED(IDC_BUTTON_GET_INDEX_SPECTRA, OnButtonGetIndexSpectra)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_DEVICE, OnButtonSelectDevice)
	ON_BN_CLICKED(IDC_CHECK_THRESHOLD_PROFILE, OnCheckThresholdProfile)
	ON_BN_CLICKED(IDC_BUTTON_SET_OP_SW, OnButtonSetOpSw)
	ON_BN_CLICKED(IDC_BUTTON_SET_GPIO, OnButtonSetGPIO)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMyDllTesterDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT_DEVICE_INDEX, &CMyDllTesterDlg::OnEnChangeEditDeviceIndex)
	ON_EN_CHANGE(IDC_EDIT_INTEGRATION_TIME, &CMyDllTesterDlg::OnEnChangeEditIntegrationTime)
	ON_LBN_SELCHANGE(IDC_LIST_DATA, &CMyDllTesterDlg::OnLbnSelchangeListData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDllTesterDlg message handlers

BOOL CMyDllTesterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bDeviceOK			 = FALSE;
	m_bLoadCalib		 = FALSE;
	m_nPixelCount		 = 512;
	m_wProcessMode		 = 1;

	m_ctrlComboOpSwState.SetCurSel(0);
	m_ctrlComboAcqMode.SetCurSel(1);
	

	memset(m_pdblNoiseThresholdProfile, 0, 8 * PIXEL_COUNT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDllTesterDlg::OnButtonInit()  //初始化
{
	CString strMsg;

	m_bDeviceOK = DLL_Open_Device(); //打开设备

	
	if (!m_bDeviceOK)
	{
		MessageBox("Device Open Failed!");
		return;
	}

	m_ctrlListData.AddString("Open Device Successfully!");
	
	m_nDeviceCount = DLL_Get_Device_Count();//获得设备的数量

	strMsg.Format("Device Count: %d", m_nDeviceCount); 
	
	if (m_nDeviceCount == -1)
		m_ctrlListData.AddString("Get Device Count Failed!");
	else
		m_ctrlListData.AddString(strMsg);

	for (int i = m_nDeviceCount - 1; i >= 0; i--)
	{
		if (!DLL_Select_Device(i))
			m_ctrlListData.AddString("Select Device Failed!");
		else
		{
			m_nDeviceIndex = i;
			OnButtonGetDevInfo();
		}
	}

	for (int i = 0; i < PIXEL_COUNT; i++)
		m_pdblWL[i] = i;
}

void CMyDllTesterDlg::OnButtonSelectDevice() 
{
	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	UpdateData(TRUE);

	if (!DLL_Select_Device(m_nDeviceIndex))
		m_ctrlListData.AddString("Select Device Failed!");

	OnButtonGetDevInfo();	
}

void CMyDllTesterDlg::OnButtonGetSpectrum()  
{
	WORD	i;
	double	dblCaseTemp, pdblPwr[PIXEL_COUNT], pdblWL[PIXEL_COUNT];
	CString strTemp;

	memset(pdblPwr, 0, 8 * PIXEL_COUNT);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (DLL_Get_Spectra(pdblPwr, &dblCaseTemp))
	{
		strTemp.Format("Case Temperature: %.3f", dblCaseTemp);
		m_ctrlListData.AddString(strTemp);

		if (m_bLoadCalib)
		{
			m_ctrlListData.AddString("Wavelength, Intensity");

			if (!DLL_Get_Wavelength(dblCaseTemp, pdblWL))
			{
				m_ctrlListData.AddString("Calculate Wavelength Failed!");
				return;
			}

			for (i = 0; i < m_nPixelCount; i++)
			{
				strTemp.Format("%.3f,    %.0f", pdblWL[i],  pdblPwr[i]);
				m_ctrlListData.AddString(strTemp);
			}
		}
		else
		{
			m_ctrlListData.AddString("Pixel, Intensity");

			for (i = 0; i < m_nPixelCount; i++)
			{
				strTemp.Format("%03d,    %.0f", i,  pdblPwr[i]);
				m_ctrlListData.AddString(strTemp);
			}
		}
	}
	else
		m_ctrlListData.AddString("Get Spectrum Data Failed!");

}

void CMyDllTesterDlg::OnButtonClose() 
{
	DLL_Close_Device();

	m_ctrlListData.AddString("Device Closed!");

	m_bDeviceOK = FALSE;
}

void CMyDllTesterDlg::OnButtonSetTime() 
{
	WORD	wLineRate;
	DWORD	dwIntegrationTime;
	
	CString strTemp;

	UpdateData(TRUE);

	
	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (!DLL_Set_Integration_Time_Line_Rate(m_dwIntegrationTime, (WORD)m_dwLineRate))
	{
		m_ctrlListData.AddString("Set Integration Time and Line Rate Failed!");
		return;
	}

	Sleep(500);

	if (!DLL_Get_Integration_Time_Line_Rate(&dwIntegrationTime, &wLineRate))
	{
		m_ctrlListData.AddString("Get Integration Time and Line Rate Failed!");
		return;
	}


	strTemp.Format("Integration Time: %d us", dwIntegrationTime);
	m_ctrlListData.AddString(strTemp);
	
	strTemp.Format("Line Rate: %d Hz", wLineRate);
	m_ctrlListData.AddString(strTemp);

}

void CMyDllTesterDlg::OnButtonGetDevInfo() 
{
	char	szSN[64];
	DWORD	dwHW, dwFW, dwDLLVersion;
	CString strTemp;

	if (!m_bDeviceOK || !DLL_Is_Device_OK())
	{
		MessageBox("Device Not Opened!");
		return;
	}

	strTemp.Format("Device Index: %d", m_nDeviceIndex);
	m_ctrlListData.AddString(strTemp);

	if (DLL_Get_Device_SN(szSN))
	{
		strTemp.Format("S/N: %s", szSN);
		m_pstrSN[m_nDeviceIndex].Format("%s", szSN); 
		m_ctrlListData.AddString(strTemp);
	}
	else
		m_ctrlListData.AddString("Get Device SN Failed!");

	m_nPixelCount = DLL_Get_Pixel_Count();
	
	if (m_nPixelCount >=0)
	{
		strTemp.Format("Pixel Count: %d", m_nPixelCount);
		m_ctrlListData.AddString(strTemp);
	}
	else
		m_ctrlListData.AddString("Get Pixel Count Failed!");

	if (DLL_Get_HW_FW_REV(&dwHW, &dwFW))
	{
		strTemp.Format("HW Version: %08d", dwHW);
		m_ctrlListData.AddString(strTemp);

		strTemp.Format("FW Version: %08d", dwFW);
		m_ctrlListData.AddString(strTemp);
	}
	else
		m_ctrlListData.AddString("Get Device HW & FW Failed!");

	DLL_Get_DLL_Versions(&dwDLLVersion);

	strTemp.Format("DLL Version: %08d", dwDLLVersion);
	m_ctrlListData.AddString(strTemp);
}

void CMyDllTesterDlg::OnButtonGetTemp() 
{
	double  dblCaseTemp, dblSensorTemp;
	CString strTemp;

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (!DLL_Get_Temperature(&dblCaseTemp, &dblSensorTemp))
		m_ctrlListData.AddString("Get Temperature Failed!");	
	
	strTemp.Format("Case Temp: %.1fC", dblCaseTemp);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("Sensor Temp: %.1fC", dblSensorTemp);
	m_ctrlListData.AddString(strTemp);

}

void CMyDllTesterDlg::OnButtonClear() 
{
	m_ctrlListData.ResetContent();
/*
	// Speed test
	DWORD  i, pdwPeakInfo[PIXEL_COUNT / 2];
	double dblCaseTemp, pdblPwr[PIXEL_COUNT], pdblWL[PIXEL_COUNT];

	for (i = 0; i < PIXEL_COUNT; i++)
		pdblWL[i] = i;

	LARGE_INTEGER	lnTime;
	LARGE_INTEGER	lnFreq;

	QueryPerformanceFrequency(&lnFreq);	
	QueryPerformanceCounter(&lnTime);

	double dblStartSec = (double) (lnTime.QuadPart / (double) lnFreq.QuadPart);

	for (i = 0; i < 100; i++)
	{
		if (!DLL_Get_Spectra(pdblPwr, &dblCaseTemp))
		{
			MessageBox("Grab data failed!");
			return;
		}

		if (m_bLoadCalib)
		{
			if (!DLL_Get_Wavelenth(dblCaseTemp, pdblWL))
			{
				MessageBox("Calculate Wavelength Failed!");
				return;
			}
		}

		if (!DLL_Search_Peaks(m_nPixelCount, pdblWL, pdblPwr, 5000, pdwPeakInfo))
		{
			MessageBox("Search Peak Failed!");
			return;
		}
	}

	QueryPerformanceFrequency(&lnFreq);	
	QueryPerformanceCounter(&lnTime);

	double dblEndSec = (double) (lnTime.QuadPart / (double) lnFreq.QuadPart);

	CString strTemp;
	
	strTemp.Format("Test Grab Rate: %.1f Hz", 100.0 / (dblEndSec - dblStartSec));
	m_ctrlListData.AddString(strTemp);
*/
}

void CMyDllTesterDlg::OnButtonLoadCalib() 
{
	int		nErrorCode;
	char	szFilter[] = "Calibration Data File (*.dat)|*.dat|All Files (*.*)|*.*||";
	char	szCurDir[256], szCalibFilePath[256];
	CString strTemp;

	UpdateData(TRUE);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	GetCurrentDirectory(256, szCurDir);

	CFileDialog	dlgFile(TRUE, NULL, szCurDir, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);


	if (IDOK == dlgFile.DoModal())
		sprintf(szCalibFilePath, "%s", dlgFile.GetPathName());
	else
	{
		MessageBox("Invalid file path!");
		return;
	}

	nErrorCode = DLL_Load_Calibration_Data(m_nDeviceIndex, m_pstrSN[m_nDeviceIndex], szCalibFilePath);

	if (nErrorCode != 0)
	{
		strTemp.Format("Load Calib Data Failed! Error Code: %d", nErrorCode);
		m_ctrlListData.AddString(strTemp);
		return;
	}

	m_ctrlListData.AddString("Load Calibration Data Successfully");

	m_bLoadCalib = TRUE;
}

void CMyDllTesterDlg::OnButtonGetWL() 
{
	double  dblCaseTemp, dblSensorTemp;
	CString strTemp;

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (!m_bLoadCalib)
	{
		MessageBox("Calibration Data Not Loaded!");
		return;
	}

	if (!DLL_Get_Temperature(&dblCaseTemp, &dblSensorTemp))
		m_ctrlListData.AddString("Get Temperature Failed!");	


	if (!DLL_Get_Wavelength(dblCaseTemp, m_pdblWL)) //获取波长
	{
		m_ctrlListData.AddString("Calculate Wavelength Failed!");
		return;
	}

	m_ctrlListData.AddString("Pixel,  Wavelength(nm)");

	for (int i = 0; i < m_nPixelCount; i++)
	{
		strTemp.Format("%03d,   %.4f", i, m_pdblWL[i]);
		m_ctrlListData.AddString(strTemp);
	}
}

void CMyDllTesterDlg::OnButtonStartRun() 
{
	int		nErrorCode; 
	WORD	wPeakSearchMode;
	double	pdblBackground[PIXEL_COUNT];
	CString strTemp;

	UpdateData(TRUE);

	m_wProcessMode	= m_ctrlComboAcqMode.GetCurSel();
	wPeakSearchMode = (WORD)m_bThresholdProfile;
	
	if (m_nExtTimingMode == 1)
	{
		m_nExtTriggeringMode = 1;
		UpdateData(FALSE);
	}

	memset(pdblBackground, 0, 8 * PIXEL_COUNT);

	nErrorCode = DLL_Start_Constantly_Grab_Spectra(m_wProcessMode, 
												   wPeakSearchMode, 
												   m_nExtTimingMode, 
												   m_nExtTriggeringMode, 
												   pdblBackground, 
												   m_dblNoiseThreshold, 
												   m_pdblNoiseThresholdProfile);
	
	if (nErrorCode == 0)
		m_ctrlListData.AddString("Constant Acquisition Started!");
	else
	{
		strTemp.Format("Constant Acquisition Failed! Error Code: %d", nErrorCode);
		m_ctrlListData.AddString(strTemp);
	}
}																		   

void CMyDllTesterDlg::OnButtonStopRun() 
{
	DLL_Stop_Constantly_Grab_Spectra();

	m_ctrlListData.AddString("Constant Acquisition Stopped");
}

void CMyDllTesterDlg::OnButtonGetCurrentSpectra()
{
	int		nLineCount = 0;	
	DWORD	dwLineStamp, pdwPeakData[PIXEL_COUNT / 2];
	double	pdblRawData[PIXEL_COUNT];
	CString strTemp;

	memset(pdblRawData, 0, 8 * PIXEL_COUNT);
	memset(pdwPeakData, 0, 4 * PIXEL_COUNT / 2);

	nLineCount = DLL_Get_Last_Spectrum_Index();

	if (nLineCount < 0)
	{
		m_ctrlListData.AddString("Get Last Constant Acquired Spectra Line Number Failed");
		return;
	}

	strTemp.Format("Current spectrum line count: %d", nLineCount);
	m_ctrlListData.AddString(strTemp);

	if (!DLL_Get_Constantly_Grab_Spectra(nLineCount, &dwLineStamp, pdblRawData))
	{
		m_ctrlListData.AddString("Get Laast Constant Acquired Spectra Failed");
		return;
	}

	if (!DLL_Get_Constantly_Grab_Peaks(nLineCount, pdwPeakData))
	{
		m_ctrlListData.AddString("Get Last Constant Acquired Peaks Failed");
		return;
	}

	if (m_wProcessMode % 2 != 0)
		dwLineStamp = pdwPeakData[0];

	strTemp.Format("Last spectrum line Stamp: %d", dwLineStamp);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("First pixel power: %.3f", pdblRawData[0]);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("Peak number: %d", pdwPeakData[1]);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("First Peak Pixel/WL: %.4f", 0.001 * pdwPeakData[2]);
	m_ctrlListData.AddString(strTemp);
	strTemp.Format("First Peak Power: %.3f", 0.001 * pdwPeakData[129]);
	m_ctrlListData.AddString(strTemp);
}

void CMyDllTesterDlg::OnButtonGetIndexSpectra() 
{
	int		nLineCount = 0;
	DWORD	i, dwLineStamp, pdwPeakData[PIXEL_COUNT / 2];
	double	pdblRawData[PIXEL_COUNT];
	CString strTemp;

	memset(pdblRawData, 0, 8 * PIXEL_COUNT);
	memset(pdwPeakData, 0, 4 * PIXEL_COUNT / 2);

	UpdateData(TRUE);

	if (!DLL_Get_Constantly_Grab_Spectra(m_dwLineIndex, &dwLineStamp, pdblRawData))
	{
		m_ctrlListData.AddString("Get Current Constant Acquired Spectra Failed");
		return;
	}

	if (!DLL_Get_Constantly_Grab_Peaks(m_dwLineIndex, pdwPeakData))
	{
		m_ctrlListData.AddString("Get Current Constant Acquired Peaks Failed");
		return;
	}

	if (m_wProcessMode % 2 != 0)
		dwLineStamp = pdwPeakData[0];

	strTemp.Format("Spectrum line Stamp: %d", dwLineStamp);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("First pixel power: %.3f", pdblRawData[0]);
	m_ctrlListData.AddString(strTemp);	

	strTemp.Format("Peak number: %d", pdwPeakData[1]);
	m_ctrlListData.AddString(strTemp);

	m_ctrlListData.AddString("Peak#, Peak Pixel/WL, Peak Power");

	for (i = 0; i < pdwPeakData[1]; i++)
	{
		strTemp.Format("%d, %.4f, %.3f", i, 0.001 * pdwPeakData[2 + i], 0.001 * pdwPeakData[129 + i]);
		m_ctrlListData.AddString(strTemp);
	}	
}


void CMyDllTesterDlg::OnDestroy() 
{
	OnButtonClose();

	CDialog::OnDestroy();		
}

void CMyDllTesterDlg::OnButtonGetPeak() 
{
	WORD	wPeakSearchMode, pwPwr[PIXEL_COUNT];	
	DWORD	j, pdwPeakInfo[PIXEL_COUNT / 2];
	double	dblCaseTemp, pdblPwr[PIXEL_COUNT];
	CString strTemp;
	
	memset(pwPwr, 0, 2 * PIXEL_COUNT);
	memset(pdwPeakInfo, 0, 2 * PIXEL_COUNT);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (!DLL_Get_Spectra(pdblPwr, &dblCaseTemp)) //先读光谱才行
	{
		MessageBox("Get Spectrum Failed!");
		return;
	}

	UpdateData(TRUE);

	if (m_bThresholdProfile)
		wPeakSearchMode = 1;
	else
		wPeakSearchMode = 0;
	int count=5000*60;
	CString temp;
	int CountLine=m_ctrlListData.GetCount();
	
	
	CTime time=CTime::GetCurrentTime();//time.Format("%Y-%m-%d-%H-%M-%S");
	CString strFileName="moving";
	CString path= "Data\\"+strFileName+".txt";
	CFile file;
	
	file.Open(path, CFile::modeWrite|CFile::modeCreate|CFile::modeRead);
//	CString str="LiuFang";
	for(int i=0;i<count;i++)
	{
		m_ctrlListData.GetText(i,temp);//.GetItemData(1).Item.
		file.Write(temp,temp.GetLength());

		 //寻峰函数； 注意：因为参数m_pdblWL是成员函数，所以，必须初始化这个
		if (!DLL_Search_Peaks(wPeakSearchMode, m_nPixelCount, m_pdblWL, pdblPwr, m_dblNoiseThreshold, m_pdblNoiseThresholdProfile, pdwPeakInfo)) 
	{
		MessageBox("Search Peak Failed!");
		return;
	}

	strTemp.Format("Peak Count: %d", pdwPeakInfo[1]);
	m_ctrlListData.AddString(strTemp);
	file.Write(strTemp,strTemp.GetLength());
	strTemp="Peak#, Peak Pixel, Peak Power";
	file.Write(strTemp,strTemp.GetLength());

	for (j = 0; j < pdwPeakInfo[1]; j++)
	{
		strTemp.Format("%02d, %8.3f, %8.3f", j + 1, 0.001 * pdwPeakInfo[2 + j], 0.001 * pdwPeakInfo[129 + j]);
		file.Write(strTemp,strTemp.GetLength());
	}
		file.Write("\r\n",2);
	}
	
	file.Flush();
	file.Close();
	

	

}

void CMyDllTesterDlg::OnButtonSetOpSw()  
{
	int		nState;
	BOOL	bAutoSw;

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	UpdateData(TRUE);

	nState = m_ctrlComboOpSwState.GetCurSel();

	if (nState == -1)
	{
		MessageBox("No Channel Selected!");
		return;
	}

	if (nState == 4)
		bAutoSw = TRUE;
	else
		bAutoSw = FALSE;

	if (!DLL_Set_Optical_Switch(bAutoSw, nState + 1))
	{
		m_ctrlListData.AddString("Set Optical Switch Failed!");
	}
	else
	{
		m_ctrlListData.AddString("Set Optical Switch Successfully!");
	}	
}

void CMyDllTesterDlg::OnCheckThresholdProfile() 
{
	char	seps[] = " ,\t\n";
	char	*token;
	char	buf[512], szCurDir[256];
	char	szFilter[] = "Calibration Data File (*.csv)|*.csv|All Files (*.*)|*.*||";
	WORD	i, wPixelCount;
	CString strTemp, strFilePath;

	CStdioFile	fileThresholdProfile;

	UpdateData(TRUE);

	if (m_bThresholdProfile)
	{
		GetCurrentDirectory(256, szCurDir);

		CFileDialog	dlgFile(TRUE, NULL, szCurDir, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

		if (IDOK == dlgFile.DoModal())
			strFilePath = dlgFile.GetPathName();
		else
		{
			MessageBox("Invalid file path!");
			return;
		}

		if (!fileThresholdProfile.Open(strFilePath, CFile::modeRead, NULL))
		{
			strTemp.Format("Cann't open noise threshold file: %s", strFilePath);
			MessageBox(strTemp);
		}
				
		fileThresholdProfile.ReadString(buf, 512);

		token = strtok(buf, seps);
		token = strtok(NULL, seps);

		wPixelCount = atoi(token);

		fileThresholdProfile.ReadString(buf, 512);

		for (i = 0; i < wPixelCount; i++)
		{
			fileThresholdProfile.ReadString(buf, 512);

			token = strtok(buf, seps);
			token = strtok(NULL, seps);

			m_pdblNoiseThresholdProfile[i]   = atof(token);
		}

		fileThresholdProfile.Close();
	}
}

void CMyDllTesterDlg::OnButtonSetGPIO() 
{
	BYTE	byteGPIO;
	CString strData;

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	UpdateData(TRUE);

	if (!DLL_Set_GPIO_State(m_byteGPIO))
	{
		m_ctrlListData.AddString("Set GPIO Failed!");
	}
	else
	{
		m_ctrlListData.AddString("Set GPIO Successfully!");
	}
	
	if (!DLL_Get_GPIO_State(&byteGPIO))
	{
		m_ctrlListData.AddString("Get GPIO Failed!");
	}
	else
	{
		strData.Format("Get GPIO State: 0X%02X",byteGPIO);
		m_ctrlListData.AddString(strData);
	}
}


void CMyDllTesterDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	//File  *pFile=fopen();
	CString temp;
	int CountLine=m_ctrlListData.GetCount();
	
	
	CTime time=CTime::GetCurrentTime();
	CString strFileName=time.Format("%Y-%m-%d-%H-%M-%S");
	CString path= "Data\\"+strFileName+".txt";
	CFile file;
	
	file.Open(path, CFile::modeWrite|CFile::modeCreate|CFile::modeRead);
//	CString str="LiuFang";
	for(int i=0;i<CountLine;i++)
	{
		m_ctrlListData.GetText(i,temp);//.GetItemData(1).Item.
		file.Write(temp,temp.GetLength());
		file.Write("\r\n",2);
	}
	
	file.Flush();
	file.Close();
}


void CMyDllTesterDlg::OnEnChangeEditDeviceIndex()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMyDllTesterDlg::OnEnChangeEditIntegrationTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMyDllTesterDlg::OnLbnSelchangeListData()
{
	// TODO: 在此添加控件通知处理程序代码
}
