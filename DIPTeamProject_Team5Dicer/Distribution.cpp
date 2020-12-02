#include "pch.h"
#include "Distribution.h"

// board �̹����� �޾ƿ���, ĭ �ĺ��ϴ� �Լ��� ȣ���Ѵ�.
void Distribution::SetBoardImage(Mat m_matImage) {
	boardImage = m_matImage.clone();
	DistributeCell();
}

// cmp ���� �� �Լ��� �� �� ����(����, �Ʒ�, ������, ����) �ĺ� �� ĭ�� ������ �����ϱ� ���� �Լ���.

// ���� ���� ���� row ���� ���� cell�� �տ� �;� �Ѵ�.
bool cmpFrist(const Cell& u, const Cell& v) {
	return u.min.first < v.min.first;
}

// �Ʒ� ���� ���� column ���� ���� cell�� �տ� �;� �Ѵ�.
bool cmpSecond(const Cell& u, const Cell& v) {
	return u.min.second < v.min.second;
}

// ������ ���� ���� row ���� ū cell�� �տ� �;� �Ѵ�.
bool cmpThird(const Cell& u, const Cell& v) {
	return u.min.first > v.min.first;
}

// ���� ���� ���� column ���� ū cell�� �տ� �;� �Ѵ�.
bool cmpFourth(const Cell& u, const Cell& v) {
	return u.min.second > v.min.second;
}

void Distribution::DistributeCell() {
	int width = boardImage.cols;
	int height = boardImage.rows;

	// board size�� �´� ������ �迭 ���͸� �����Ѵ�.
	// visit�� �̹� �ĺ��� ĭ���� Ȯ���� ���� ����Ѵ�.
	for (int i = 0; i < height; i++) {
		vector<int> tmp(width, -1);
		visit.push_back(tmp);
	}

	// ���� ���� cell���� �ĺ�
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

	// �Ʒ��� ���� cell���� �ĺ�
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

	// ������ ���� cell���� �ĺ�
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

	// ���� ���� cell���� �ĺ�
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

// � cell������ ���� ������ �Ѱ��ֱ� ���� �Լ�.
char Distribution::BoardCellColor(int r, int c) {
	int blue = boardImage.at<Vec3b>(r, c)[0];
	int green = boardImage.at<Vec3b>(r, c)[1];
	int red = boardImage.at<Vec3b>(r, c)[2];

	if ((blue + green + red) / 3 <= 70) // ����ĭ
	{
		if (flag) {
			dark_color = Vec3b(blue, green, red);
		}
		return 'd';
	}
	else if (((blue + green + red) / 3 <= 100)) //�ʷϻ�ĭ
	{
		return 'g';
	}
	else if (((blue + green + red) / 3 <= 140)) //������ĭ
	{
		return 'r';
	}
	else if (((blue + green + red) / 3 <= 180)) //�Ķ���ĭ
	{
		return 'b';
	}
	else if (((blue + green + red) / 3 <= 215)) //�����ĭ
	{
		return 'y';
	}
	else if (((blue + green + red) / 3 <= 238)) //��ȫ��ĭ
	{
		return 'p';
	}
}

// bfs�� �̿��Ͽ� �ش� cell ������ �ĺ��Ѵ�.
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

					// �� cell�� ������ �ּ� ��ġ�� �ִ� ��ġ�� �����ϹǷ�, �ּ�/�ִ븦 ã�´�.
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

	// �̹����� ����� �ִ� ���, ���� ���� cell�� �νĵǾ ������� cell�� ���Խ�Ű�� �ʱ� ���� �ش� ���� �߰�.
	if (maxC - minC > 10) {
		Cell tmp;
		tmp.max = make_pair(maxR, maxC);
		tmp.min = make_pair(minR, minC);
		//�׳� min�̳� max�� �̿��ϸ� ���� �ĺ��� �̻��ϰ� �Ǿ cell�� �߾Ӱ��� �������� ���� �ĺ��Ѵ�.
		tmp.info = BoardCellColor((maxR + minR) / 2, (maxC + minC) / 2);

		cells.push_back(tmp);
	}
}

