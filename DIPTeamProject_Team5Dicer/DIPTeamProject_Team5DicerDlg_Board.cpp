// DIPTeamProject_Team5DicerDlg_Board.cpp: 구현 파일
//

#include "pch.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DIPTeamProject_Team5DicerDlg_Board.h"
#include "DIPTeamProject_Team5DicerDlg.h"
#include "afxdialogex.h"

// DIPTeamProject_Team5DicerDlg_Board 대화 상자

IMPLEMENT_DYNAMIC(DIPTeamProject_Team5DicerDlg_Board, CDialogEx)

DIPTeamProject_Team5DicerDlg_Board::DIPTeamProject_Team5DicerDlg_Board(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG1_BOARD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

DIPTeamProject_Team5DicerDlg_Board::~DIPTeamProject_Team5DicerDlg_Board()
{
}

void DIPTeamProject_Team5DicerDlg_Board::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
}


BEGIN_MESSAGE_MAP(DIPTeamProject_Team5DicerDlg_Board, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL DIPTeamProject_Team5DicerDlg_Board::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CDIPTeamProjectTeam5DicerDlg* pDlg = (CDIPTeamProjectTeam5DicerDlg*)AfxGetMainWnd();
	boardFile = pDlg->getBoardName();
	pDlg->SendMessage(WM_CLOSE, 0, 0);

	button1.LoadBitmaps(IDB_BITMAP8, NULL, NULL, IDB_BITMAP10);
	button2.LoadBitmaps(IDB_BITMAP9, NULL, NULL, IDB_BITMAP11);

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

		m_matImg2 = imread(boardFile, -1);
		resize(m_matImg2, m_matImage2, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage2.cols, m_matImage2.rows);
		DrawImage(IDC_PIC_VIEW2, m_matImage2);

		m_matImg3 = imread("dice\\rules.jpg", -1);
		resize(m_matImg3, m_matImage3, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage3.cols, m_matImage3.rows);
		DrawImage(IDC_PIC_VIEW3, m_matImage3);

		gameInfo.SetBoardImage(m_matImage2);
		gamePros.setDistribution(gameInfo);
		DrawBoardCenterImage("dice\\base_redTurn.jpg");
	}
}

HCURSOR DIPTeamProject_Team5DicerDlg_Board::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton1() { // '주사위 굴리기' 버튼 클릭하면 red, blue, green 팀 순서대로 랜덤하게 주사위 이미지 띄움

	String fileName;
	int red, blue, green;
	int width, height;
	bool exitOuterLoop = false;

	while (true) { //현재 팀 값과 주사위 색깔이 같으면 반복문 탈출

		fileName = CurrentDiceTurn() + LoadDice();

		m_matImg1 = imread(fileName, -1);
		resize(m_matImg1, m_matImage1, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage1.cols, m_matImage1.rows);
		DrawImage(IDC_PIC_VIEW1, m_matImage1);
		
		width = m_matImage1.cols;
		height = m_matImage1.rows;

		// 여긴 일단 안건드림.
		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				blue = m_matImage1.at<Vec3b>(x, y)[0];
				green = m_matImage1.at<Vec3b>(x, y)[1];
				red = m_matImage1.at<Vec3b>(x, y)[2];

				blue; green; red;

				if (blue > 10 && blue < 200) {
					exitOuterLoop = true;
					break;
				}
			}

			if (exitOuterLoop == true)
				break;
		}

		// 현재 주사위 red (255, 80, 80) blue (78, 147, 210) green (102, 158, 64)
		// 새 주사위 red(255, 0, 0) blue (0, 0, 255), green (0, 255, 0)
		if (red > 150 && gamePros.GetCurrentTurn() == 0)
			break;
		else if (blue > 150 && gamePros.GetCurrentTurn() == 1)
			break;
		else if (green > 150 && gamePros.GetCurrentTurn() == 2)
			break;
	}
	gamePros.setDiceImage(m_matImage1);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


String DIPTeamProject_Team5DicerDlg_Board::CurrentDiceTurn() { // 순서 바꾸기 (red/blue/green 순서대로, 잡으면 한 번 더)

	// 대충 사진 로드 잘 되는지 보려고 짠거니까 순서 구현하는 사람이 므시께 잘 구현해쥬세용!
	// 이런식으로 파일 이름의 일부가 되는 string만 반환해주면 됩니다

	String team;

	int turn = gamePros.GetCurrentTurn();

	switch (turn) {
	case 0:
		team = "dice\\red_";
		break;
	case 1:
		team = "dice\\blue_";
		break;
	case 2:
		team = "dice\\green_";
		break;
	}

	return team;
}

String DIPTeamProject_Team5DicerDlg_Board::LoadDice() { // 난수 받아서 주사위 눈 1~6 결정

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

void DIPTeamProject_Team5DicerDlg_Board::CreateBitmapInfo(int width, int height) { // mat 이미지 별로 BITMAPINFO 구조체 생성

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

void DIPTeamProject_Team5DicerDlg_Board::DrawImage(int id, Mat m_matImage) { // 각 Picture control에 주사위와 보드 이미지 띄움

	CClientDC dc(GetDlgItem(id));
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR);

	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2() { // '말 이동하기' 버튼 클릭하면 말 움직이는 함수 호출
	UpdateBoard();

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
}

Mat DIPTeamProject_Team5DicerDlg_Board::ResizeImage(int width, int heigth,string path) { // 말 이미지 크기를 보드 칸의 크기로 resize (UpdateBoard 함수에서 사용)

	Mat m_matImageTemp;

	Mat targetImage = imread(path , -1);
	resize(targetImage, m_matImageTemp, Size(width, heigth), 0, 0, 1);

	return m_matImageTemp;
}

void DIPTeamProject_Team5DicerDlg_Board::DrawBoardCenterImage(string path) {
	int width = m_matImage2.cols;
	int height = m_matImage2.rows;

	int cr = height / 2;
	int cc = width / 2;
	int bc = 0;
	int br = 0;

	Mat centerImage = ResizeImage(161, 121, path);

	for (int r = cr - 60; r <= cr + 60; r++) {
		bc = 0;
		for (int c = cc - 80; c <= cc + 80; c++) {
			m_matImage2.at<Vec3b>(r, c) = centerImage.at<Vec3b>(br, bc);
			bc++;
		}
		br++;
	}

	DrawImage(IDC_PIC_VIEW2, m_matImage2);
}

string DIPTeamProject_Team5DicerDlg_Board::GetMarkerPath(int turn) {
	switch (turn) {
	case 0:
		return "dice\\r_marker.jpg";
	case 1:
		return "dice\\b_marker.jpg";
	case 2:
		return "dice\\g_marker.jpg";
	}
}

void DIPTeamProject_Team5DicerDlg_Board::ShowWinner(int turn) {
	string path;

	switch (turn) {
	case 0:
		path = "dice\\base_redWins.jpg";
		break;
	case 1:
		path = "dice\\base_blueWins.jpg";
		break;
	case 2:
		path = "dice\\base_greenWins.jpg";
		break;
	}

	DrawBoardCenterImage(path);
}

void DIPTeamProject_Team5DicerDlg_Board::DrawCatchImage(int catchCase) {
	switch (catchCase) {
	case 0:
		DrawBoardCenterImage("dice\\base_redDead.jpg");
		Sleep(1100);
		break;
	case 1:
		DrawBoardCenterImage("dice\\base_blueDead.jpg");
		Sleep(1100);
		break;
	case 2:
		DrawBoardCenterImage("dice\\base_greenDead.jpg");
		Sleep(1100);
		break;
	}
}

void DIPTeamProject_Team5DicerDlg_Board::DrawTurnImage(int turn) {
	switch (turn) {
	case 0:
		DrawBoardCenterImage("dice\\base_redTurn.jpg");
		break;
	case 1:
		DrawBoardCenterImage("dice\\base_blueTurn.jpg");
		break;
	case 2:
		DrawBoardCenterImage("dice\\base_greenTurn.jpg");
	}
}

void DIPTeamProject_Team5DicerDlg_Board::UpdateBoard() { // 이동할 위치를 받아와서 보드에 적용시킴 (Button2를 클릭하면 호출됨)

	int red, green, blue;

	int turn = gamePros.GetCurrentTurn(); // 현재 순서인 팀 (말을 옮겨야 하는 팀)

	int originalPos = gamePros.GetPosition(turn);

	// 시작점에서 출발하는거니까 일단 0으로
	if (originalPos == -1) {
		originalPos = 0;
	}
	else {
		// 원래 말 있던 곳 되돌림. 검은색으로
		for (int r = gameInfo.cells[originalPos].min.first; r <= gameInfo.cells[originalPos].max.first; r++) {
			for (int c = gameInfo.cells[originalPos].min.second; c <= gameInfo.cells[originalPos].max.second; c++) {
				m_matImage2.at<Vec3b>(r, c) = Vec3b(gameInfo.dark_color);
			}
		}
	}

	int newPos = gamePros.CalculatePosition(originalPos); // 이동할 위치 정보 가져옴

	if (newPos == 0) {
		ShowWinner(turn);
		return;
	}

	int width = gameInfo.cells[newPos].max.second - gameInfo.cells[newPos].min.second +1;
	int height = gameInfo.cells[newPos].max.first - gameInfo.cells[newPos].min.first +1;
	Mat marker = ResizeImage(width, height, GetMarkerPath(turn));

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

	int next = gamePros.ChangeTurn(turn, newPos);
	DrawCatchImage(gamePros.catchFlag);
	DrawTurnImage(next);

	gamePros.catchFlag = -1;

	/*for (int y = gameInfo.cells[ccc].min.second; y <= gameInfo.cells[ccc].max.second; y++) {
		for (int x = gameInfo.cells[ccc].min.first; x <= gameInfo.cells[ccc].max.first; x++) {
			m_matImage2.at<Vec3b>(x, y) = Vec3b(255, 0, 0);
			//m_matImage.at<Vec3b>(x, y) = Vec3b(dark_color);
		}
	}
	ccc++;*/

	DrawImage(IDC_PIC_VIEW2, m_matImage2);
}