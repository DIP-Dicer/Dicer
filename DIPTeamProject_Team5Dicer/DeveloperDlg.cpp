#include "pch.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DeveloperDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DeveloperDlg, CDialogEx)

// 개발자 목록 화면

DeveloperDlg::DeveloperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVELOPER, pParent)
{

}

DeveloperDlg::~DeveloperDlg()
{
}

void DeveloperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DeveloperDlg, CDialogEx)
END_MESSAGE_MAP()
