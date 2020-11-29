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

void DIPTeamProject_Team5DicerDlg_Board::ChangeTurn(int nowTurn, int pos) {
	switch (nowTurn) {
	case 0:
		if (IsBlueCatch(pos) || IsGreenCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn++;
		}
		break;
	case 1:
		if (IsRedCatch(pos) || IsGreenCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn++;
		}
		break;
	case 2:
		if (IsRedCatch(pos) || IsBlueCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn = 0;
		}
	}
}

void DIPTeamProject_Team5DicerDlg_Board::OnBnClickedButton2() { // '말 이동하기' 버튼 클릭하면 말 움직이는 함수 호출

	UpdateBoard(m_matImage2);
}

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

int DIPTeamProject_Team5DicerDlg_Board::RecognizeDiceNum(Mat m_matImage) { // 주사위 숫자 알아내기 (CalculatePosition 함수에서 호출됨)

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int color;
	// 여기에서 팀 정보 알아내지 않고 주사위 눈 개수만 세면 되니까 binarization 된 이미지 사용하면 될 것 같아서 컬러변수 하나만 만들었어오 (0 아니면 255)
	int diceNum = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			color = m_matImage.at<Vec3b>(x, y)[0];

			// 주사위 눈 개수 식별
		}
	}

	return diceNum;
}

int  DIPTeamProject_Team5DicerDlg_Board::CalculatePosition(int pos) { // 현재 위치와 주사위 숫자 이용해서 이동할 위치 계산 (UpdateBoard 함수에서 호출됨)

	int pips = RecognizeDiceNum(Binarization(m_matImage1)); // 주사위 눈 개수
	int tmp = pos + pips;

	// 특수 칸에 대한 계산도 추가적으로 해야함.(특수 칸 규칙 정해지면 할거임)

	return pos;
}

void DIPTeamProject_Team5DicerDlg_Board::DistributeCell(Mat m_matImage) { // 각 칸이 무슨 픽셀로 이루어져있는지 구분 (UpdateBoard 함수에서 사용)

	//int width = m_matImage.cols;
	//int height = m_matImage.rows;
	int red, green, blue;

	//민지 추가 - 소현아 여기에 셀 구분하는거 넣으면 되는데, header 파일에 보면 구조체있고, 그 구조체로 cells라는 변수 만들어놨거든.
	//그거 이용해서 일단 여기에 Cell tmp; 이렇게 임시 변수 만들고
	//tmp.min.first = 최소 x값 tmp.min.second = 최소 y값 이런식으로 최소/최대 x,y값 넣어주고
	//cells.push_back(tmp) 이렇게 해주면 돼!
	//구조체 내용 바꾸고 싶으면 바꿔도 됑 근데 그러면 내 부분도 바꿔야해서 말해주랏!!

	//소현: 구조체내용은 그대로 유지했고 칸 순서대로 cell에 넣어뒀어! info가 의미하는 값들은 BoardCellColor 함수에 설명해뒀습니다~~!!

	Mat cellImg = m_matImage.clone();
	int width = cellImg.cols;
	int height = cellImg.rows;
	//printf("height: %d | width: %d\n", height, width);
	int change[400] = { 0, };
	int change2[400] = { 0, };
	int change3[400] = { 0, };
	int change4[400] = { 0, };

	queue<int> changePos;
	bool start = false, end = false;
	int left, right, top, bottom;
	int index = 0;
	int firstrow[30] = { 0, };
	int secondrow[35] = { 0, };
	int thirdrow[25] = { 0, };
	int fourthrow[30] = { 0, };


	//픽셀값 정규화하는 for문
	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {
			blue = cellImg.at<Vec3b>(x, y)[0];
			green = cellImg.at<Vec3b>(x, y)[1];
			red = cellImg.at<Vec3b>(x, y)[2];

			if ((blue + green + red) / 3 <= 70) // 검은칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 70;
				cellImg.at<Vec3b>(x, y)[1] = 70;
				cellImg.at<Vec3b>(x, y)[2] = 70;
			}
			else if (((blue + green + red) / 3 > 70) && ((blue + green + red) / 3 <= 100)) //초록색칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 100;
				cellImg.at<Vec3b>(x, y)[1] = 100;
				cellImg.at<Vec3b>(x, y)[2] = 100;
			}
			else if (((blue + green + red) / 3 > 100) && ((blue + green + red) / 3 <= 140)) //빨간색칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 140;
				cellImg.at<Vec3b>(x, y)[1] = 140;
				cellImg.at<Vec3b>(x, y)[2] = 140;
			}
			else if (((blue + green + red) / 3 > 140) && ((blue + green + red) / 3 <= 180)) //파란색칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 180;
				cellImg.at<Vec3b>(x, y)[1] = 180;
				cellImg.at<Vec3b>(x, y)[2] = 180;
			}
			else if (((blue + green + red) / 3 > 180) && ((blue + green + red) / 3 <= 215)) //노란색칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 215;
				cellImg.at<Vec3b>(x, y)[1] = 215;
				cellImg.at<Vec3b>(x, y)[2] = 215;
			}
			else if (((blue + green + red) / 3 > 215) && ((blue + green + red) / 3 <= 238)) //분홍색칸
			{
				cellImg.at<Vec3b>(x, y)[0] = 238;
				cellImg.at<Vec3b>(x, y)[1] = 238;
				cellImg.at<Vec3b>(x, y)[2] = 238;
			}
			else //배경색(연회색)
			{
				cellImg.at<Vec3b>(x, y)[0] = 255;
				cellImg.at<Vec3b>(x, y)[1] = 255;
				cellImg.at<Vec3b>(x, y)[2] = 255;
			}

			if (x >= 2 && y >= 2) //하나 다른 픽셀 값들 일반화
			{
				if ((cellImg.at<Vec3b>(x - 2, y) != cellImg.at<Vec3b>(x - 1, y)) && (cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x - 1, y)))
				{
					cellImg.at<Vec3b>(x - 1, y)[0] = cellImg.at<Vec3b>(x, y)[0];
					cellImg.at<Vec3b>(x - 1, y)[1] = cellImg.at<Vec3b>(x, y)[1];
					cellImg.at<Vec3b>(x - 1, y)[2] = cellImg.at<Vec3b>(x, y)[2];
				}
			}


		}
	}



	//첫번째줄(6칸) 판별하기 위한 for문1
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (x >= 1 && y >= 1)
			{
				if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x - 1, y)))
				{
					change[y]++;
				}
			}
		}
		//printf("height %d 's change: %d \n", y, change[y]);
	}
	//첫번째줄(6칸) 변화지점 좌표 저장하는 for문2
	for (int y = 0; y < height; y++)
	{
		if (change[y] == 12)
			if (start == false)
			{
				start = true;
				left = y;
				for (int x = 0; x < width; x++) {
					if (x >= 1)
					{
						if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x - 1, y)))
						{
							changePos.push(x);
							changePos.push(y);
							changePos.push(cellImg.at<Vec3b>(x, y)[0]);
						}
					}
				}
			}
		if (change[y] == 0 && start == true)
			if (end == false)
			{
				end = true;
				right = y - 1;
				for (int x = 0; x < width; x++) {
					if (x >= 1)
					{
						if ((cellImg.at<Vec3b>(x, y - 1) != cellImg.at<Vec3b>(x - 1, y - 1)))
						{
							changePos.push(x - 1);
							changePos.push(y - 1);
							changePos.push(cellImg.at<Vec3b>(x - 1, y - 1)[0]);
						}
					}
				}
			}
	}
	//첫번째줄(6칸) 칸 최소,최대 좌표 저장하는 for문3
	for (int i = 0; i < change[left]; i++)
	{
		if (i % 2 == 0 && changePos.front())
		{

			firstrow[index * 5] = changePos.front(); //x-min
			changePos.pop();
			firstrow[index * 5 + 1] = changePos.front(); //y-min
			changePos.pop();
			firstrow[index * 5 + 2] = changePos.front(); //color
			changePos.pop();

			index++;
		}
		else if (i % 2 == 1 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}
	index = 0;
	for (int i = 0; i < change[right]; i++)
	{
		if (i % 2 == 1 && changePos.front())
		{
			firstrow[index * 5 + 3] = changePos.front(); //x-max
			changePos.pop();
			firstrow[index * 5 + 4] = changePos.front(); //y-max
			changePos.pop();
			changePos.pop();
			index++;
		}
		else if (i % 2 == 0 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}

	for (int i = 0; i < 6; i++)
	{
		Cell tmp;
		tmp.min.first = firstrow[i * 5];
		tmp.min.second = firstrow[i * 5 + 1];
		tmp.max.first = firstrow[i * 5 + 3];
		tmp.max.second = firstrow[i * 5 + 4];
		tmp.info = BoardCellColor(firstrow[i * 5 + 2]);

		cells.push_back(tmp);
		//printf("(x-min,y-min) = ( %d , %d ) | (x-max,y-max) = ( %d , %d ) | color: %d\n",firstrow[i*5], firstrow[i * 5+1], firstrow[i * 5+3], firstrow[i * 5+4], firstrow[i * 5 + 2]);
	}

	///
	start = false, end = false;
	index = 0;

	for (int x = 0; x < width; x++) {

		for (int y = 0; y < height; y++) {

			if (x >= 2 && y >= 2) //하나 다른 픽셀 값들 일반화
			{
				if ((cellImg.at<Vec3b>(x, y - 2) != cellImg.at<Vec3b>(x, y - 1)) && (cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y - 1)))
				{
					cellImg.at<Vec3b>(x, y - 1)[0] = cellImg.at<Vec3b>(x, y)[0];
					cellImg.at<Vec3b>(x, y - 1)[1] = cellImg.at<Vec3b>(x, y)[1];
					cellImg.at<Vec3b>(x, y - 1)[2] = cellImg.at<Vec3b>(x, y)[2];
				}
			}
		}
	}

	//두번째줄(7칸) 판별하기 위한 for문1
	for (int x = firstrow[25] - 5; x < width; x++) {
		for (int y = firstrow[29] + 1; y < height; y++) {
			if (x >= firstrow[25] - 4 && y >= firstrow[29] + 2)
			{
				if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y - 1)))
				{
					change2[x]++;

				}
			}
		}
	}



	//두번째줄(7칸) 변화지점 좌표 저장하는 for문2
	for (int x = firstrow[25] - 5; x < width; x++)
	{
		if (change2[x] == 14)
			if (start == false)
			{
				start = true;
				top = x;
				for (int y = firstrow[29] + 1; y < height; y++) {
					if (y >= firstrow[29] + 2)
					{
						if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y - 1)))
						{
							changePos.push(x);
							changePos.push(y);
							changePos.push(cellImg.at<Vec3b>(x, y)[0]);
						}
					}
				}
			}
		if (change2[x] == 0 && start == true)
			if (end == false)
			{
				end = true;
				bottom = x - 1;

				for (int y = firstrow[29] + 1; y < height; y++) {
					if (y >= firstrow[29] + 2)
					{
						if ((cellImg.at<Vec3b>(x - 1, y) != cellImg.at<Vec3b>(x - 1, y - 1)))
						{
							changePos.push(x - 1);
							changePos.push(y - 1);
							changePos.push(cellImg.at<Vec3b>(x - 1, y - 1)[0]);

						}
					}
				}
			}
	}



	//두번째줄(7칸) 칸 최소,최대 좌표 저장하는 for문3
	for (int i = 0; i < change2[top]; i++)
	{
		if (i % 2 == 0 && changePos.front())
		{

			secondrow[index * 5] = changePos.front(); //x-min
			changePos.pop();
			secondrow[index * 5 + 1] = changePos.front(); //y-min
			changePos.pop();
			secondrow[index * 5 + 2] = changePos.front(); //color
			changePos.pop();

			index++;
		}
		else if (i % 2 == 1 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}
	index = 0;
	for (int i = 0; i < change2[bottom]; i++)
	{
		if (i % 2 == 1 && changePos.front())
		{
			secondrow[index * 5 + 3] = changePos.front(); //x-max
			changePos.pop();
			secondrow[index * 5 + 4] = changePos.front(); //y-max
			changePos.pop();
			changePos.pop();

			index++;
		}
		else if (i % 2 == 0 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}


	for (int i = 0; i < 7; i++)
	{
		Cell tmp;
		tmp.min.first = secondrow[i * 5];
		tmp.min.second = secondrow[i * 5 + 1];
		tmp.max.first = secondrow[i * 5 + 3];
		tmp.max.second = secondrow[i * 5 + 4];
		tmp.info = BoardCellColor(secondrow[i * 5 + 2]);

		cells.push_back(tmp);
		//printf("(x-min,y-min) = ( %d , %d ) | (x-max,y-max) = ( %d , %d ) | color: %d\n", secondrow[i * 5], secondrow[i * 5 + 1], secondrow[i * 5 + 3], secondrow[i * 5 + 4], secondrow[i * 5 + 2]);
	}

	start = false, end = false;
	index = 0;

	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			if (x >= 2 && y >= 2) //하나 다른 픽셀 값들 일반화
			{
				if ((cellImg.at<Vec3b>(x - 2, y) != cellImg.at<Vec3b>(x - 1, y)) && (cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x - 1, y)))
				{
					cellImg.at<Vec3b>(x - 1, y)[0] = cellImg.at<Vec3b>(x, y)[0];
					cellImg.at<Vec3b>(x - 1, y)[1] = cellImg.at<Vec3b>(x, y)[1];
					cellImg.at<Vec3b>(x - 1, y)[2] = cellImg.at<Vec3b>(x, y)[2];
				}
			}
		}
	}

	//세번째줄(5칸) 판별하기 위한 for문1
	for (int y = secondrow[31] - 5; y < height; y++) {
		for (int x = secondrow[30] - 5; x > 0; x--) {
			if (x >= 1 && x < secondrow[30] - 10)
			{
				if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x + 1, y)))
				{
					change3[y]++;
				}
			}
		}
	}

	//세번째줄(5칸) 변화지점 좌표 저장하는 for문2
	for (int y = secondrow[31] - 5; y < height; y++)
	{
		if (change3[y] == 10)
			if (start == false)
			{
				start = true;
				left = y;
				for (int x = secondrow[30] - 5; x > 0; x--) {
					if (x >= 1)
					{
						if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x - 1, y)))
						{
							changePos.push(x);
							changePos.push(y);
							changePos.push(cellImg.at<Vec3b>(x, y)[0]);
						}
					}
				}
			}
		if (change3[y] == 0 && start == true)
			if (end == false)
			{
				end = true;
				right = y - 1;

				for (int x = secondrow[30] - 5; x > 0; x--) {
					if (x >= 1)
					{
						if ((cellImg.at<Vec3b>(x, y - 1) != cellImg.at<Vec3b>(x - 1, y - 1)))
						{
							changePos.push(x - 1);
							changePos.push(y - 1);
							changePos.push(cellImg.at<Vec3b>(x - 1, y - 1)[0]);

						}
					}
				}
			}
	}


	//세번째줄(5칸) 칸 최소,최대 좌표 저장하는 for문3
	for (int i = 0; i < change3[left]; i++)
	{
		if (i % 2 == 1 && changePos.front())
		{

			thirdrow[index * 5] = changePos.front(); //x-min
			changePos.pop();
			thirdrow[index * 5 + 1] = changePos.front(); //y-min
			changePos.pop();
			thirdrow[index * 5 + 2] = changePos.front(); //color
			changePos.pop();
			index++;


		}
		else if (i % 2 == 0 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}
	index = 0;
	for (int i = 0; i < change3[right]; i++)
	{
		if (i % 2 == 0 && changePos.front())
		{
			thirdrow[index * 5 + 3] = changePos.front(); //x-max
			changePos.pop();
			thirdrow[index * 5 + 4] = changePos.front(); //y-max
			changePos.pop();
			changePos.pop();

			index++;
		}
		else if (i % 2 == 1 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}

	for (int i = 0; i < 5; i++)
	{
		Cell tmp;
		tmp.min.first = thirdrow[i * 5];
		tmp.min.second = thirdrow[i * 5 + 1];
		tmp.max.first = thirdrow[i * 5 + 3];
		tmp.max.second = thirdrow[i * 5 + 4];
		tmp.info = BoardCellColor(thirdrow[i * 5 + 2]);

		cells.push_back(tmp);
		//printf("(x-min,y-min) = ( %d , %d ) | (x-max,y-max) = ( %d , %d ) | color: %d\n", thirdrow[i * 5], thirdrow[i * 5 + 1], thirdrow[i * 5 + 3], thirdrow[i * 5 + 4], thirdrow[i * 5 + 2]);
	}


	start = false, end = false;

	for (int x = 0; x < width; x++) {

		for (int y = 0; y < height; y++) {
			if (x >= 2 && y >= 2) //하나 다른 픽셀 값들 일반화
			{
				if ((cellImg.at<Vec3b>(x, y - 2) != cellImg.at<Vec3b>(x, y - 1)) && (cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y - 1)))
				{
					cellImg.at<Vec3b>(x, y - 1)[0] = cellImg.at<Vec3b>(x, y)[0];
					cellImg.at<Vec3b>(x, y - 1)[1] = cellImg.at<Vec3b>(x, y)[1];
					cellImg.at<Vec3b>(x, y - 1)[2] = cellImg.at<Vec3b>(x, y)[2];
				}
			}
		}
	}

	//4번째줄(5칸) 판별하기 위한 for문1
	for (int x = thirdrow[23] + 3; x > 0; x--) {
		for (int y = thirdrow[21] - 1; y > firstrow[4] + 1; y--) {
			if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y - 1)))
			{
				change4[x]++;
			}
		}
	}



	//4번째줄(5칸) 변화지점 좌표 저장하는 for문2
	for (int x = thirdrow[23] + 3; x > 0; x--)
	{
		if (change4[x] == 12)
			if (start == false)
			{
				start = true;
				bottom = x;
				for (int y = thirdrow[21] - 1; y > firstrow[4] + 1; y--) {
					if ((cellImg.at<Vec3b>(x, y) != cellImg.at<Vec3b>(x, y + 1)))
					{
						changePos.push(x);
						changePos.push(y);
						changePos.push(cellImg.at<Vec3b>(x, y)[0]);
					}
				}
			}
		if (change4[x] == 0 && start == true)
			if (end == false)
			{
				end = true;
				top = x + 1;

				for (int y = thirdrow[21] - 1; y > firstrow[4] + 1; y--) {
					if ((cellImg.at<Vec3b>(x + 1, y) != cellImg.at<Vec3b>(x + 1, y - 1)))
					{
						changePos.push(x + 1);
						changePos.push(y - 1);
						changePos.push(cellImg.at<Vec3b>(x + 1, y - 1)[0]);
					}
				}
			}
	}



	//4번째줄(5칸) 칸 최소,최대 좌표 저장하는 for문3
	index = 0;
	for (int i = 0; i < change4[top]; i++)
	{
		if (i % 2 == 1 && changePos.front())
		{

			fourthrow[index * 5 + 3] = changePos.front(); //x-min
			changePos.pop();
			fourthrow[index * 5 + 4] = changePos.front(); //y-min
			changePos.pop();
			fourthrow[index * 5 + 2] = changePos.front(); //color
			changePos.pop();

			index++;
		}
		else if (i % 2 == 0 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}
	changePos.pop();
	changePos.pop();
	changePos.pop();
	index = 0;
	for (int i = 0; i < change4[bottom]; i++)
	{
		if (i % 2 == 0 && changePos.front())
		{
			fourthrow[index * 5] = changePos.front(); //x-max
			changePos.pop();
			fourthrow[index * 5 + 1] = changePos.front(); //y-max
			changePos.pop();
			changePos.pop();

			index++;
		}
		else if (i % 2 == 1 && changePos.front())
		{
			changePos.pop();
			changePos.pop();
			changePos.pop();
		}
	}


	for (int i = 0; i < 6; i++)
	{
		Cell tmp;
		tmp.min.first = fourthrow[i * 5];
		tmp.min.second = fourthrow[i * 5 + 1];
		tmp.max.first = fourthrow[i * 5 + 3];
		tmp.max.second = fourthrow[i * 5 + 4];
		tmp.info = BoardCellColor(fourthrow[i * 5 + 2]);

		cells.push_back(tmp);
		//printf("(x-min,y-min) = ( %d , %d ) | (x-max,y-max) = ( %d , %d ) | color: %d\n", fourthrow[i * 5], fourthrow[i * 5 + 1], fourthrow[i * 5 + 3], fourthrow[i * 5 + 4], fourthrow[i * 5 + 2]);
	}


}


char DIPTeamProject_Team5DicerDlg_Board::BoardCellColor(int colornum) { // 칸을 나타내는 숫자가 어떤 색을 의미하는지 문자로 반환 (DistributeCell 함수에서 사용)

	char color;

	if (colornum == 70) //dark color(black-일반칸) -> +1
		color = 'd';
	else if (colornum == 100) //green -> 다른 green칸의 +1위치로 이동
		color = 'g';
	else if (colornum == 140) //red -> +2
		color = 'r';
	else if (colornum == 180) //blue -> -1
		color = 'b';
	else if (colornum == 215) //yellow -> 다른 yellow칸의 +1위치로 이동
		color = 'y';
	else if (colornum == 238) //pink -> start&end point
		color = 'p';
	else if (colornum == 255) //white -> background color
		color = 'w';

	return color;

}

Mat DIPTeamProject_Team5DicerDlg_Board::ResizeMarker(int cellsize, Mat m_matImage) { // 말 이미지 크기를 보드 칸의 크기로 resize (UpdateBoard 함수에서 사용)

	Mat m_matImageTemp;

	// 보드 칸이 정사각형이라는 가정 (왠지 정사각형으러 만들것같다!!?!!) - 그래서 민지도 일단 정사각형이라 생각하고 함.
	resize(m_matImage, m_matImageTemp, Size(cellsize, cellsize), 0, 0, 1);

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
bool DIPTeamProject_Team5DicerDlg_Board::IsRedCatch(int pos) {
	if (redPos == pos) {
		redPos = 0;
		return true;
	}
	return false;
}

bool DIPTeamProject_Team5DicerDlg_Board::IsBlueCatch(int pos) {
	if (bluePos == pos) {
		bluePos = 0;
		return true;
	}
	return false;
}

bool DIPTeamProject_Team5DicerDlg_Board::IsGreenCatch(int pos) {
	if (greenPos == pos) {
		greenPos = 0;
		return true;
	}
	return false;
}

void DIPTeamProject_Team5DicerDlg_Board::UpdateBoard(Mat m_matImage) { // 이동할 위치를 받아와서 보드에 적용시킴 (Button2를 클릭하면 호출됨)

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int red, green, blue;
	//Mat marker_matImage = ResizeMarker(셀크기, imread("말 이미지 파일 이름.jpg", -1)); 리사이즈된 말 이미지가 된다

	int turn = GetCurrentTurn(); // 현재 순서인 팀 (말을 옮겨야 하는 팀)

	int originalPos = GetPosition(turn);

	// 원래 말 있던 곳 되돌림. 검은색으로
	for (int y = cells[originalPos].min.second; y <= cells[originalPos].max.second; y++) {
		for (int x = cells[originalPos].min.first; x <= cells[originalPos].max.first; x++) {
			m_matImage.at<Vec3b>(x, y) = (0, 0, 0);
		}
	}

	int newPos = CalculatePosition(turn); // 이동할 위치 정보 가져옴

	int size = cells[newPos].max.first - cells[newPos].min.first + 1;
	Mat marker_matImage = ResizeMarker(size, imread("dice\\red_1.jpg", -1)); // 이 부분도 보드 게임 칸 크기가 다 같다면 매번 여기서 말고 다른데서 한번만 해도 될듓

	int my = 0;
	int mx = 0;
	for (int y = cells[newPos].min.second; y <= cells[newPos].max.second; y++) {
		mx = 0;
		for (int x = cells[newPos].min.first; x <= cells[newPos].max.first; x++) {
			m_matImage.at<Vec3b>(x, y) = marker_matImage.at<Vec3b>(mx, my);
			mx++;
		}
		my++;
	}

	ChangeTurn(turn, newPos);

	DrawImage(IDC_PIC_VIEW2, m_matImage);
}

// 반환값 도통 모르겠는 부분은 일단 void로 해놨어욥
// 엥? 이게 뭐야? 싶은 부분이 있우먄 당장 슬랙에다 서율아 멍청한 놈아~~~~~~!~!~! 이게 뭐야~~~~~~~!~! 외쳐주시길...........