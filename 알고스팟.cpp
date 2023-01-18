#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const int INF = 10000;
int M, N;
int map[101][101] = { 0, };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> M >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			char c;
			cin >> c;
			if (c == '1') { map[y][x] = 1; }
		}
	}
	priority_queue<P, vector<P>, greater<P>> PQ;
	PQ.push(P(0, 0));

	int wall_cnt[101][101];
	fill(&wall_cnt[0][0], &wall_cnt[100][101], INF);
	wall_cnt[0][0] = 0;

	while (!PQ.empty())
	{
		P curr = P(PQ.top().second / 100, PQ.top().second % 100);
		//cout << "\n[" << curr.first << "][" << curr.second << "] 현재까지 : " << PQ.top().first << "\n";
		if (PQ.top().second == (M - 1) * 100 + N - 1) {
			cout << PQ.top().first;
			return 0;
		}
		PQ.pop();
		
		for (int t = 0; t < 4; t++){
			int nx = curr.first + dx[t];
			int ny = curr.second + dy[t];
			int d = map[nx][ny];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N) { continue; }
			//cout << "-> [" << nx << "][" << ny << "] 비용 : " << d << "\n";
			if (wall_cnt[ny][nx] > wall_cnt[curr.second][curr.first] + d) {
				wall_cnt[ny][nx] = wall_cnt[curr.second][curr.first] + d;
				PQ.push(P(wall_cnt[ny][nx], nx * 100 + ny));
				//cout << "갱신 : " << wall_cnt[ny][nx] << endl;
			}
		}
	}
}
