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

struct cell {
	pair<int, int> min;
	pair<int, int> max;
	char info;
}typedef Cell;

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
	vector<Cell> cells; // 보드 위의 각 cell의 위치 정보, 특수 칸 정보가 담겨 있음.
	Mat m_matImg1, m_matImg2, m_matImage1, m_matImage2; // m_matImage1에는 주사위 그림, m_matImage2에는 보드 그림
	BITMAPINFO* m_pBitmapInfo;
	int imgSize = 400;
	String boardFile;
	Vec3b dark_color;
	//확인용변수
	int ccc = 0;

	void CreateBitmapInfo(int width, int height);
	void DrawImage(int id, Mat m_matImage);
	String CurrentDiceTurn();
	String LoadDice();
	int GetCurrentTurn();
	void ChangeTurn(int turn, int pos);
	Mat Binarization(Mat m_matImage);
	int RecognizeDiceNum(Mat m_matImage);
	int FindSpecialPosition(int pos);
	int CalculatePosition(int pos);
	int GetPosition(int turn);
	bool IsRedCatch(int pos);
	bool IsBlueCatch(int pos);
	bool IsGreenCatch(int pos);
	void DistributeCell(Mat m_matImage);
	void CreateMarker(int size);
	void ShowWinner(Mat m_matImage, int turn);
	Mat GetMarker(int turn);
	char BoardCellColor(int colornum);
	Mat ResizeMarker(int cellsize, Mat m_matImage);
	void UpdateBoard(Mat m_matImage);
private:
	int turn = 0; // turn은 현재 순서인 팀
	int redPos = -1, bluePos = -1, greenPos = -1;
	Mat redMarker, blueMarker, greenMarker;

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