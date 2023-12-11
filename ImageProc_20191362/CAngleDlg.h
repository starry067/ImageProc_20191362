#pragma once
#include "afxdialogex.h"


// CAngleDlg 대화 상자

class CAngleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAngleDlg)

public:
	CAngleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAngleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_DIALOG_ANGLEINPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int m_iAngle;
};
