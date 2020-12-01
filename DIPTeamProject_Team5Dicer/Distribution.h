#pragma once
#include <string>
#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

struct cell {
	pair<int, int> min;
	pair<int, int> max;
	char info;
}typedef Cell;

class Distribution {
public:
	vector<Cell> cells; // 보드 위의 각 cell의 위치 정보, 특수 칸 정보가 담겨 있음.
	Vec3b dark_color;

	void SetBoardImage(Mat m_matImage);
	void DistributeCell();
	char BoardCellColor(int r, int c);
	void FindCellBound(int i, int j);
private:
	Mat boardImage;
	int cellNum = 0;
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	vector<vector<int>> visit;
	int flag = 1;
};