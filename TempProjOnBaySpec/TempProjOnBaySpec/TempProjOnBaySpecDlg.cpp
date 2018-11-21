
// TempProjOnBaySpecDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CTempProjOnBaySpecDlg �Ի���




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


	//��LISTControl������
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


// CTempProjOnBaySpecDlg ��Ϣ�������

BOOL CTempProjOnBaySpecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	m_bDeviceOK			 = FALSE;
	m_bLoadCalib		 = FALSE;
	m_nPixelCount		 = 512;
	m_wProcessMode		 = 1;

	memset(m_pdblNoiseThresholdProfile, 0, 8 * PIXEL_COUNT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTempProjOnBaySpecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTempProjOnBaySpecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTempProjOnBaySpecDlg::OnBnClickedButton1()  //��ʼ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnButtonInit() ;  //��ó�ʼ�� �����豸
	OnButtonSetTime() ;//�ӽ����϶�ȡ����ʱ���Ƶ�ʵĲ�������д���豸
	//m_bDeviceOK=true;  //���Ե�ʱ������
	OnButtonLoadCalib(); //����궨��Ϣ


}


void CTempProjOnBaySpecDlg::OnLbnSelchangeListData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTempProjOnBaySpecDlg::OnBnClickedButton2()  //�ر��豸
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DLL_Close_Device();

	m_ctrlListData.AddString("Device Closed!");

	m_bDeviceOK = FALSE;
}


void CTempProjOnBaySpecDlg::OnButtonGetDevInfo()  //��ȡ�豸��Ϣ
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


void CTempProjOnBaySpecDlg::OnButtonLoadCalib() // ���ر궨��Ϣ
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


void CTempProjOnBaySpecDlg::OnButtonInit()  //��ó�ʼ�� �����豸
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


void CTempProjOnBaySpecDlg::OnButtonSetTime()   //���û���ʱ��
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

	if (!DLL_Set_Integration_Time_Line_Rate(m_dwIntegrationTime, (WORD)m_dwLineRate)) //���û���ʱ��ĺ���������
	{
		m_ctrlListData.AddString("Set Integration Time and Line Rate Failed!");
		return;
	}

	Sleep(500);

	if (!DLL_Get_Integration_Time_Line_Rate(&dwIntegrationTime, &wLineRate))//����ʱ��ĺ���������Ƿ��ȡ��Ƶ�ʺͻ���ʱ��
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CTempProjOnBaySpecDlg::OnButtonGetWL()  //��ò���
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


void CTempProjOnBaySpecDlg::OnBnClickedButton4() // Ѱ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	strTemp.Format("�����񲨳��� �� %8.3f, %8.3f",braggWavelength,braggPower);
	m_ctrlListData.AddString(strTemp);

	temperature =getTemperature(braggWavelength,10.2, 39.7, 1543.418);//����ˮ����һ֧������   //double targetWL,double slope,double givenTemp, double givenWL   
	//double temperature = Demodulator.getTemperature(braggWavelength,10.6, 20.9, 1538.097);//���ǳ��õ�1538�Ĵ�����  20.9	1538.097


	strTemp.Format("��ǰ�¶��� �� %8.3f ��",temperature);
	m_ctrlListData.AddString(strTemp);

}


void CTempProjOnBaySpecDlg::OnBnClickedButton3()  //������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	WORD	i;
	double	dblCaseTemp, pdblPwr[PIXEL_COUNT], pdblWL[PIXEL_COUNT];
	CString strTemp;

	memset(pdblPwr, 0, 8 * PIXEL_COUNT);

	if (!m_bDeviceOK)
	{
		MessageBox("Device Not Opened!");
		return;
	}

	if (DLL_Get_Spectra(pdblPwr, &dblCaseTemp))//�����׺����� ����Ϊ����ǿ��ָ��  ��   ��ǰ�¶ȣ� û��ʹ�ó�Ա����
	{
		strTemp.Format("Case Temperature: %.3f", dblCaseTemp);   //���һ�µ�ǰ�¶�
		m_ctrlListData.AddString(strTemp);

		if (m_bLoadCalib) //�ж��ǲ����Ѿ������˱궨��Ϣ
		{
			m_ctrlListData.AddString("Wavelength, Intensity");

			if (!DLL_Get_Wavelength(dblCaseTemp, pdblWL)) //��ȡ��ǰ�Ĳ��� �� û��ʹ�ó�Ա����
			{
				m_ctrlListData.AddString("Calculate Wavelength Failed!");
				return;
			}

			for (i = 0; i < m_nPixelCount; i++) //������׺�ǿ��
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


void CTempProjOnBaySpecDlg::OnBnClickedButton5()  //����б�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlListData.ResetContent();
}


void CTempProjOnBaySpecDlg::OnEnChangeEditTemperature()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

double  CTempProjOnBaySpecDlg::getTemperature(double targetWL,double slope,double givenTemp, double givenWL)
{

	return (targetWL-givenWL)*1000.0/slope+givenTemp;

}


void CTempProjOnBaySpecDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	switch(m_Radio1){
	case 0://ѡ����ʱ������
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

			strTemp1.Format("�����·��Ϊ: %s", path);
			m_ctrlListData.AddString(strTemp1);
		}

		break;
	case 1://�Զ�������

		{
			CString strTemp2;
			
		

			BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
			CTime time=CTime::GetCurrentTime();
			CString strFileName=time.Format("%Y-%m-%d-%H-%M-%S");
			CString fileName= strFileName+".txt";
			CString defaultDir = GetWorkDir()+ "\\Data";	//Ĭ�ϴ򿪵��ļ�·��
			CString filter = "�ļ� (*.txt)|.txt||";	//�ļ����ǵ�����
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

			strTemp2.Format("�����·��Ϊ: %s", filePath);
			m_ctrlListData.AddString(strTemp2);

		}
		break;

	default:
		//������ʽ��ֵ�����ϵ�case�����ֵ��û��ƥ���ϣ���ô��ִ������Ĵ��롣
		break;
	}



}


void CTempProjOnBaySpecDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio1 = 0;    //��һ����ѡ��ť��ѡ��
}


void CTempProjOnBaySpecDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Radio1 = 1;    //�ڶ�����ѡ��ť��ѡ��
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

//��ȡ����·��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnButtonSetTime() ; //�ӽ����϶�ȡ����ʱ���Ƶ�ʵĲ�������д���豸
}
