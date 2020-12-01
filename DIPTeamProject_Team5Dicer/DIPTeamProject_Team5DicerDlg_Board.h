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

using namespace cv;
using namespace std;

class DIPTeamProject_Team5DicerDlg_Board : public CDialogEx
{
	DECLARE_DYNAMIC(DIPTeamProject_Team5DicerDlg_Board)

public:
	DIPTeamProject_Team5DicerDlg_Board(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DIPTeamProject_Team5DicerDlg_Board();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG1_BOARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
<<<<<<< HEAD
	Mat m_matImg1, m_matImg2, m_matImg3, m_matImage1, m_matImage2, m_matImage3; // m_matImage1에는 주사위 그림, m_matImage2에는 보드 그림
=======
	vector<Cell> cells; // 보드 위의 각 cell의 위치 정보, 특수 칸 정보가 담겨 있음.
	vector<Cell> cellsTmp;
	Mat m_matImg1, m_matImg2, m_matImg3, m_matImg4, m_matImage1, m_matImage2, m_matImage3, m_matImage4; // m_matImage1에는 주사위 그림, m_matImage2에는 보드 그림
>>>>>>> 626f99151af3af4886750b806ec451aabb9c2646
	BITMAPINFO* m_pBitmapInfo;
	int imgSize = 400;
	String boardFile;

	int ccc = 0;

	void CreateBitmapInfo(int width, int height);
	void DrawImage(int id, Mat m_matImage);
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
	CMyBitmapButton button5;
};