
// TW8035_MFCDlg.cpp : 구현 파일
//


#include "stdafx.h"
#include "TW8035_MFC.h"
#include "TW8035_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <algorithm>
using namespace std;


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTW8035_MFCDlg 대화 상자



CTW8035_MFCDlg::CTW8035_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TW8035_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTW8035_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboPort);
	DDX_Control(pDX, IDC_EDIT1, m_editRecvCnt);
	DDX_Control(pDX, IDC_EDIT2, m_editFps);
	DDX_Control(pDX, IDC_EDIT4, m_editMax);
	DDX_Control(pDX, IDC_EDIT3, m_editMin);
}

BEGIN_MESSAGE_MAP(CTW8035_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTW8035_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTW8035_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTW8035_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTW8035_MFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTW8035_MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTW8035_MFCDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CTW8035_MFCDlg 메시지 처리기

BOOL CTW8035_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	makePortCombo(getTW8035PortList());
	drawColorBar();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTW8035_MFCDlg::drawColorBar()
{
	//b_drawColorbar = true;
	//UpdateData(false);
}

void CTW8035_MFCDlg::makePortCombo(CString str)
{
	CString Sep = _TEXT("|");
	int position = 0;

	CString Token;
	Token = str.Tokenize(Sep, position);

	m_comboPort.ResetContent();

	while (!Token.IsEmpty())
	{
		m_comboPort.AddString(Token);
		//m_comboPort2.AddString(Token);
		Token = str.Tokenize(Sep, position);
	}

	if (position != 0)
	{
		m_comboPort.SetCurSel(0);
		//m_comboPort2.SetCurSel(0);
	}
}

void CTW8035_MFCDlg::connect(UINT idx, CComboBox* targetCombo)
{
	CString portName;

	targetCombo->GetLBText(targetCombo->GetCurSel(), portName);

	if (serialPortConnect(this, portName))
	{
		targetCombo->EnableWindow(false);
	}
}

void CTW8035_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTW8035_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();	
		CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		if (b_drawColorbar == true)
		{
			int x = 450;
			int y = 80;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 255; j++)
				{
					dc.SetPixel(x + i, y + j, RGB(255 - j, 255 - j, 255 - j));
					
					cr[i] = RGB(255 - j, 255 - j, 255 - j);
				}
			}

			b_drawColorbar = false;
		}
		if (b_drawPic == true)
		{
			b_drawPic = false;
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTW8035_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTW8035_MFCDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (isConnected() == false)
	{
		connect(0, &m_comboPort);
	}
	else
	{
		requestStop();
		Sleep(300);
		serialPortClose(this);
	}
}


void CTW8035_MFCDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	requestRunStreamingMode();
}

void CTW8035_MFCDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	requestStop();
}

void CTW8035_MFCDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	changeFPSCmd(10);
}


void CTW8035_MFCDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	changeFPSCmd(20);
}


void CTW8035_MFCDlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	changeFPSCmd(30);
}

LRESULT CTW8035_MFCDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
	if (message == WM_COMM_RX_CNT) // ch 1
	{
	UINT recvCnt = wParam;
	CString string;
	string.Format(_T("%u"), recvCnt);
	((CStatic*)GetDlgItem(IDC_RECV_CNT))->SetWindowText(string);

	return CDialog::DefWindowProc(message, wParam, lParam);
	}
	*/
	if (message == WM_COMM_RX_DATA) // ch 1
	{
		//unsigned short* imageArr = (unsigned short*)wParam;
		TWImageData* twi = (TWImageData*)wParam;
		CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		int cnt = twi->cnt;
		int fps = twi->FPS;
		int width = twi->ImageWidth;
		int height = twi->ImageHeight;
		unsigned short imageArr[4800] = {};
		unsigned short t1 = twi->T_Data1;
		unsigned short t2 = twi->T_Data2;
		unsigned short t3 = twi->T_Data3;

		memcpy(imageArr, twi->ImageData, 9600);
		
		float tempArr[4800];

		// Temperature Data Array
		GenerateTempData(imageArr, tempArr, t1, t2, t3);

		drawTwi = twi;

		float perCode = 40 - 20;
		perCode = 255 / perCode;

		float minVal = *min_element(tempArr, tempArr + 4800);
		float maxVal = *max_element(tempArr, tempArr + 4800);

		CString str = _T("");;

		str.Format(_T("%d"), cnt);
		m_editRecvCnt.SetWindowTextW(str);

		str.Format(_T("%d"), fps);
		m_editFps.SetWindowTextW(str);
		
		str.Format(_T("%02.2f"), minVal);
		m_editMin.SetWindowTextW(str);

		str.Format(_T("%02.2f"), maxVal);
		m_editMax.SetWindowTextW(str);
				
		b_drawPic = true;

		UpdateData(false);
	}
	else if (message == WM_COMM_RECV_INFO)
	{
		TWDeviceInfo* tw = (TWDeviceInfo*)wParam;

		//m_staticDeviceType.SetWindowText(tw->DeviceType);
		//m_staticHWVer.SetWindowText(tw->DeviceHWVer);
		//m_staticSWVer.SetWindowText(tw->DeviceSWVer);
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CTW8035_MFCDlg::GenerateTempData(unsigned short* arr, float* dst, unsigned short t1, unsigned short t2, unsigned t3)
{
	float nSlope = 20.0f / (t2 - t1);

	for (int i = 0; i < 4800; i++)
	{
		dst[i] = (nSlope * (arr[i] - t1) + t3);
	}
}