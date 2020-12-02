#include "pch.h"
#include "GameProgress.h"


// dice�̹����� setting�Ѵ�.
void GameProgress::setDiceImage(Mat m_matImage) {
	diceImage = m_matImage.clone();
}

// Distribution ��ü�� setting�Ѵ�.(������ Cell�� �̿��ؾ� �ϹǷ�)
void GameProgress::setDistribution(Distribution tmp) {
	gameInfo = tmp;
}

// ���� ���� ������ �Ѱ��ش�.
int GameProgress::GetCurrentTurn() {
	return turn;
}

// ���ʸ� �ٲ۴�. ���� �������� ���ʸ� �ѱ��, ������� �ѹ� �� ��ȸ�� �ش�.
int GameProgress::ChangeTurn(int pos) {
	switch (turn) {
	case 0:
		if (!IsBlueCatch(pos) && !IsGreenCatch(pos)) {
			turn++;
		}
		break;
	case 1:
		if ( !IsRedCatch(pos) && !IsGreenCatch(pos) ) {
			turn++;
		}
		break;
	case 2:
		if (!IsRedCatch(pos) && !IsBlueCatch(pos)) {
			turn=0;
		}
	}
	return turn;
}

// Ư��ĭ�϶��� �̵��ؾ��� ��ġ�� ����Ѵ�.
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

// �ֻ��� ���ڿ� ���� �̵��ؾ� �� ��ġ�� ����Ѵ�.
int  GameProgress::CalculatePosition(int pos) {

	// �ֻ��� �� ����
	int pips = RecognizeDiceNum(Binarization(diceImage)); 
	pos += pips;

	// ��ü ĭ �� ���� ��� �� ��ġ ���� ũ�ų� ���ٸ� ������ ĭ�� �Ѿ�ٴ� ���̴�.
	if (pos >= gameInfo.cells.size()) {
		return 0;
	}
	// �⺻ ĭ�� ��� �� ��ġ�� �ٷ� ��ȯ�Ѵ�.
	else if (gameInfo.cells[pos].info == 'd') {
		return pos;
	}
	// �⺻ ĭ�� �ƴ� ��쿡�� Ư��ĭ�̹Ƿ�, Ư��ĭ�� ���� ����� �Ѵ�.
	else {
		return FindSpecialPosition(pos);
	}
}

// ���ο� ��ġ�� ������ ��ġ�� �ݿ��Ѵ�.
void GameProgress::SetPosition(int pos) {
	switch (turn) {
	case 0:
		redPos = pos;
		break;
	case 1:
		bluePos = pos;
		break;
	case 2:
		greenPos = pos;
	}
}

// ������ ��ġ�� ��ȯ�Ѵ�.
int GameProgress::GetPosition() {
	switch (turn) {
	case 0:
		return redPos;
	case 1:
		return bluePos;
	case 2:
		return greenPos;
	}
}

// red���� ���� �������� Ȯ���Ѵ�.
bool GameProgress::IsRedCatch(int pos) {
	if (redPos == pos) {
		catchFlag = 0;
		redPos = -1;
		return true;
	}
	return false;
}

// blue���� ���� �������� Ȯ���Ѵ�.
bool GameProgress::IsBlueCatch(int pos) {
	if (bluePos == pos) {
		catchFlag = 1;
		bluePos = -1;
		return true;
	}
	return false;
}

// green���� ���� �������� Ȯ���Ѵ�.
bool GameProgress::IsGreenCatch(int pos) {
	if (greenPos == pos) {
		catchFlag = 2;
		greenPos = -1;
		return true;
	}
	return false;
}


Mat GameProgress::Binarization(Mat m_matImage) { 
	int width = m_matImage.cols;
	int height = m_matImage.rows;
	int color, blue, green, red;
	Mat m_matImg = Mat::zeros(height, width, m_matImage.type());

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// �̹��� RGB2GRAY
			blue = m_matImage.at<Vec3b>(x, y)[0];
			green = m_matImage.at<Vec3b>(x, y)[1];
			red = m_matImage.at<Vec3b>(x, y)[2];
			color = (blue + green + red) / 3;

			// threshold:180 -> ����ȭ
			if (color > 180)
				m_matImg.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
			else
				m_matImg.at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		}
	}

	return m_matImg;
}

// �ֻ��� ���� �˾Ƴ��� (CalculatePosition �Լ����� ȣ���)
int GameProgress::RecognizeDiceNum(Mat m_matImage) {

	
	int count = 0;
	int diceNum = 0;

	int fw = filter.cols;
	int fh = filter.rows;
	Mat t_matImage;
	resize(m_matImage, t_matImage, Size(fw, fh), 0, 0, 1); //�̹��� ���Ϳ� ���� ������� resize
	t_matImage = Binarization(t_matImage);	//�̹��� ����ȭ

	int width = t_matImage.cols;
	int height = t_matImage.rows;

	//���Ϳ� �̹����� ���ϸ� ���� ��� 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (t_matImage.at<Vec3b>(col, row)[0] == 0) {
				count = count + filter.at<Vec3b>(col, row)[0];
			}
		}
	}

	//������ ���� ���� �з�
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




