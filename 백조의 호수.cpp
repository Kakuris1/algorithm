#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> Pr;
int R, C; // 세로,가로
Pr P[1501][1501];
Pr ice = make_pair(-1, -1);
queue<Pr>Q;
Pr Swan[2];
bool first_swan = true;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

Pr Find(Pr n)
{
	if (P[n.second][n.first] == ice) { return n; } // 얼음이면 자기자신 리턴
	if (P[n.second][n.first] == n) { return n; }
	return P[n.second][n.first] = Find(P[n.second][n.first]);
}
void Union(Pr a, Pr b)
{
	Pr A = Find(a);
	Pr B = Find(b);
	if (A == B) { return; }
	P[B.second][B.first] = A;
	return;
}

int main()
{
	cin >> R >> C;
	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			char c;
			cin >> c;
			if (c == 'X') { P[y][x] = ice; }
			else {
				Pr input = make_pair(x, y);
				P[y][x] = input;
				Q.push(input);
				if (c == 'L') {
					if (first_swan) { Swan[0] = input; first_swan = false; }
					else { Swan[1] = input; }
				}
			}
		}
	}

	int day_cnt = 0;
	while (true)
	{
		int Q_size = Q.size();
		queue<Pr>Q_tmp = Q;
		for (int Qfor = 0; Qfor < Q_size; Qfor++)
		{
			Pr curr = Q_tmp.front();
			Q_tmp.pop();
			for (int i = 0; i < 4; i++)
			{
				int nx = curr.first + dx[i];
				int ny = curr.second + dy[i];
				Pr next = make_pair(nx, ny);
				if (nx<1 || ny<1 || nx>C || ny>R) { continue; }
				if (P[ny][nx] != ice) { Union(curr, next); }
			}
		}

		if (Find(Swan[0]) == Find(Swan[1])) { cout << day_cnt; return 0; }// 두 백조가 같은 물 그룹에 속함

		for (int Qfor = 0; Qfor < Q_size; Qfor++)
		{
			Pr curr = Q.front();
			Q.pop();
			for (int i = 0; i < 4; i++)
			{
				int nx = curr.first + dx[i];
				int ny = curr.second + dy[i];
				Pr next = make_pair(nx, ny);
				if (nx<1 || ny<1 || nx>C || ny>R) { continue; }

				if (P[ny][nx] == ice) {
					Q.push(next);
					Union(curr, next);
				}
			}
		}
		day_cnt++;
	}
}
