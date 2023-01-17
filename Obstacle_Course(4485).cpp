#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const int INF = 2500;
int N;
int map[125][125];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };


int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int problem = 1;
	while (true)
	{
		cin >> N;
		if (N == 0) { return 0; }

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				int tmp;
				cin >> tmp;
				map[y][x] = tmp;
			}
		}

		priority_queue<P, vector<P>, greater<P>> PQ; // (시작점으로 부터의 거리, X * 1000 + Y )
		PQ.push(P(map[0][0], 0));

		int dist[125][125];
		fill(&dist[0][0], &dist[124][125], INF);
		dist[0][0] = map[0][0];

		while (!PQ.empty())
		{
			P curr = P(PQ.top().second / 1000, PQ.top().second % 1000); // 현재 좌표

			//cout << "\n[" << curr.first << "][" << curr.second << "] 현재까지 : " << PQ.top().first << "\n";
			PQ.pop();
			if (curr == P(N - 1, N - 1)) {
				cout << "Problem " << problem << ": " << dist[N - 1][N - 1] << "\n";
				break;
			}

			for (int t = 0; t < 4; t++)
			{
				int nx = curr.first + dx[t];
				int ny = curr.second + dy[t];
				int d = map[ny][nx];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) { continue; }

				//cout << "-> [" << nx << "][" << ny << "] 비용 : " << d << "\n";
				if (dist[ny][nx] > dist[curr.second][curr.first] + d) {
					dist[ny][nx] = dist[curr.second][curr.first] + d;
					PQ.push(P(dist[ny][nx], nx * 1000 + ny));
					//cout << "갱신 : " << dist[ny][nx] << endl;
				}
			}
		}
		problem++;
	}
}
