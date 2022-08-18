#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int M, N; // M : X, N : Y
queue<pair<int, int>>Q;
bool visited[1001][1001];
bool have_route[1001][1001];
bool Already_clear = true;
int day = -1;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

void bfs()
{
	while (!Q.empty())
	{
		day++;
		int Qsize = Q.size();
		for (int Qfor = 0; Qfor < Qsize; Qfor++)
		{
			pair<int, int>curr = Q.front();
			Q.pop();
			for (int i = 0; i < 4; i++)
			{
				int nx = curr.first + dx[i];
				int ny = curr.second + dy[i];
				if (nx > 0 && ny > 0 && nx <= M && ny <= N){
					if (have_route[ny][nx] && !visited[ny][nx]) {
						Q.push(make_pair(nx, ny));
						visited[ny][nx] = true;
					}
				}
			}
		}
	}
}

int main()
{
	cin >> M >> N; // M : X, N : Y
	int tmp;
	for (int y = 1; y <= N; y++) {// 좌표 범위 1~1000
		for (int x = 1; x <= M; x++) {
			cin >> tmp;
			if (tmp == 1) { Q.push(make_pair(x, y)); visited[y][x] = true; }
			if (tmp == 0) { have_route[y][x] = true; Already_clear = false; }
			if (tmp == -1) { have_route[y][x] = false; visited[y][x] = true; } // 이미 false지만 구색 맞추기
		}
	}
	if (Already_clear) { cout << 0; return 0; }
	else { bfs(); }

	bool finish = true;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			if (!visited[y][x]) { finish = false; }
		}
	}
	if (finish) { cout << day; }
	else { cout << -1; }
}
