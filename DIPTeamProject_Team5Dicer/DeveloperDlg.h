#pragma once

class DeveloperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeveloperDlg)

public:
	DeveloperDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DeveloperDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVELOPER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
