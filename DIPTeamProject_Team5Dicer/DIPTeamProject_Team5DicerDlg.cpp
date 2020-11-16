#include "pch.h"
#include "framework.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DIPTeamProject_Team5DicerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDIPTeamProjectTeam5DicerDlg::CDIPTeamProjectTeam5DicerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDIPTeamProjectTeam5DicerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDIPTeamProjectTeam5DicerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL CDIPTeamProjectTeam5DicerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CDIPTeamProjectTeam5DicerDlg::OnPaint()
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

		//보드 이미지는 테스트 해볼라고 한 번 만들어본거니까 보드 판별하는 사람이 바꿔쥬세욥
		m_matImg2 = imread("dice\\board.jpg", -1);
		resize(m_matImg2, m_matImage2, Size(imgSize, imgSize), 0, 0, 1);
		CreateBitmapInfo(m_matImage2.cols, m_matImage2.rows);
		DrawImage(IDC_PIC_VIEW2, m_matImage2);
	}
}

HCURSOR CDIPTeamProjectTeam5DicerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton1() { // '주사위 굴리기' 버튼 클릭하면 red, blue, green 팀 순서대로 랜덤하게 주사위 이미지 띄움

	String fileName;

	fileName = ChangeTurn() + LoadDice();

	m_matImg1 = imread(fileName, -1);
	resize(m_matImg1, m_matImage1, Size(imgSize, imgSize), 0, 0, 1);
	CreateBitmapInfo(m_matImage1.cols, m_matImage1.rows);
	DrawImage(IDC_PIC_VIEW1, m_matImage1);
}

String CDIPTeamProjectTeam5DicerDlg::ChangeTurn() { // 순서 바꾸기 (red/blue/green 순서대로, 잡으면 한 번 더)

	//대충 사진 로드 잘 되는지 보려고 짠거니까 순서 구현하는 사람이 므시께 잘 구현해쥬세용!
	String team;

	switch (turn % 3) {
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

	turn++;
	return team;
}

String CDIPTeamProjectTeam5DicerDlg::LoadDice() { // 난수 받아서 주사위 눈 1~6 결정

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

void CDIPTeamProjectTeam5DicerDlg::CreateBitmapInfo(int width, int height) { // mat 이미지 별로 BITMAPINFO 구조체 생성

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

void CDIPTeamProjectTeam5DicerDlg::DrawImage(int id, Mat m_matImage) { // 각 Picture control에 이미지 띄움

	CClientDC dc(GetDlgItem(id));
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR);

	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matImage.cols, m_matImage.rows, m_matImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton2() { // '말 이동하기' 버튼 클릭하면 말 움직이는 함수 호출

	UpdateBoard(m_matImage2);
	//UpdateBoard(Binarization(m_matImage2));
}

Mat CDIPTeamProjectTeam5DicerDlg::Binarization(Mat m_matImage) { // 보드 이미지 이진화 시켜서 네모칸 식별하기 편하게

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

void CDIPTeamProjectTeam5DicerDlg::CountPips(Mat m_matImage) { // 주사위 눈 세기 (CalculatePosition 함수에서 호출됨)

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int red, green, blue;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];

			// 색깔 식별, 주사위 눈 개수 식별
		}
	}
}

void CDIPTeamProjectTeam5DicerDlg::CalculatePosition(Mat m_matImage) { // 현재 위치와 주사위 숫자 이용해서 이동할 위치 계산 (UpdateBoard 함수에서 호출됨)

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int red, green, blue;

	CountPips(m_matImage1); // 현재 순서인 팀 정보와 주사위 눈 정보 가져옴

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];

			// 팀의 현재 위치 파악
		}
	}

	// 이동할 위치 계산
}

void CDIPTeamProjectTeam5DicerDlg::UpdateBoard(Mat m_matImage) { // 이동할 위치를 받아와서 보드에 적용시킴 (Button2를 클릭하면 호출됨)

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int red, green, blue;

	CalculatePosition(m_matImage2); // 현재 순서인 팀, 이동할 위치 정보 가져옴

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];

			//각 칸이 무슨 픽셀로 이루어져있는지 구분, 말을 이동시킴
			
		}
	}

}