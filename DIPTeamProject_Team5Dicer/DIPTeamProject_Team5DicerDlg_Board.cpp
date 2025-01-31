﻿#include "pch.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DIPTeamProject_Team5DicerDlg_Board.h"
#include "DIPTeamProject_Team5DicerDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DIPTeamProject_Team5DicerDlg_Board, CDialogEx)

// 게임 진행 화면

DIPTeamProject_Team5DicerDlg_Board::DIPTeamProject_Team5DicerDlg_Board(CWnd* pParent)
	: CDialogEx(IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG1_BOARD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

DIPTeamProject_Team5DicerDlg_Board::~DIPTeamProject_Team5DicerDlg_Board()
{
}

void DIPTeamProject_Team5DicerDlg_Board::DoDataExchange(CDataExchange* pDX)
{
	// 각 버튼에 변수를 지정한다.
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
	DDX_Control(pDX, IDC_BUTTON3, button3);
}

// 버튼의 각 ID와 버튼 클릭 함수를 연결한다.
BEGIN_MESSAGE_MAP(DIPTeamProject_Team5DicerDlg_Board, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton3)
END_MESSAGE_MAP()

// 다이얼로그가 처음 생성될 때 실행된다.
BOOL DIPTeamProject_Team5DicerDlg_Board::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 보드 선택 창에서 보드 이미지 파일 이름 받아오고 보드 선택 창을 닫는다.
	CDIPTeamProjectTeam5DicerDlg* pDlg = (CDIPTeamProjectTeam5DicerDlg*)AfxGetMainWnd();
	boardFile = pDlg->getBoardName();
	pDlg->SendMessage(WM_CLOSE, 0, 0);

	// Roll Dice 버튼만 활성화한다.
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	// 버튼에 bitmap 이미지를 입힌다.
	button1.LoadBitmaps(IDB_BITMAP8, NULL, NULL, IDB_BITMAP10);
	button2.LoadBitmaps(IDB_BITMAP9, NULL, NULL, IDB_BITMAP11);
	button3.LoadBitmaps(IDB_BITMAP12, IDB_BITMAP13, NULL, NULL);

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void DIPTeamProject_Team5DicerDlg_Board::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();

		// 보드 이미지를 띄운다.
		m_matImg2 = imread(boardFile, -1);
		resize(m_matImg2, m_matImage2, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage2.cols, m_matImage2.rows);
		DrawBasicImage(IDC_PIC_VIEW2, m_matImage2);

		// 규칙 이미지를 띄운다.
		m_matImg3 = imread("imageAsset\\rules.jpg", -1);
		resize(m_matImg3, m_matImage3, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage3.cols, m_matImage3.rows);
		DrawBasicImage(IDC_PIC_VIEW3, m_matImage3);

		//gameInfo를 통해 board 이미지를 전달한다.
		gameInfo.SetBoardImage(m_matImage2);
		//gamePros에게 동일한 Distribution 객체를 전달한다.
		gamePros.setDistribution(gameInfo);
		DrawBoardCenterImage("imageAsset\\base_redTurn.jpg");
	}
}

HCURSOR DIPTeamProject_Team5DicerDlg_Board::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 'Roll Dice' 버튼 클릭 시
void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton1() {

	String fileName;
	int red, blue, green;
	int width, height;
	bool exitOuterLoop = false;

	while (true) {

		// 주사위 이미지 파일명을 받아온다.
		fileName = CurrentDiceTurn() + LoadDice();

		// 주사위 이미지를 띄운다.
		m_matImg1 = imread(fileName, -1);
		resize(m_matImg1, m_matImage1, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage1.cols, m_matImage1.rows);
		DrawBasicImage(IDC_PIC_VIEW1, m_matImage1);
		
		width = m_matImage1.cols;
		height = m_matImage1.rows;

		// 주사위 이미지 색상을 받아온다.
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				blue = m_matImage1.at<Vec3b>(r, c)[0];
				green = m_matImage1.at<Vec3b>(r, c)[1];
				red = m_matImage1.at<Vec3b>(r, c)[2];
				
				if ( red > 150 || blue > 150 || green > 150 ) {
					exitOuterLoop = true;
					break;
				}
			}

			if (exitOuterLoop == true)
				break;
		}

		// 색과 팀 순서가 일치하면 계속 진행
		if (red > 150 && gamePros.GetCurrentTurn() == 0)
			break;
		else if (blue > 150 && gamePros.GetCurrentTurn() == 1)
			break;
		else if (green > 150 && gamePros.GetCurrentTurn() == 2)
			break;
	}
	gamePros.setDiceImage(m_matImage1);

	// 주사위를 굴리면 Roll Dice 버튼은 비활성화, Move Marker 버튼은 활성화
	if (end == false) {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}

	// 게임이 끝나면 모든 버튼을 비활성화
	else {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
}

// GameProgress에서 받아온 순서 정보대로 주사위 이미지 파일명을 지정한다.
String DIPTeamProject_Team5DicerDlg_Board::CurrentDiceTurn() {

	String team;
	int turn = gamePros.GetCurrentTurn();

	switch (turn) {
	case 0:
		team = "imageAsset\\red_";
		break;
	case 1:
		team = "imageAsset\\blue_";
		break;
	case 2:
		team = "imageAsset\\green_";
		break;
	}

	return team;
}

// 난수 받아서 랜덤하게 주사위 숫자 정보를 결정한다. (주사위 이미지 파일명 지정)
String DIPTeamProject_Team5DicerDlg_Board::LoadDice() {

	srand(time(NULL));
	int randNum = rand() % 6;
	String imgName;

	switch (randNum) {
	case 0:
		imgName = "1.jpg";	break;
	case 1:
		imgName = "2.jpg";	break;
	case 2:
		imgName = "3.jpg";	break;
	case 3:
		imgName = "4.jpg";	break;
	case 4:
		imgName = "5.jpg";	break;
	case 5:
		imgName = "6.jpg";	break;
	}

	return imgName;
}

// mat 이미지 별로 BITMAPINFO 구조체를 생성한다.
void DIPTeamProject_Team5DicerDlg_Board::CreateBitmapInfo(int width, int height) {

	if (m_pBitmapInfo != NULL) {
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biWidth = width;
	m_pBitmapInfo->bmiHeader.biHeight = -height;
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = 24;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;
}

// 지정한 Picture control에 맞춰서 주사위와 보드 등의 이미지를 띄운다.
void DIPTeamProject_Team5DicerDlg_Board::DrawBasicImage(int id, Mat m_matImage) {

	CClientDC dc(GetDlgItem(id));
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR);

	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

// 'Move Marker' 버튼 클릭 시
void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2() {

	// 게임 말 움직이는 함수를 호출한다.
	UpdateBoard();

	// 말을 움직이면 Move Marker 버튼은 비활성화, Roll Dice 버튼은 활성화
	if (end == false) {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}

	// 게임이 끝나면 모든 버튼을 비활성화
	else {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
}

// 이미지를 원하는 크기로 resize한다.
Mat DIPTeamProject_Team5DicerDlg_Board::ResizeImage(int width, int heigth,string path) { 

	Mat m_matImageTemp;

	Mat targetImage = imread(path , -1);
	resize(targetImage, m_matImageTemp, Size(width, heigth), 0, 0, 1);

	return m_matImageTemp;
}

// 보드 중간에 이미지를 그려준다.
void DIPTeamProject_Team5DicerDlg_Board::DrawBoardCenterImage(string path) {
	int width = m_matImage2.cols;
	int height = m_matImage2.rows;

	int cr = height / 2;
	int cc = width / 2;
	int bc = 0;
	int br = 0;

	// 띄울 이미지를 크기에 맞게 조절한다.
	Mat centerImage = ResizeImage(201, 161, path);

	// 보드 중간에 그려준다.
	for (int r = cr - 80; r <= cr + 80; r++) {
		bc = 0;
		for (int c = cc - 100; c <= cc + 100; c++) {
			m_matImage2.at<Vec3b>(r, c) = centerImage.at<Vec3b>(br, bc);
			bc++;
		}
		br++;
	}

	DrawBasicImage(IDC_PIC_VIEW2, m_matImage2);
}

// 현재 팀의 말 이미지 경로를 반환한다.
string DIPTeamProject_Team5DicerDlg_Board::GetMarkerPath(int turn) {
	switch (turn) {
	case 0:
		return "imageAsset\\r_marker.jpg";
	case 1:
		return "imageAsset\\b_marker.jpg";
	case 2:
		return "imageAsset\\g_marker.jpg";
	}
}

// winner에 해당하는 팀의 승리 이미지의 경로를 DrawBoardCenterImage로 전달한다. 
void DIPTeamProject_Team5DicerDlg_Board::ShowWinner(int turn) {
	string path;

	switch (turn) {
	case 0:
		path = "imageAsset\\base_redWins.jpg";
		break;
	case 1:
		path = "imageAsset\\base_blueWins.jpg";
		break;
	case 2:
		path = "imageAsset\\base_greenWins.jpg";
		break;
	}

	end = true;
	DrawBoardCenterImage(path);
}

// 잡힌 팀의 이미지의 경로를 DrawBoardCenterImage로 전달한다. 
void DIPTeamProject_Team5DicerDlg_Board::DrawCatchImage(int catchCase) {
	switch (catchCase) {
	case 0:
		DrawBoardCenterImage("imageAsset\\base_redDead.jpg");
		Sleep(1100);
		break;
	case 1:
		DrawBoardCenterImage("imageAsset\\base_blueDead.jpg");
		Sleep(1100);
		break;
	case 2:
		DrawBoardCenterImage("imageAsset\\base_greenDead.jpg");
		Sleep(1100);
		break;
	}
}

// 현재 차례 팀 이미지의 경로를 DrawBoardCenterImage로 전달한다. 
void DIPTeamProject_Team5DicerDlg_Board::DrawTurnImage(int turn) {
	switch (turn) {
	case 0:
		DrawBoardCenterImage("imageAsset\\base_redTurn.jpg");
		break;
	case 1:
		DrawBoardCenterImage("imageAsset\\base_blueTurn.jpg");
		break;
	case 2:
		DrawBoardCenterImage("imageAsset\\base_greenTurn.jpg");
	}
}

// board를 update(말 위치 이동, 잡기, 승리)를 하기 위한 각종 연산들을 수행한다.
void DIPTeamProject_Team5DicerDlg_Board::UpdateBoard() {

	int red, green, blue;

	int originalPos = gamePros.GetPosition();

	// 처음 position은 -1로 되어 있는데, 이를 0으로 바꿔준다.
	if (originalPos == -1) {
		originalPos = 0;
	}
	else {
		// 말이 처음 position에 있는 것이 아니라면, 원래 위치의 칸 색을 이전으로 되돌려 놓는다.
		for (int r = gameInfo.cells[originalPos].min.first; r <= gameInfo.cells[originalPos].max.first; r++) {
			for (int c = gameInfo.cells[originalPos].min.second; c <= gameInfo.cells[originalPos].max.second; c++) {
				m_matImage2.at<Vec3b>(r, c) = Vec3b(gameInfo.dark_color);
			}
		}
	}

	// 이동할 위치를 구한다.
	int newPos = gamePros.CalculatePosition(originalPos);

	// 이동해야할 위치가 0으로 구해진다면, 이겼음을 뜻한다.
	if (newPos == 0) {
		ShowWinner(gamePros.GetCurrentTurn());
		return;
	}

	// 칸마다 크기가 미세하게 달라서 칸 별로 칸에 맞는 말 이미지를 생성해야한다.
	int width = gameInfo.cells[newPos].max.second - gameInfo.cells[newPos].min.second +1;
	int height = gameInfo.cells[newPos].max.first - gameInfo.cells[newPos].min.first +1;
	Mat marker = ResizeImage(width, height, GetMarkerPath(gamePros.GetCurrentTurn()));

	// 이동해야하는 칸에 현재 팀의 말을 그려준다.
	int my = 0;
	int mx = 0;
	for (int r = gameInfo.cells[newPos].min.first; r <= gameInfo.cells[newPos].max.first; r++) {
		mx = 0;
		for (int c = gameInfo.cells[newPos].min.second; c <= gameInfo.cells[newPos].max.second; c++) {
			m_matImage2.at<Vec3b>(r, c) = marker.at<Vec3b>(my, mx);
			mx++;
		}
		my++;
	}

	// 계산 된 위치에 따라 말의 위치를 바꿔주고, 차례를 바꿔준다.
	gamePros.SetPosition(newPos);
	int next = gamePros.ChangeTurn(newPos);
	DrawCatchImage(gamePros.catchFlag);
	DrawTurnImage(next);

	// 다시 catchFlag를 -1로 만들어준다.
	gamePros.catchFlag = -1;

	DrawBasicImage(IDC_PIC_VIEW2, m_matImage2);
}

// 로고 버튼 클릭 시
void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton3() {

	// 개발자 목록 다이얼로그를 생성한다.
	DeveloperDlg dlg;
	dlg.DoModal();
}