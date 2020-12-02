#pragma once

#include <string>
#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "Distribution.h"

using namespace cv;
using namespace std;

class GameProgress {
	
public:
	int catchFlag = -1;

	void setDiceImage(Mat m_matImage);
	void setDistribution(Distribution tmp);

	int GetCurrentTurn();
	int ChangeTurn(int pos);

	int CalculatePosition(int pos);
	int GetPosition();
	void SetPosition(int pos);
	
private:
	Mat filter = imread("imageAsset\\filter.jpg");
	Mat diceImage;
	int turn = 0;
	int redPos = -1, bluePos = -1, greenPos = -1;
	Distribution gameInfo;

	int FindSpecialPosition(int pos);

	bool IsRedCatch(int pos);
	bool IsBlueCatch(int pos);
	bool IsGreenCatch(int pos);

	Mat Binarization(Mat m_matImage);
	int RecognizeDiceNum(Mat m_matImage);
};
