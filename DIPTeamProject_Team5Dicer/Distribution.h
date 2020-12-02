#pragma once
#include <string>
#include <vector>
#include <queue>
#include <opencv2/core/types_c.h>

using namespace cv;
using namespace std;

// 보드 위의 각 cell의 위치 정보, 특수 칸 정보가 담겨 있음.
struct cell {
	pair<int, int> min;
	pair<int, int> max;
	char info;
}typedef Cell;

class Distribution {
public:
	vector<Cell> cells;
	Vec3b dark_color;

	void SetBoardImage(Mat m_matImage);
private:
	Mat boardImage;
	int cellNum = 0;
	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	vector<vector<int>> visit;
	int flag = 1;

	void DistributeCell();
	char BoardCellColor(int r, int c);
	void FindCellBound(int i, int j);
};