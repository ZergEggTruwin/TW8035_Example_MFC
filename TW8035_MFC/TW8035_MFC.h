
// TW8035_MFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTW8035_MFCApp:
// �� Ŭ������ ������ ���ؼ��� TW8035_MFC.cpp�� �����Ͻʽÿ�.
//

class CTW8035_MFCApp : public CWinApp
{
public:
	CTW8035_MFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTW8035_MFCApp theApp;