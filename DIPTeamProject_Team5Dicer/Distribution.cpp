#include "pch.h"
#include "Distribution.h"

void Distribution::SetBoardImage(Mat m_matImage) {
	boardImage = m_matImage.clone();
	DistributeCell();
}

bool cmpFrist(const Cell& u, const Cell& v) {
	return u.min.first < v.min.first;
}

bool cmpSecond(const Cell& u, const Cell& v) {
	return u.min.second < v.min.second;
}

bool cmpThird(const Cell& u, const Cell& v) {
	return u.min.first > v.min.first;
}

bool cmpFourth(const Cell& u, const Cell& v) {
	return u.min.second > v.min.second;
}

void Distribution::DistributeCell() {
	int width = boardImage.cols;
	int height = boardImage.rows;

	for (int i = 0; i < height; i++) {
		vector<int> tmp(width, -1);
		visit.push_back(tmp);
	}

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

char Distribution::BoardCellColor(int r, int c) {
	int blue = boardImage.at<Vec3b>(r, c)[0];
	int green = boardImage.at<Vec3b>(r, c)[1];
	int red = boardImage.at<Vec3b>(r, c)[2];

	if ((blue + green + red) / 3 <= 70) // °ËÀºÄ­
	{
		if (flag) {
			dark_color = Vec3b(blue, green, red);
		}
		return 'd';
	}
	else if (((blue + green + red) / 3 <= 100)) //ÃÊ·Ï»öÄ­
	{
		return 'g';
	}
	else if (((blue + green + red) / 3 <= 140)) //»¡°£»öÄ­
	{
		return 'r';
	}
	else if (((blue + green + red) / 3 <= 180)) //ÆÄ¶õ»öÄ­
	{
		return 'b';
	}
	else if (((blue + green + red) / 3 <= 215)) //³ë¶õ»öÄ­
	{
		return 'y';
	}
	else if (((blue + green + red) / 3 <= 238)) //ºÐÈ«»öÄ­
	{
		return 'p';
	}
	else {
		return 'w';
	}
}

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

	if (maxC - minC > 10) {
		Cell tmp;
		tmp.max = make_pair(maxR, maxC);
		tmp.min = make_pair(minR, minC);
		//±×³É minÀÌ³ª max°ª ÀÌ¿ëÇÏ¸é »ö»ó ½Äº°ÀÌ ÀÌ»óÇÏ°Ô µÊ.
		tmp.info = BoardCellColor((maxR + minR) / 2, (maxC + minC) / 2);

		cells.push_back(tmp);
	}
}

