#include "pch.h"
#include "Distribution.h"

// board 이미지를 받아오고, 칸 식별하는 함수를 호출한다.
void Distribution::SetBoardImage(Mat m_matImage) {
	boardImage = m_matImage.clone();
	DistributeCell();
}

// cmp 관련 된 함수는 각 줄 별로(왼쪽, 아래, 오른쪽, 위쪽) 식별 된 칸의 순서를 정렬하기 위한 함수다.

// 왼쪽 세로 줄은 row 값이 작은 cell이 앞에 와야 한다.
bool cmpFrist(const Cell& u, const Cell& v) {
	return u.min.first < v.min.first;
}

// 아래 가로 줄은 column 값이 작은 cell이 앞에 와야 한다.
bool cmpSecond(const Cell& u, const Cell& v) {
	return u.min.second < v.min.second;
}

// 오른쪽 세로 줄은 row 값이 큰 cell이 앞에 와야 한다.
bool cmpThird(const Cell& u, const Cell& v) {
	return u.min.first > v.min.first;
}

// 위쪽 가로 줄은 column 값이 큰 cell이 앞에 와야 한다.
bool cmpFourth(const Cell& u, const Cell& v) {
	return u.min.second > v.min.second;
}

void Distribution::DistributeCell() {
	int width = boardImage.cols;
	int height = boardImage.rows;

	// board size에 맞는 이차원 배열 벡터를 생성한다.
	// visit은 이미 식별된 칸인지 확인을 위해 사용한다.
	for (int i = 0; i < height; i++) {
		vector<int> tmp(width, -1);
		visit.push_back(tmp);
	}

	// 왼쪽 세로 cell들을 식별
	for (int c = 0; c < width / 8; c++) {
		for (int r = 0; r < height; r++) {

			int blue = boardImage.at<Vec3b>(r, c)[0];
			int green = boardImage.at<Vec3b>(r, c)[1];
			int red = boardImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c);
			}
		}
		if (cellNum == 5) {
			break;
		}
	}

	sort(cells.begin(), cells.end(), cmpFrist);

	// 아래쪽 가로 cell들을 식별
	for (int r = cells[5].min.first; r < height; r++) {
		for (int c = 0; c < width; c++) {

			int blue = boardImage.at<Vec3b>(r, c)[0];
			int green = boardImage.at<Vec3b>(r, c)[1];
			int red = boardImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c);
			}
		}
		if (cellNum == 12) {
			break;
		}
	}

	sort(cells.begin() + 5, cells.end(), cmpSecond);

	// 오른쪽 세로 cell들을 식별
	for (int c = cells[12].min.second; c < width; c++) {
		for (int r = cells[12].min.first; r > 0; r--) {

			int blue = boardImage.at<Vec3b>(r, c)[0];
			int green = boardImage.at<Vec3b>(r, c)[1];
			int red = boardImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c);
			}
		}
		if (cellNum == 17) {
			break;
		}
	}
	sort(cells.begin() + 12, cells.end(), cmpThird);

	// 윗쪽 가로 cell들을 식별
	for (int r = cells[17].max.first; r > 0; r--) {
		for (int c = cells[17].min.second; c > 0; c--) {

			int blue = boardImage.at<Vec3b>(r, c)[0];
			int green = boardImage.at<Vec3b>(r, c)[1];
			int red = boardImage.at<Vec3b>(r, c)[2];

			if (((blue + green + red) / 3 <= 238) && visit[r][c] == -1) {
				cellNum++;
				FindCellBound(r, c);
			}
		}
		if (cellNum == 23) {
			break;
		}
	}
	sort(cells.begin() + 17, cells.end(), cmpFourth);
}

// 어떤 cell인지에 대한 정보를 넘겨주기 위한 함수.
char Distribution::BoardCellColor(int r, int c) {
	int blue = boardImage.at<Vec3b>(r, c)[0];
	int green = boardImage.at<Vec3b>(r, c)[1];
	int red = boardImage.at<Vec3b>(r, c)[2];

	if ((blue + green + red) / 3 <= 70) // 검은칸
	{
		if (flag) {
			dark_color = Vec3b(blue, green, red);
		}
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
	else if (((blue + green + red) / 3 <= 238)) //분홍색칸
	{
		return 'p';
	}
}

// bfs를 이용하여 해당 cell 영역을 식별한다.
void Distribution::FindCellBound(int i, int j) {

	int width = boardImage.cols;
	int height = boardImage.rows;

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
				int blue = boardImage.at<Vec3b>(nextRow, nextColumn)[0];
				int green = boardImage.at<Vec3b>(nextRow, nextColumn)[1];
				int red = boardImage.at<Vec3b>(nextRow, nextColumn)[2];

				if (((blue + green + red) / 3 <= 238) && visit[nextRow][nextColumn] == -1) {
					visit[nextRow][nextColumn] = cellNum;

					// 각 cell의 정보로 최소 위치와 최대 위치를 저장하므로, 최소/최대를 찾는다.
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

	// 이미지에 노이즈가 있는 경우, 작은 점도 cell로 인식되어서 노이즈는 cell에 포함시키지 않기 위해 해당 조건 추가.
	if (maxC - minC > 10) {
		Cell tmp;
		tmp.max = make_pair(maxR, maxC);
		tmp.min = make_pair(minR, minC);
		//그냥 min이나 max값 이용하면 색상 식별이 이상하게 되어서 cell의 중앙값을 기준으로 색을 식별한다.
		tmp.info = BoardCellColor((maxR + minR) / 2, (maxC + minC) / 2);

		cells.push_back(tmp);
	}
}

