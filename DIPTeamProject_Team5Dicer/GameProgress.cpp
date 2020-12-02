#include "pch.h"
#include "GameProgress.h"

void GameProgress::setDiceImage(Mat m_matImage) {
	diceImage = m_matImage.clone();
}

void GameProgress::setDistribution(Distribution tmp) {
	gameInfo = tmp;
}

int GameProgress::GetCurrentTurn() {
	return turn;
}

int GameProgress::ChangeTurn(int nowTurn, int pos) {
	switch (nowTurn) {
	case 0:
		redPos = pos;
		if (IsBlueCatch(pos) || IsGreenCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn++;
		}
		break;
	case 1:
		bluePos = pos;
		if (IsRedCatch(pos) || IsGreenCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn++;
		}
		break;
	case 2:
		greenPos = pos;
		if (IsRedCatch(pos) || IsBlueCatch(pos)) {
			turn = nowTurn;
		}
		else {
			turn = 0;
		}
	}

	return turn;
}


int GameProgress::FindSpecialPosition(int pos) {

	switch (gameInfo.cells[pos].info) {
	case 'g':
		for (int i = 1; i < gameInfo.cells.size() - 1; i++) {
			if (gameInfo.cells[i].info == 'g' && i != pos) {
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
		for (int i = 1; i < gameInfo.cells.size() - 1; i++) {
			if (gameInfo.cells[i].info == 'y' && i != pos) {
				pos = i + 1;
				break;
			}
		}
		return pos;
	}
}

int  GameProgress::CalculatePosition(int pos) { // 현재 위치와 주사위 숫자 이용해서 이동할 위치 계산 (UpdateBoard 함수에서 호출됨)

	int pips = RecognizeDiceNum(Binarization(diceImage)); // 주사위 눈 개수

	pos += pips;

	if (pos >= gameInfo.cells.size()) {
		return 0;
	}
	else if (gameInfo.cells[pos].info == 'd') {
		return pos;
	}
	else {
		return FindSpecialPosition(pos);
	}
}

int GameProgress::GetPosition(int turn) {
	switch (turn) {
	case 0:
		return redPos;
	case 1:
		return bluePos;
	case 2:
		return greenPos;
	}
}

bool GameProgress::IsRedCatch(int pos) {
	if (redPos == pos) {
		catchFlag = 0;
		redPos = -1;
		return true;
	}
	return false;
}

bool GameProgress::IsBlueCatch(int pos) {
	if (bluePos == pos) {
		catchFlag = 1;
		bluePos = -1;
		return true;
	}
	return false;
}

bool GameProgress::IsGreenCatch(int pos) {
	if (greenPos == pos) {
		catchFlag = 2;
		greenPos = -1;
		return true;
	}
	return false;
}

Mat GameProgress::Binarization(Mat m_matImage) { // 이진화

	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int color, blue, green, red;
	Mat m_matImg = Mat::zeros(height, width, m_matImage.type());

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// 이미지 RGB2GRAY
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];
			color = (blue + green + red) / 3;

			// threshold:180 -> 이진화
			if (color > 180)
				m_matImg.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
			else
				m_matImg.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}

	return m_matImg;
}

int GameProgress::RecognizeDiceNum(Mat m_matImage) { // 주사위 숫자 알아내기 (CalculatePosition 함수에서 호출됨)

	
	int count = 0;
	int diceNum = 0;

	int fw = filter.cols;
	int fh = filter.rows;
	Mat t_matImage;
	resize(m_matImage, t_matImage, Size(fw, fh), 0, 0, 1); //이미지 필터와 같은 사이즈로 resize
	t_matImage = Binarization(t_matImage);	//이미지 이진화

	int width = t_matImage.cols;
	int height = t_matImage.rows;

	//필터와 이미지를 비교하며 점수 계산 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (t_matImage.at<Vec3b>(col, row)[0] == 0) {
				count = count + filter.at<Vec3b>(col, row)[0];
			}
		}
	}

	//점수에 따라 숫자 분류
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




