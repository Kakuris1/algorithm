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



//



// 연장 풀이, 19점 부분정답



//


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
bool this_year[2001][2001];
Pr yet = make_pair(0, 0);
int cnt_CIV_meet = 1;

Pr Find(Pr n)
{
	if (p[n.second][n.first] == n) { return n; }
	return p[n.second][n.first] = Find(p[n.second][n.first]);
}
void Union(Pr a, Pr b)
{
	Pr A = Find(a);
	Pr B = Find(b);
	if (A == B) { return; }
	//cout << " Union 됨 ";
	if (B == yet) {
		p[b.second][b.first] = A;
		cnt[A.second][A.first] += cnt[b.second][b.first]; // p[a] 문명의 땅 넓이 cnt
	}
	else {
		p[B.second][B.first] = A;
		cnt[A.second][A.first] += cnt[B.second][B.first]; // p[a] 문명의 땅 넓이 cnt
	}
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
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
		//cout << time_spend << " 년째\n\n";
		fill(&this_year[0][0], &this_year[2000][2001], false);
		int Q_size = Q.size();
		for (int i = 0; i < Q_size; i++)
		{
			Pr curr = Q.front();
			Q.pop();
			for (int t = 0; t < 4; t++) {
				int nx = curr.first + dx[t];
				int ny = curr.second + dy[t];
				Pr next = make_pair(nx, ny);

				if (nx<1 || ny<1 || nx>N || ny>N || Find(curr) == Find(next)) { continue; } // 맵 벗어남, 같은 문명임

				//cout << "[" << curr.first << "][" << curr.second << "] ("<<p[curr.second][curr.first].first << ", " << p[curr.second][curr.first].second << ") ->["
					//<< next.first << "][" << next.second << "] (" << p[next.second][next.first].first << ", " << p[next.second][next.first].second << ")";

				if (p[ny][nx] == yet) { // 빈땅
					Q.push(next);
					Union(curr, next);
					map_extend_cnt++;
					//cout << "빈땅 확장\n";
					this_year[ny][nx] = true;
				}
				else if (Find(curr) != Find(next)) {
					Union(curr, next); // 문명 접견
					cnt_CIV_meet++;
					
					if (cnt_CIV_meet == K) {
						if (this_year[ny][nx]) { cout << time_spend; }
						else { cout << time_spend - 1; }
						return 0;
					}
					//cout << "새 문명 접견\n";
					/*
					if (cnt[curr.second][curr.first] == map_extend_cnt) { // 모든 문명이 만남
						cout << time_spend;
						return 0;
					}*/
					
				}
				//cout << "모든 확장 : " << map_extend_cnt << " ["<< Find(curr).first << ", " << Find(curr).second << "] 문명 땅 : " << cnt[Find(curr).second][Find(curr).first] << "\n\n";
			}
		}
	}
}


//
// 3회
//만난 문명수가 아닌, 확장수==UNION수 로 
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> Pr;
int N, K;
int map_extend_cnt = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
Pr p[3000][3000];
int cnt[3000][3000];
bool this_year[3000][3000];
Pr yet = make_pair(0, 0);
int cnt_CIV_meet = 1;

Pr Find(Pr n)
{
	if (p[n.second][n.first] == n) { return n; }
	return p[n.second][n.first] = Find(p[n.second][n.first]);
}
void Union(Pr a, Pr b)
{
	Pr A = Find(a);
	Pr B = Find(b);
	if (A == B) { return; }
	//cout << " Union 됨 ";
	if (B == yet) {
		p[b.second][b.first] = A;
		cnt[A.second][A.first] += cnt[b.second][b.first]; // p[a] 문명의 땅 넓이 cnt
	}
	else {
		p[B.second][B.first] = A;
		cnt[A.second][A.first] += cnt[B.second][B.first]; // p[a] 문명의 땅 넓이 cnt
	}
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> K;
	fill(&p[0][0], &p[2999][2999], yet);
	fill(&cnt[0][0], &cnt[2999][2999], 1);
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
		fill(&this_year[0][0], &this_year[2999][2999], false);
		int Q_size = Q.size();
		for (int i = 0; i < Q_size; i++)
		{
			Pr curr = Q.front();
			Q.pop();
			for (int t = 0; t < 4; t++) {
				int nx = curr.first + dx[t];
				int ny = curr.second + dy[t];
				Pr next = make_pair(nx, ny);

				if (nx<1 || ny<1 || nx>N || ny>N || Find(curr) == Find(next)) { continue; } // 맵 벗어남, 같은 문명임

				if (p[ny][nx] == yet) { // 빈땅
					Q.push(next);
					Union(curr, next);
					map_extend_cnt++;
					this_year[ny][nx] = true;
				}
				else if (Find(curr) != Find(next)) {
					Union(curr, next); // 문명 접견
					cnt_CIV_meet++;
					if (cnt[Find(curr).second][Find(curr).first] == map_extend_cnt) { // 모든 문명이 만남
						if (this_year[ny][nx]) { cout << time_spend; }
						else { cout << time_spend - 1; }
						return 0;
					}

				}
			}
		}
	}
}
// 추후 재도전
