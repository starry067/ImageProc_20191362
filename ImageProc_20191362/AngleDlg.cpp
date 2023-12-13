// AngleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProc_20191362.h"
#include "afxdialogex.h"
#include "CAngleDlg.h"


// CAngleDlg 대화 상자

IMPLEMENT_DYNAMIC(CAngleDlg, CDialogEx)

CAngleDlg::CAngleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_DIALOG_ANGLEINPUT, pParent)
	, m_iAngle(0)
{

}

CAngleDlg::~CAngleDlg()
{
}

void CAngleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CAngleDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CAngleDlg 메시지 처리기
