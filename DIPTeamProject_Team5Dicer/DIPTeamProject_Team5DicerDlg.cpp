#include "pch.h"
#include "framework.h"
#include "DIPTeamProject_Team5Dicer.h"
#include "DIPTeamProject_Team5DicerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 보드 선택 화면

CDIPTeamProjectTeam5DicerDlg::CDIPTeamProjectTeam5DicerDlg(CWnd* pParent)
	: CDialogEx(IDD_DIPTEAMPROJECT_TEAM5DICER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDIPTeamProjectTeam5DicerDlg::DoDataExchange(CDataExchange* pDX)
{
	// 각 버튼에 변수를 지정한다.
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, boardbutton1);
	DDX_Control(pDX, IDC_BUTTON2, boardbutton2);
	DDX_Control(pDX, IDC_BUTTON3, boardbutton3);
	DDX_Control(pDX, IDC_BUTTON4, boardbutton4);
	DDX_Control(pDX, IDC_BUTTON5, boardbutton5);
	DDX_Control(pDX, IDC_BUTTON6, boardbutton6);
	DDX_Control(pDX, IDC_BUTTON7, boardbutton7);
	DDX_Control(pDX, IDC_BUTTON8, ChooseBoard);
}

// 버튼의 각 ID와 버튼 클릭 함수를 연결한다.
BEGIN_MESSAGE_MAP(CDIPTeamProjectTeam5DicerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton7)
END_MESSAGE_MAP()

// 다이얼로그가 처음 생성될 때 실행된다.
BOOL CDIPTeamProjectTeam5DicerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 버튼에 bitmap 이미지 입히기
	boardbutton1.LoadBitmaps(IDB_BITMAP1, NULL, NULL, NULL);
	boardbutton2.LoadBitmaps(IDB_BITMAP2, NULL, NULL, NULL);
	boardbutton3.LoadBitmaps(IDB_BITMAP3, NULL, NULL, NULL);
	boardbutton4.LoadBitmaps(IDB_BITMAP4, NULL, NULL, NULL);
	boardbutton5.LoadBitmaps(IDB_BITMAP5, NULL, NULL, NULL);
	boardbutton6.LoadBitmaps(IDB_BITMAP6, NULL, NULL, NULL);
	boardbutton7.LoadBitmaps(IDB_BITMAP7, NULL, NULL, NULL);
	ChooseBoard.LoadBitmaps(IDB_BITMAP14, NULL, NULL, NULL);

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
	}
}

HCURSOR CDIPTeamProjectTeam5DicerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 선택된 보드 이미지에 해당하는 파일명을 게임 화면 클래스에게 전달한다.
String CDIPTeamProjectTeam5DicerDlg::getBoardName() {

	return boardName;
}

// 보드 이미지 파일명을 지정하고 게임 진행 다이얼로그를 생성한다.

// 'Board 1' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton1() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board1.jpg";
	m_board.DoModal();
}

// 'Board 2' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton2() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board2.jpg";
	m_board.DoModal();
}

// 'Board 3' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton3() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board3.jpg";
	m_board.DoModal();
}

// 'Board 4' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton4() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board4.jpg";
	m_board.DoModal();
}

// 'Board 5' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton5() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board5.jpg";
	m_board.DoModal();
}

// 'Board 6' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton6() { 

	DIPTeamProject_Team5DicerDlg_Board m_board;
	boardName = "imageAsset\\board6.jpg";
	m_board.DoModal();
}

// 'Random Board' 버튼 클릭 시
void CDIPTeamProjectTeam5DicerDlg::OnBnClickedButton7() { 

	// 난수 받아서 랜덤하게 보드 이미지 파일명을 지정하고 게임 진행 다이얼로그를 생성한다.
	DIPTeamProject_Team5DicerDlg_Board m_board;

	srand(time(NULL));
	int randNum = rand() % 6;

	switch (randNum) {
	case 0:
		boardName = "imageAsset\\board1.jpg";	break;
	case 1:
		boardName = "imageAsset\\board2.jpg";	break;
	case 2:
		boardName = "imageAsset\\board3.jpg";	break;
	case 3:
		boardName = "imageAsset\\board4.jpg";	break;
	case 4:
		boardName = "imageAsset\\board5.jpg";	break;
	case 5:
		boardName = "imageAsset\\board6.jpg";	break;
	}

	m_board.DoModal();
}