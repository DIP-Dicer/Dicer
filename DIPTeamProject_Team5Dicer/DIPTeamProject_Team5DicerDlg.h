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

class CDIPTeamProjectTeam5DicerDlg : public CDialogEx
{
public:
	CDIPTeamProjectTeam5DicerDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	Mat m_matImg1, m_matImg2, m_matImage1, m_matImage2; // m_matImage1에는 주사위 그림, m_matImage2에는 보드 그림
	BITMAPINFO* m_pBitmapInfo;
	int imgSize = 400, turn = 0; // turn은 현재 순서인 팀

	void CreateBitmapInfo(int width, int height);
	void DrawImage(int id, Mat m_matImage);
	String ChangeTurn();
	String LoadDice();
	int GetCurrentTurn();
	Mat Binarization(Mat m_matImage);
	int RecognizeDiceNum(Mat m_matImage);
	void CalculatePosition(Mat m_matImage);
	void DistributeCell(Mat m_matImage);
	Mat ResizeMarker(int cellsize, Mat m_matImage);
	void UpdateBoard(Mat m_matImage);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
