#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "DIPTeamProject_Team5DicerDlg_Board.h"

using namespace cv;
using namespace std;

class CDIPTeamProjectTeam5DicerDlg : public CDialogEx
{
public:
	CDIPTeamProjectTeam5DicerDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

private:
	String boardName;

public:
	String getBoardName();

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};