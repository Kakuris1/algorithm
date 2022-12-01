#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> Pr;
int N, K;
int map_extend_cnt = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
Pr p[2001][2001];
int cnt[2001][2001];
Pr yet = make_pair(-1, -1);
int cnt_CIV_meet = 1;

Pr Find(Pr n)
{
	if (p[n.second][n.first] == n) { return n; }
	return p[n.second][n.first] = Find(p[n.second][n.first]);
}
void Union(Pr a, Pr b)
{
	a = Find(a);
	b = Find(b);
	if (a == b) { return; }
	p[b.second][b.first] = a;
	cnt[a.second][a.first] += cnt[b.second][b.first]; // p[a] 문명의 땅 넓이 cnt
	return;
}
void check(Pr curr, Pr next);

int main()
{
	cin >> N >> K;
	fill(&p[0][0], &p[2000][2001], yet);
	fill(&cnt[0][0], &cnt[2000][2001], 1);

	queue<Pr> Q;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		Q.push(make_pair(x, y));
		p[y][x] = make_pair(x, y); // 문명 발상지만 좌표를 P로 가짐
		map_extend_cnt++;
	}

	int time_spend = 0;
	while (!Q.empty())
	{
		time_spend++;
		int Q_size = Q.size();
		for (int i = 0; i < Q_size; i++)
		{
			Pr curr = Q.front();
			Q.pop();
			for (int t = 0; t < 4; t++) {
				int nx = curr.first + dx[t];
				int ny = curr.second + dy[t];
				Pr next = make_pair(nx, ny);

				if (nx<1 || ny<1 || nx>N || ny>N || p[curr.second][curr.first] == p[ny][nx]) { continue; } // 맵 벗어남, 같은 문명임

				check(curr, next);
				if (p[ny][nx] == yet) { // 빈땅
					Q.push(next);
					Union(curr, next);
					map_extend_cnt++;
				}
				else if (p[curr.second][curr.first] != p[ny][nx]) {
					Union(curr, next); // 문명 접견
					cnt_CIV_meet++;
					if (cnt_CIV_meet == K) {
						cout << time_spend;
						return 0;
					}
					/*
					if (cnt[curr.first][curr.second] == map_extend_cnt) { // 모든 문명이 만남
						cout << time_spend;
						return 0;
					}
					*/
				}
			}
		}
	}
}

void check(Pr curr, Pr next)
{
	cout << "모든 확장 : " << map_extend_cnt << " 해당문명 땅 : " << cnt[curr.first][curr.second] << "\n\n";
	cout << "[" << curr.first << "][" << curr.second << "] -> [" << next.first << "][" << next.second << "] ";
	if (p[next.second][next.first] == yet) { cout << "빈땅 확장\n"; }
	else if (p[curr.second][curr.first] != p[next.second][next.first]) { cout << "새 문명 접견\n"; }
}

/*
* BFS하고 모두 Union 하면서 BFS로 방문한 칸의 개수와 Union 된 수가 같으면 하나가 된거임
* BFS 방문한 칸 수는 POP할때 마다 카운트하면 되고, 
* Union 된 수는 Union할 때마다 해당 집합의 개수를 더하면됨 즉, 집합이 생성될때 마다 크기 1을 넣어주자.
* 
* 가로 세로 입력 후 문명 시작지 입력받음 xy좌표
* 각 시작지를 큐에 넣고 BFS를 돌리면서 Pop하면 개수 카운트,
* 한 칸 방문할때 마다 Union
* 
*/
