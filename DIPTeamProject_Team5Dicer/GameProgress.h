#pragma once

#include <string>
#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Distribution.h"

using namespace cv;
using namespace std;

class GameProgress {
	
public:
	int catchFlag = -1;

	void setDiceImage(Mat m_matImage);
	void setDistribution(Distribution tmp);

	int GetCurrentTurn();
	int ChangeTurn(int nowTurn, int pos);

	int FindSpecialPosition(int pos);
	int CalculatePosition(int pos);
	int GetPosition(int turn);
	
	bool IsRedCatch(int pos);
	bool IsBlueCatch(int pos);
	bool IsGreenCatch(int pos);

	Mat Binarization(Mat m_matImage);
	int RecognizeDiceNum(Mat m_matImage);
private:
	Mat filter = imread("dice\\filter.jpg");
	Mat diceImage;
	int turn = 0; // turn은 현재 순서인 팀
	int redPos = -1, bluePos = -1, greenPos = -1;
	Distribution gameInfo;
};
