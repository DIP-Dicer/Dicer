#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>

using namespace cv;
using namespace std;

// 민지 추가 - 소현이가 이용해야함.
struct cell {
	//cell을 구성하는 최소 x,y
	pair<int, int> min;
	//cell을 구성하는 최대 x,y
	pair<int, int> max;
	//cell정보(자료형 뭘로 할지 고민하다가 일단 char로 했는데 뭐 int 해도 되고..원하는걸로? 소현 결정하면 말 해주랏!)
	char info;
}typedef Cell; 

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
	vector<Cell> cells; // (민지추가) - 소현이가 이용해야함.
	Mat m_matImg1, m_matImg2, m_matImage1, m_matImage2; // m_matImage1에는 주사위 그림, m_matImage2에는 보드 그림
	BITMAPINFO* m_pBitmapInfo;
	int imgSize = 400;

	void CreateBitmapInfo(int width, int height);
	void DrawImage(int id, Mat m_matImage);
	String CurrentDiceTurn();
	String LoadDice();
	int GetCurrentTurn();
	void ChangeTurn(int turn, int pos);
	Mat Binarization(Mat m_matImage);
	int RecognizeDiceNum(Mat m_matImage);
	int CalculatePosition(int pos);
	int GetPosition(int turn);
	bool IsRedCatch(int pos);
	bool IsBlueCatch(int pos);
	bool IsGreenCatch(int pos);
	void DistributeCell(Mat m_matImage);
	char BoardCellColor(int colornum);
	Mat ResizeMarker(int cellsize, Mat m_matImage);
	void UpdateBoard(Mat m_matImage);
private:
	int turn = 0; // turn은 현재 순서인 팀
	int redPos = 0, bluePos = 0, greenPos = 0;

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
