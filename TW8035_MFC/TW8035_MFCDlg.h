
// TW8035_MFCDlg.h : ��� ����
//

#pragma once

#include "TW8035_API_DEF.h"
#include "afxwin.h"


// CTW8035_MFCDlg ��ȭ ����
class CTW8035_MFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTW8035_MFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TW8035_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	void makePortCombo(CString);
	void connect(UINT, CComboBox*);


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	void drawColorBar();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboPort;
	TWImageData* drawTwi;
	bool drawPicture = false;
	bool b_drawColorbar = false;
	bool b_drawPic = false;
	COLORREF cr[255];
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void GenerateTempData(unsigned short * arr, float * dst, unsigned short t1, unsigned short t2, unsigned t3);
	CEdit m_editRecvCnt;
	CEdit m_editFps;
	CEdit m_editMax;
	CEdit m_editMin;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
