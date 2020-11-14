#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

// CDIPTeamProjectTeam5DicerDlg 대화 상자
class CDIPTeamProjectTeam5DicerDlg : public CDialogEx
{
// 생성입니다.
public:
	CDIPTeamProjectTeam5DicerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	Mat m_matImage, m_matImageTemp;
	BITMAPINFO* m_pBitmapInfo;
	int turn;

	void CreateBitmapInfo(int width, int height);
	void DrawImage(int id, Mat m_matImage);
	String LoadDice();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
