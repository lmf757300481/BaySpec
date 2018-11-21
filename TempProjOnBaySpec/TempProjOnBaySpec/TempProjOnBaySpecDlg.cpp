
// TempProjOnBaySpecDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TempProjOnBaySpec.h"
#include "TempProjOnBaySpecDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "fstream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTempProjOnBaySpecDlg 对话框




CTempProjOnBaySpecDlg::CTempProjOnBaySpecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTempProjOnBaySpecDlg::IDD, pParent)
{

	m_dwIntegrationTime  = 0;
	m_dwLineRate		 = 200;
	m_dwLineIndex		 = 0;
	m_dblNoiseThreshold  = 2000.0;
	m_nDeviceIndex		 = 0;
	m_bThresholdProfile  = FALSE;
	m_nExtTimingMode	 = 2;
	m_nExtTriggeringMode = 1;
	m_byteGPIO = 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Radio1 = 0;
}

void CTempProjOnBaySpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	//绑定LISTControl的数据
	DDX_Control(pDX, IDC_LIST_DATA, m_ctrlListData);
	DDX_Text(pDX, IDC_EDIT_LINE_RATE, m_dwLineRate);
	DDX_Text(pDX, IDC_EDIT_INTEGRATION_TIME, m_dwIntegrationTime);
	DDV_MinMaxDWord(pDX, m_dwIntegrationTime, 0, 38749999);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE, temperature);
	//  DDX_Control(pDX, IDC_RADIO1, m_Radio1);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio1);
}

BEGIN_MESSAGE_MAP(CTempProjOnBaySpecDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON1, &CTempProjOnBaySpecDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST_DATA, &CTempProjOnBaySpecDlg::OnLbnSelchangeListData)
	ON_BN_CLICKED(IDC_BUTTON2, &CTempProjOnBaySpecDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT_INTEGRATION_TIME, &CTempProjOnBaySpecDlg::OnEnChangeEditIntegrationTime)
	ON_BN_CLICKED(IDC_BUTTON4, &CTempProjOnBaySpecDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTempProjOnBaySpecDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CTempProjOnBaySpecDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT_TEMPERATURE, &CTempProjOnBaySpecDlg::OnEnChangeEditTemperature)
	ON_BN_CLICKED(IDC_BUTTON6, &CTempProjOnBaySpecDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_RADIO1, &CTempProjOnBaySpecDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTempProjOnBaySpecDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON7, &CTempProjOnBaySpecDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CTempProjOnBaySpecDlg 消息处理程序

BOOL CTempProjOnBaySpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	m_bDeviceOK			 = FALSE;
	m_bLoadCalib		 = FALSE;
	m_nPixelCount		 = 512;
	m_wProcessMode		 = 1;

	memset(m_pdblNoiseThresholdProfile, 0, 8 * PIXEL_COUNT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTempProjOnBaySpecDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTempProjOnBaySpecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTempProjOnBaySpecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTempProjOnBaySpecDlg::OnBnClickedButton1()  //初始化
{
	// TODO: 在此添加控件通知处理程序代码
	OnButtonInit() ;  //获得初始化 ，打开设备
	OnButtonSetTime() ;//从界面上读取积分时间和频率的参数，并写入设备
	//m_bDeviceOK=true;  //测试的时候打开这个
	OnButtonLoadCalib(); //导入标定信息


}


void CTempProjOnBaySpecDlg::OnLbnSelchangeListData()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTempProjOnBaySpecDlg::OnBnClickedButton2()  //关闭设备
{
	// TODO: 在此添加控件通知处理程序代码
	DLL_Close_Device();

	m_ctrlListData.AddString("Device Closed!");

	m_bDeviceOK = FALSE;
}


void CTempProjOnBaySpecDlg::OnButtonGetDevInfo()  //获取设备信息
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


void CTempProjOnBaySpecDlg::OnButtonLoadCalib() // 加载标定信息
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


void CTempProjOnBaySpecDlg::OnButtonInit()  //获得初始化 ，打开设备
{
	CString strMsg;

	m_bDeviceOK = DLL_Open_Device();

	if (!m_bDeviceOK)
	{
		MessageBox("Device Open Failed!");
		return;
	}

	m_ctrlListData.AddString("Open Device Successfully!");

	m_nDeviceCount = DLL_Get_Device_Count();

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


void CTempProjOnBaySpecDlg::OnButtonSetTime()   //设置积分时间
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

	if (!DLL_Set_Integration_Time_Line_Rate(m_dwIntegrationTime, (WORD)m_dwLineRate)) //设置积分时间的函数，操作
	{
		m_ctrlListData.AddString("Set Integration Time and Line Rate Failed!");
		return;
	}

	Sleep(500);

	if (!DLL_Get_Integration_Time_Line_Rate(&dwIntegrationTime, &wLineRate))//积分时间的函数，检查是否读取了频率和积分时间
	{
		m_ctrlListData.AddString("Get Integration Time and Line Rate Failed!");
		return;
	}


	strTemp.Format("Integration Time: %d us", dwIntegrationTime);
	m_ctrlListData.AddString(strTemp);

	strTemp.Format("Line Rate: %d Hz", wLineRate);
	m_ctrlListData.AddString(strTemp);

}

void CTempProjOnBaySpecDlg::OnEnChangeEditIntegrationTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CTempProjOnBaySpecDlg::OnButtonGetWL()  //获得波长
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


	if (!DLL_Get_Wavelength(dblCaseTemp, m_pdblWL))
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


void CTempProjOnBaySpecDlg::OnBnClickedButton4() // 寻峰
{
	// TODO: 在此添加控件通知处理程序代码
	WORD	wPeakSearchMode, pwPwr[PIXEL_COUNT];	
	DWORD	j, pdwPeakInfo[PIXEL_COUNT / 2];
	double	dblCaseTemp, pdblPwr[PIXEL_COUNT];
	CString strTemp;

	DWORD braggWavelength=0, braggPower=0;

	memset(pwPwr, 0, 2 * PIXEL_COUNT);
	memset(pdwPeakInfo, 0, 2 * PIXEL_COUNT);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (!DLL_Get_Spectra(pdblPwr, &dblCaseTemp))
	{
		MessageBox("Get Spectrum Failed!");
		return;
	}

	UpdateData(TRUE);

	if (m_bThresholdProfile)
		wPeakSearchMode = 1;
	else
		wPeakSearchMode = 0;

	if (!DLL_Search_Peaks(wPeakSearchMode, m_nPixelCount, m_pdblWL, pdblPwr, m_dblNoiseThreshold, m_pdblNoiseThresholdProfile, pdwPeakInfo))
	{
		MessageBox("Search Peak Failed!");
		return;
	}



	strTemp.Format("Peak Count: %d", pdwPeakInfo[1]);
	m_ctrlListData.AddString(strTemp);

	m_ctrlListData.AddString("Peak#, Peak Pixel, Peak Power");

	for (j = 0; j < pdwPeakInfo[1]; j++)
	{
		if(0.001 * pdwPeakInfo[129 + j]>braggPower)
		{
			braggPower=0.001 * pdwPeakInfo[129 + j];
			braggWavelength=0.001 * pdwPeakInfo[2 + j];
		}

		strTemp.Format("%02d, %8.3f, %8.3f", j + 1, 0.001 * pdwPeakInfo[2 + j], 0.001 * pdwPeakInfo[129 + j]);
		m_ctrlListData.AddString(strTemp);
	}

	strTemp.Format("布拉格波长是 ： %8.3f, %8.3f",braggWavelength,braggPower);
	m_ctrlListData.AddString(strTemp);

	temperature =getTemperature(braggWavelength,10.2, 39.7, 1543.418);//这是水箱中一支传感器   //double targetWL,double slope,double givenTemp, double givenWL   
	//double temperature = Demodulator.getTemperature(braggWavelength,10.6, 20.9, 1538.097);//这是常用的1538的传感器  20.9	1538.097


	strTemp.Format("当前温度是 ： %8.3f ℃",temperature);
	m_ctrlListData.AddString(strTemp);

}


void CTempProjOnBaySpecDlg::OnBnClickedButton3()  //读光谱
{
	// TODO: 在此添加控件通知处理程序代码

	WORD	i;
	double	dblCaseTemp, pdblPwr[PIXEL_COUNT], pdblWL[PIXEL_COUNT];
	CString strTemp;

	memset(pdblPwr, 0, 8 * PIXEL_COUNT);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (DLL_Get_Spectra(pdblPwr, &dblCaseTemp))//读光谱函数： 输入为光谱强度指针  和   当前温度； 没有使用成员变量
	{
		strTemp.Format("Case Temperature: %.3f", dblCaseTemp);   //输出一下当前温度
		m_ctrlListData.AddString(strTemp);

		if (m_bLoadCalib) //判断是不是已经导入了标定信息
		{
			m_ctrlListData.AddString("Wavelength, Intensity");

			if (!DLL_Get_Wavelength(dblCaseTemp, pdblWL)) //读取当前的波长 ； 没有使用成员变量
			{
				m_ctrlListData.AddString("Calculate Wavelength Failed!");
				return;
			}

			for (i = 0; i < m_nPixelCount; i++) //输出光谱和强度
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


void CTempProjOnBaySpecDlg::OnBnClickedButton5()  //清除列表
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctrlListData.ResetContent();
}


void CTempProjOnBaySpecDlg::OnEnChangeEditTemperature()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

double  CTempProjOnBaySpecDlg::getTemperature(double targetWL,double slope,double givenTemp, double givenWL)
{

	return (targetWL-givenWL)*1000.0/slope+givenTemp;

}


void CTempProjOnBaySpecDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	switch(m_Radio1){
	case 0://选择了时间命名
		{
			CString strTemp1;
			


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

			strTemp1.Format("保存的路径为: %s", path);
			m_ctrlListData.AddString(strTemp1);
		}

		break;
	case 1://自定义命名

		{
			CString strTemp2;
			
		

			BOOL isOpen = FALSE;		//是否打开(否则为保存)
			CTime time=CTime::GetCurrentTime();
			CString strFileName=time.Format("%Y-%m-%d-%H-%M-%S");
			CString fileName= strFileName+".txt";
			CString defaultDir = GetWorkDir()+ "\\Data";	//默认打开的文件路径
			CString filter = "文件 (*.txt)|.txt||";	//文件过虑的类型
			CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
			openFileDlg.GetOFN().lpstrInitialDir =defaultDir+ "\\"+strFileName+".txt";
			INT_PTR result = openFileDlg.DoModal();
			CString filePath = defaultDir + "\\" + fileName;
			if(result == IDOK) {
				filePath = openFileDlg.GetPathName();
			}
	

			int CountLine=m_ctrlListData.GetCount();	
			CFile file;
			CString temp;

			file.Open(filePath, CFile::modeWrite|CFile::modeCreate|CFile::modeRead);
			//	CString str="LiuFang";
			for(int i=0;i<CountLine;i++)
			{
				m_ctrlListData.GetText(i,temp);//.GetItemData(1).Item.
				file.Write(temp,temp.GetLength());
				file.Write("\r\n",2);
			}

			file.Flush();
			file.Close();

			strTemp2.Format("保存的路径为: %s", filePath);
			m_ctrlListData.AddString(strTemp2);

		}
		break;

	default:
		//如果表达式的值和以上的case后面的值都没有匹配上，那么就执行这里的代码。
		break;
	}



}


void CTempProjOnBaySpecDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio1 = 0;    //第一个单选按钮被选中
}


void CTempProjOnBaySpecDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio1 = 1;    //第二个单选按钮被选中
}

CString CTempProjOnBaySpecDlg::GetModuleDir() 
{ 
 HMODULE module = GetModuleHandle(0); 
 char pFileName[MAX_PATH]; 
 GetModuleFileName(module, pFileName, MAX_PATH); 
 
 CString csFullPath(pFileName); 
 int nPos = csFullPath.ReverseFind( _T('\\') ); 
 if( nPos < 0 ) 
  return CString(""); 
 else 
  return csFullPath.Left( nPos ); 
}

//获取工作路径
CString  CTempProjOnBaySpecDlg::GetWorkDir() 
{  
 char pFileName[MAX_PATH]; 
 int nPos = GetCurrentDirectory( MAX_PATH, pFileName); 
 
 CString csFullPath(pFileName);  
 if( nPos < 0 ) 
  return CString(""); 
 else 
  return csFullPath; 
}


void CTempProjOnBaySpecDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	OnButtonSetTime() ; //从界面上读取积分时间和频率的参数，并写入设备
}
