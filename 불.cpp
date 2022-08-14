#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int T, w, h;
bool visited[1000][1000];
bool have_route[1000][1000];
queue<pair<int, int>> Q_fire;
queue<pair<int, int>> Q_prs;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

void bfs() 
{
	int dis = 0;
	while (!Q_prs.empty())
	{
		// 불 번지기 bfs
		int Qfire_size = Q_fire.size();
		for (int i = 0; i < Qfire_size; i++)
		{
			pair<int, int> curr = Q_fire.front();
			Q_fire.pop();
			for (int pos = 0; pos < 4; pos++)
			{
				int nx = curr.first + dx[pos];
				int ny = curr.second + dy[pos];
				// 불은 가장자리로 나가도 끝나지 않으므로 좌표 조건문
				if (nx >= 0 && ny >= 0 && nx < w && ny < h) {
					if (have_route[ny][nx] == true) {
						Q_fire.push(make_pair(nx, ny));
						have_route[ny][nx] = false;
					}
				}
			}
		}

		// 상근이 bfs
		int Qprs_size = Q_prs.size();
		for (int i = 0; i < Qprs_size; i++)
		{
			pair<int, int> curr = Q_prs.front();
			// 가장자리 도달했을때 함수 탈출
			if (curr.first == 0 || curr.first == w - 1 || curr.second == 0 || curr.second == h - 1) {
				cout << dis + 1 << '\n';
				return;
			}
			Q_prs.pop();
			for (int pos = 0; pos < 4; pos++)
			{
				int nx = curr.first + dx[pos];
				int ny = curr.second + dy[pos];
				if (have_route[ny][nx] && !visited[ny][nx]) {
					Q_prs.push(make_pair(nx, ny));
					visited[ny][nx] = true;
				}
			}
		}
		dis++;
	}
	cout << "IMPOSSIBLE\n";
	return;
}

void reset()
{
	fill(&visited[0][0], &visited[999][1000], false);
	fill(&have_route[0][0], &have_route[999][1000], false);
	while (!Q_fire.empty()) Q_fire.pop();
	while (!Q_prs.empty()) Q_prs.pop();
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> w >> h;
		reset();
		char c;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				cin >> c;
				if (c == '.') have_route[i][j] = true;
				if (c == '@') { Q_prs.push(make_pair(j, i)); visited[i][j] = true; }
				if (c == '*') Q_fire.push(make_pair(j, i));
				if (c == '#') have_route[i][j] = false;
			}
		bfs();
	}
}
