#include<iostream>
#include<queue>
#include<algorithm>
#include<tuple>
using namespace std;
typedef pair<int, int> P;
typedef tuple<int, int, int, int> T;
int N;
bool visited[100][100];
queue<T> Q; // (x, y, 방향, turn 횟수) 1,2,3,4 순 12시부터 시계방향
P End;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	if (N == 1) { cout << 0; return 0; }
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			char c;
			cin >> c;
			if (c == 'A') { Q.push(T(x, y, 0, -1)); visited[y][x] = true; }
			if (c == 'B') { End = P(x, y); }
			if (c == 'x') { visited[y][x] = true; }
		}
	}

	while (!Q.empty())
	{
		int Qsize = Q.size();
		for (int i = 0; i < Qsize; i++)
		{
			T curr = Q.front();
			if (End == P(get<0>(curr), get<1>(curr))) {
				cout << get<3>(curr);
				return 0;
			}
			Q.pop();
			for (int t = 0; t < 4; t++)
			{
				int nx = get<0>(curr) + dx[t];
				int ny = get<1>(curr) + dy[t];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[ny][nx]) { continue; }

				int turn_cnt = get<3>(curr) + 1; // turn + 1
				if (get<2>(curr) == t + 1) { turn_cnt--; } // 안 꺾고 직진한 경우 예외 처리

				Q.push(T(nx, ny, t + 1, turn_cnt));
				visited[ny][nx] = true;
			}
		}
	}
}
