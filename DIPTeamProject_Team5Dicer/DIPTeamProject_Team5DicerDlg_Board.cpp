// DIPTeamProject_Team5DicerDlg_Board.cpp: 구현 파일
//

#include "pch.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DIPTeamProject_Team5DicerDlg_Board.h"
#include "DIPTeamProject_Team5DicerDlg.h"
#include "afxdialogex.h"
#include <Windows.h>


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

		DistributeCell(m_matImage2);
		DrawBoardCenterImage(m_matImage2, "dice\\base_redTurn.jpg");
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
		if (red > 150 && GetCurrentTurn() == 0)
			break;
		else if (blue > 150 && GetCurrentTurn() == 1)
			break;
		else if (green > 150 && GetCurrentTurn() == 2)
			break;
	}
}


String DIPTeamProject_Team5DicerDlg_Board::CurrentDiceTurn() { // 순서 바꾸기 (red/blue/green 순서대로, 잡으면 한 번 더)

	// 대충 사진 로드 잘 되는지 보려고 짠거니까 순서 구현하는 사람이 므시께 잘 구현해쥬세용!
	// 이런식으로 파일 이름의 일부가 되는 string만 반환해주면 됩니다

	String team;

	int turn = GetCurrentTurn();

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

int DIPTeamProject_Team5DicerDlg_Board::GetCurrentTurn() {
	return turn;
}

void DIPTeamProject_Team5DicerDlg_Board::ChangeTurn(Mat m_matImage, int nowTurn, int pos) {
	switch (nowTurn) {
	case 0:
		redPos = pos;
		if (IsBlueCatch(m_matImage, pos) || IsGreenCatch(m_matImage, pos)) {
			DrawBoardCenterImage(m_matImage, "dice\\base_redTurn.jpg");
			turn = nowTurn;
		}
		else {
			turn++;
			DrawBoardCenterImage(m_matImage, "dice\\base_blueTurn.jpg");
		}
		break;
	case 1:
		bluePos = pos;
		if (IsRedCatch(m_matImage, pos) || IsGreenCatch(m_matImage, pos)) {
			turn = nowTurn;
			DrawBoardCenterImage(m_matImage, "dice\\base_blueTurn.jpg");
		}
		else {
			DrawBoardCenterImage(m_matImage, "dice\\base_greenTurn.jpg");
			turn++;
		}
		break;
	case 2:
		greenPos = pos;
		if (IsRedCatch(m_matImage, pos) || IsBlueCatch(m_matImage, pos)) {
			turn = nowTurn;
			DrawBoardCenterImage(m_matImage, "dice\\base_greenTurn.jpg");
		}
		else {
			DrawBoardCenterImage(m_matImage, "dice\\base_redTurn.jpg");
			turn = 0;
		}
	}
}

void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2() { // '말 이동하기' 버튼 클릭하면 말 움직이는 함수 호출
	UpdateBoard(m_matImage2);
}

// 여기도 안바꿈.
Mat DIPTeamProject_Team5DicerDlg_Board::Binarization(Mat m_matImage) { // 보드 이미지 이진화 시켜서 네모칸 식별하기 편하게

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int color, blue, green, red;
	Mat m_matImg = Mat::zeros(height, width, m_matImage.type());

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];
			color = (blue + green + red) / 3;

			if (color > 180)
				m_matImg.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
			else
				m_matImg.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}

	return m_matImg;
}

// 여기도 일단 안바꿈.
int DIPTeamProject_Team5DicerDlg_Board::RecognizeDiceNum(Mat m_matImage) { // 주사위 숫자 알아내기 (CalculatePosition 함수에서 호출됨)

	// 여기에서 팀 정보 알아내지 않고 주사위 눈 개수만 세면 되니까 binarization 된 이미지 사용하면 될 것 같아서 컬러변수 하나만 만들었어오 (0 아니면 255)
	int count = 0;
	int diceNum = 0;

	Mat filter;
	filter = imread("dice\\filter.jpg");
	int fw = filter.cols;
	int fh = filter.rows;
	Mat t_matImage;
	resize(m_matImage, t_matImage, Size(fw, fh), 0, 0, 1);
	t_matImage = Binarization(t_matImage);

	int width = t_matImage.cols;
	int height = t_matImage.rows;
	
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (t_matImage.at<Vec3b>(x, y)[0] == 0) {
				count = count + filter.at<Vec3b>(x, y)[0];
			}
		}
	}
	
	if (count < 1300)
		diceNum = 1;
	else if (count < 2000)
		diceNum = 4;
	else if (count < 2300)
		diceNum = 3;
	else if (count < 2400)
		diceNum = 5;
	else if (count < 2600)
		diceNum = 2;
	else
		diceNum = 6;
	
	return diceNum;
}

int DIPTeamProject_Team5DicerDlg_Board::FindSpecialPosition(int pos) {

	switch (cells[pos].info) {
	case 'g':
		for (int i = 1; i < cells.size()-1; i++) {
			if (cells[i].info == 'g' && i != pos) {
				pos = i + 1;
				break;
			}
		}
		return pos;
	case 'r':
		return pos += 2;
	case 'b':
		return pos -= 1;
	case 'y':
		for (int i = 1; i < cells.size()-1; i++) {
			if (cells[i].info == 'y' && i != pos) {
				pos = i + 1;
				break;
			}
		}
		return pos;
	}
}

int  DIPTeamProject_Team5DicerDlg_Board::CalculatePosition(int pos) { // 현재 위치와 주사위 숫자 이용해서 이동할 위치 계산 (UpdateBoard 함수에서 호출됨)

	//어차피 근데 RecognizeDiceNum에서 binarization 하는거 아닌가?
	int pips = RecognizeDiceNum(Binarization(m_matImage1)); // 주사위 눈 개수
//<<<<<<< HEAD
	int tmp = pos + pips;
//=======
//>>>>>>> ab655f322ae7cc7a76a59be74832f52c002a2634

	pos += pips;

	if (pos >= cells.size()) {
		return 0;
	}else if (cells[pos].info == 'd') {
		return pos;
	}else {
		return FindSpecialPosition(pos);
	}
}

void DIPTeamProject_Team5DicerDlg_Board::FindCellBound(int i, int j, Mat m_matImage) {

	int width = m_matImage.cols;
	int height = m_matImage.rows;

	int minR = i, minC = j, maxR = i, maxC = j;

	queue < pair<int, int>> q;
	visit[i][j] = cellNum;
	q.push(make_pair(i, j));

	while (!q.empty()) {
		int currentRow = q.front().first;
		int currentColumn = q.front().second;

		for (int k = 0; k < 4; k++) {
			int nextRow = currentRow + dy[k];
			int nextColumn = currentColumn + dx[k];

			
			if ((0 <= nextRow && nextRow < height) && (0 <= nextColumn && nextColumn < width)) {
				int blue = m_matImage.at<Vec3b>(nextRow, nextColumn)[0];
				int green = m_matImage.at<Vec3b>(nextRow, nextColumn)[1];
				int red = m_matImage.at<Vec3b>(nextRow, nextColumn)[2];

				if (((blue + green + red) / 3 <= 238) && visit[nextRow][nextColumn] == -1) {
					visit[nextRow][nextColumn] = cellNum;

					if (nextRow > maxR) {
						maxR = nextRow;
					}
					if (nextRow < minR) {
						minR = nextRow;
					}
					if (nextColumn > maxC) {
						maxC = nextColumn;
					}
					if (nextColumn < minC) {
						minC = nextColumn;
					}

					q.push(make_pair(nextRow, nextColumn));
				}
			}
		}
		q.pop();
	}

	if (maxC - minC > 10) {
		Cell tmp;
		tmp.max = make_pair(maxR, maxC);
		tmp.min = make_pair(minR, minC);
		//그냥 min이나 max값 이용하면 색상 식별이 이상하게 됨.
		tmp.info = BoardCellColor((maxR+minR)/2, (maxC+minC)/2, m_matImage);

		cells.push_back(tmp);
	}
}

char DIPTeamProject_Team5DicerDlg_Board::BoardCellColor(int r, int c, Mat m_matImage) {
	int blue = m_matImage.at<Vec3b>(r, c)[0];
	int green = m_matImage.at<Vec3b>(r, c)[1];
	int red = m_matImage.at<Vec3b>(r, c)[2];

	if ((blue + green + red) / 3 <= 70) // 검은칸
	{
		// 이거 매 반복문마다 호출됨 -> 나중에 수정해야 됨.
		dark_color = Vec3b(blue, green, red);

		return 'd';
	}
	else if (((blue + green + red) / 3 <= 100)) //초록색칸
	{
		return 'g';
	}
	else if (((blue + green + red) / 3 <= 140)) //빨간색칸
	{
		return 'r';
	}
	else if (((blue + green + red) / 3 <= 180)) //파란색칸
	{
		return 'b';
	}
	else if (((blue + green + red) / 3 <= 215)) //노란색칸
	{
		return 'y';
	}
	else if ( ((blue + green + red) / 3 <= 238)) //분홍색칸
	{
		return 'p';
	}
	else {
		return 'w';
	}
}

bool cmpFrist(const Cell& u, const Cell& v) {
	return u.min.first < v.min.first;
}

bool cmpSecond(const Cell& u, const Cell& v) {
	return u.min.second < v.min.second;
}

bool cmpThird(const Cell& u, const Cell& v) {
	return u.min.first > v.min.first;
}

bool cmpFourth(const Cell& u, const Cell& v) {
	return u.min.second > v.min.second;
}

void DIPTeamProject_Team5DicerDlg_Board::DistributeCell(Mat m_matImage) {
	int width = m_matImage.cols;
	int height = m_matImage.rows;

	for (int i = 0; i < height; i++) {
		vector<int> tmp(width, -1);
		visit.push_back(tmp);
	}

	for (int c = 0; c < width/8; c++) {
		for (int r = 0; r < height; r++) {

			int blue = m_matImage.at<Vec3b>(r, c)[0];
			int green = m_matImage.at<Vec3b>(r, c)[1];
			int red = m_matImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c, m_matImage);
			}
		}
		if (cellNum == 5) {
			break;
		}
	}

	sort(cells.begin(), cells.end(), cmpFrist);

	for (int r = cells[5].min.first; r < height; r++) {
		for (int c = 0; c < width; c++) {

			int blue = m_matImage.at<Vec3b>(r, c)[0];
			int green = m_matImage.at<Vec3b>(r, c)[1];
			int red = m_matImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c, m_matImage);
			}
		}
		if (cellNum == 12) {
			break;
		}
	}

	sort(cells.begin()+5, cells.end(), cmpSecond);

	for (int c = cells[12].min.second; c < width; c++) {
		for (int r = cells[12].min.first; r > 0; r--) {

			int blue = m_matImage.at<Vec3b>(r, c)[0];
			int green = m_matImage.at<Vec3b>(r, c)[1];
			int red = m_matImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c, m_matImage);
			}
		}
		if (cellNum == 17) {
			break;
		}
	}
	sort(cells.begin()+12, cells.end(), cmpThird);

	for (int r = cells[17].max.first; r > 0; r--) {
		for (int c = cells[17].min.second; c > 0; c--) {

			int blue = m_matImage.at<Vec3b>(r, c)[0];
			int green = m_matImage.at<Vec3b>(r, c)[1];
			int red = m_matImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c, m_matImage);
			}
		}
		if (cellNum == 23) {
			break;
		}
	}
	sort(cells.begin()+17, cells.end(), cmpFourth);
}

Mat DIPTeamProject_Team5DicerDlg_Board::ResizeImage(int width, int heigth,string path) { // 말 이미지 크기를 보드 칸의 크기로 resize (UpdateBoard 함수에서 사용)

	Mat m_matImageTemp;

	Mat markerImage = imread(path , -1);
	resize(markerImage, m_matImageTemp, Size(width, heigth), 0, 0, 1);

	return m_matImageTemp;
}

int DIPTeamProject_Team5DicerDlg_Board::GetPosition(int turn) {
	switch (turn) {
	case 0:
		return redPos;
	case 1:
		return bluePos;
	case 2:
		return greenPos;
	}
}

// 잡았을 때 무슨 말이 잡혔습니다! 이런거 나오면 좋을 듯.
bool DIPTeamProject_Team5DicerDlg_Board::IsRedCatch(Mat m_matImage, int pos) {
	if (redPos == pos) {
		DrawBoardCenterImage(m_matImage, "dice\\base_redDead.jpg");
		Sleep(1100);
		redPos = -1;
		return true;
	}
	return false;
}

bool DIPTeamProject_Team5DicerDlg_Board::IsBlueCatch(Mat m_matImage, int pos) {
	if (bluePos == pos) {
		DrawBoardCenterImage(m_matImage, "dice\\base_blueDead.jpg");
		Sleep(1100);
		bluePos = -1;
		return true;
	}
	return false;
}

bool DIPTeamProject_Team5DicerDlg_Board::IsGreenCatch(Mat m_matImage, int pos) {
	if (greenPos == pos) {
		DrawBoardCenterImage(m_matImage, "dice\\base_greenDead.jpg");
		Sleep(1100);
		greenPos = -1;
		return true;
	}
	return false;
}

void DIPTeamProject_Team5DicerDlg_Board::ShowWinner(Mat m_matImage, int turn) {
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

	DrawBoardCenterImage(m_matImage, path);
}

void DIPTeamProject_Team5DicerDlg_Board::DrawBoardCenterImage(Mat m_matImage, string path) {
	int width = m_matImage.cols;
	int height = m_matImage.rows;

	int cr = height / 2;
	int cc = width / 2;
	int bc = 0;
	int br = 0;

	Mat boardImage = ResizeImage(161, 121, path);

	for (int r = cr - 60; r <= cr + 60; r++) {
		bc = 0;
		for (int c = cc - 80; c <= cc + 80; c++) {
			m_matImage.at<Vec3b>(r, c) = boardImage.at<Vec3b>(br, bc);
			bc++;
		}
		br++;
	}

	DrawImage(IDC_PIC_VIEW2, m_matImage);
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

void DIPTeamProject_Team5DicerDlg_Board::UpdateBoard(Mat m_matImage) { // 이동할 위치를 받아와서 보드에 적용시킴 (Button2를 클릭하면 호출됨)

	int red, green, blue;

	int turn = GetCurrentTurn(); // 현재 순서인 팀 (말을 옮겨야 하는 팀)

	int originalPos = GetPosition(turn);

	// 시작점에서 출발하는거니까 일단 0으로
	if (originalPos == -1) {
		originalPos = 0;
	}
	else {
		// 원래 말 있던 곳 되돌림. 검은색으로
		for (int r = cells[originalPos].min.first; r <= cells[originalPos].max.first; r++) {
			for (int c = cells[originalPos].min.second; c <= cells[originalPos].max.second; c++) {
				m_matImage.at<Vec3b>(r, c) = Vec3b(dark_color);
			}
		}
	}

	int newPos = CalculatePosition(originalPos); // 이동할 위치 정보 가져옴

	if (newPos == 0) {
		// 게임 끝난거에 대한거 추가.
		ShowWinner(m_matImage, turn);
		return;
	}

	int width = cells[newPos].max.second - cells[newPos].min.second +1;
	int height = cells[newPos].max.first - cells[newPos].min.first +1;
	Mat marker = ResizeImage(width, height, GetMarkerPath(turn));

	int my = 0;
	int mx = 0;
	for (int r = cells[newPos].min.first; r <= cells[newPos].max.first; r++) {
		mx = 0;
		for (int c = cells[newPos].min.second; c <= cells[newPos].max.second; c++) {
			m_matImage.at<Vec3b>(r, c) = marker.at<Vec3b>(my, mx);
			mx++;
		}
		my++;
	}

	ChangeTurn(m_matImage, turn, newPos);

	// 소현아 제대로 칸 식별되는건지 확인하려면 1110~1117 부분 주석 해제해서 해봥
	/*for (int y = cells[ccc].min.first; y <= cells[ccc].max.first; y++) {
		for (int x = cells[ccc].min.second; x <= cells[ccc].max.second; x++) {
			m_matImage.at<Vec3b>(y, x) = Vec3b(255, 0, 0);
			//m_matImage.at<Vec3b>(x, y) = Vec3b(dark_color);
		}
	}

	ccc++;*/
	DrawImage(IDC_PIC_VIEW2, m_matImage);
}

// 반환값 도통 모르겠는 부분은 일단 void로 해놨어욥
// 엥? 이게 뭐야? 싶은 부분이 있우먄 당장 슬랙에다 서율아 멍청한 놈아~~~~~~!~!~! 이게 뭐야~~~~~~~!~! 외쳐주시길...........