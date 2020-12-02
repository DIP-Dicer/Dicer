#pragma once

class DeveloperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeveloperDlg)

public:
	DeveloperDlg(CWnd* pParent = nullptr);
	virtual ~DeveloperDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVELOPER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};
