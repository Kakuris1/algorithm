#include<iostream>
#include<queue>
#include<tuple>
#include<algorithm>
using namespace std;
int N, K; // 맵 크기 N, 문명 개수 K
int p[100001];
int visited[2001][2001];
int v_time[2001][2001];
queue<tuple<int,int,int>> Q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

int find(int n)
{
	if (p[n] == n) { return n; }
	return p[n] = find(p[n]);
}

void Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b) { return; }
	p[b] = a;
}

int bfs()
{
	int count_year = 0;
	while (!Q.empty()) {
		bool finish = true;
		int Qsize = Q.size();

		cout << "\n" << count_year << "년 경과\n";

		int tmp = find(get<2>(Q.front()));
		for (int Qfor = 0; Qfor < Qsize; Qfor++) {
			auto curr = Q.front();
			cout << get<0>(Q.front()) << ", " << get<1>(Q.front()) << " 문명 : " << get<2>(Q.front()) << "\n";

			//if (find(get<2>(curr)) != tmp) { finish = false; }
			Q.pop();
			for (int i = 0; i < 4; i++) {
				int nx = get<0>(curr) + dx[i];
				int ny = get<1>(curr) + dy[i];
				cout << nx << ", " << ny << " : ";
				//범위를 벗어나거나 같은 문명땅이면 스킵
				if (nx<1 || ny<1 || nx>N || ny>N || visited[ny][nx] == get<2>(curr)) { cout << "불가\n";  continue; }
				if (visited[ny][nx] == -1) {
					cout << "빈땅 확장\n";
					Q.push(make_tuple(nx, ny, get<2>(curr)));
					visited[ny][nx] = get<2>(curr);
					v_time[ny][nx] = count_year+1;
				}
				else {
					cout << visited[ny][nx] << "번째 문명과 만남\n";
					Union(visited[ny][nx], get<2>(curr)); // 이미 점령한 곳으로 포함됨
				}
			}
		}
		count_year++;
		for(int i=2;i<=K; i++){
			if (find(i) != find(1)) { finish = false; }
		}
		if (finish) { return count_year; }
	}
	cout << "error\n";
	return count_year++;
}

int main()
{
	fill(&visited[0][0], &visited[2000][2001], -1);
	for (int i = 0; i < 100001; i++) { p[i] = i; }

	cin >> N >> K;

	int x = 0, y = 0;
	for (int i = 1; i <= K; i++){
		cin >> x >> y;
		Q.push(make_tuple(x, y, i));
		visited[y][x] = i;
	}

	/*
	while (!Q.empty())
	{
		cout << get<0>(Q.front())<<", "<< get<1>(Q.front())<<" 문명 : "<< get<2>(Q.front())<<"\n";
		Q.pop();
	}
	*/

	cout << bfs();
}
