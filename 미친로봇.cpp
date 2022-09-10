#include<iostream>
using namespace std;
int N;
bool visited[30][30];
double East, West, South, North;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

double dfs(int x, int y, int move_cnt)
{
	if (move_cnt == N) { return 1; }// 이동 종료시
	visited[y][x] = true;
	double sum = 0;
	for (int d = 0; d < 4; d++) // 동서남북 순
	{
		int next_x = x + dx[d];
		int next_y = y + dy[d];
		if (visited[next_y][next_x] == true) { continue; } // 단순하지 않음

		double tmp = dfs(next_x, next_y, move_cnt + 1);
		visited[next_y][next_x] = false;

		switch (d)
		{
		case 0:
			tmp *= East / 100;
			break;
		case 1:
			tmp *= West / 100;
			break;
		case 2:
			tmp *= South / 100;
			break;
		case 3:
			tmp *= North / 100;
			break;
		default:
			break;
		}
		sum += tmp;
	}
	return sum;
}

int main()
{
	cin >> N >> East >> West >> South >> North;
	cout.precision(10);
	cout << fixed;
	cout << dfs(15, 15, 0);
}
