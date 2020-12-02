#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "MyBitmapButton.h"
#include "GameProgress.h"
#include "Distribution.h"
#include "DeveloperDlg.h"

using namespace cv;
using namespace std;

class DIPTeamProject_Team5DicerDlg_Board : public CDialogEx
{
	DECLARE_DYNAMIC(DIPTeamProject_Team5DicerDlg_Board)

public:
	DIPTeamProject_Team5DicerDlg_Board(CWnd* pParent = nullptr);
	virtual ~DIPTeamProject_Team5DicerDlg_Board();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG1_BOARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	// 각각 주사위 이미지, 보드 이미지, 규칙 이미지를 저장한다.
	Mat m_matImg1, m_matImg2, m_matImg3, m_matImage1, m_matImage2, m_matImage3;
	BITMAPINFO* m_pBitmapInfo;
	int imgSize = 400;
	String boardFile;

	bool end = false;
	int ccc = 0;

	void CreateBitmapInfo(int width, int height);
	void DrawBasicImage(int id, Mat m_matImage);
	String CurrentDiceTurn();
	String LoadDice();
	void DrawBoardCenterImage(string path);
	Mat ResizeImage(int width, int height, string path);
	string GetMarkerPath(int turn);
	void ShowWinner(int turn);
	void UpdateBoard();
	void DrawTurnImage(int turn);
	void DrawCatchImage(int turn);

private:
	// GameProgress, Distribution 클래스의 객체를 생성한다.
	GameProgress gamePros;
	Distribution gameInfo;

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
	CMyBitmapButton button1;
	CMyBitmapButton button2;
	CMyBitmapButton button3;
};