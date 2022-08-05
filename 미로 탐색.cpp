#include<iostream>
#include<algorithm>
#include<utility>
#include<queue>
#include<vector>
using namespace std;

vector<vector<int>> adj;
vector<vector<bool>>visited(101, vector<bool>(101, false));
int N, M;
char map[101][101];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int bfs()
{
	queue<pair<int,int>>Q;
	pair<int, int>p;
	p.first = 1;
	p.second = 1;
	Q.push(p);
	visited[1][1] = true;

	int dis = 0;
	while (!Q.empty())
	{
		int Qsize = Q.size();
		for (int i = 0; i < Qsize; i++)
		{
			pair<int, int> curr = Q.front();
			if (curr.first == M && curr.second == N) { return dis++; }
			Q.pop();
			for (int j = 0; j < 4; j++)
			{
				int nx = curr.first + dx[j];
				int ny = curr.second + dy[j];
				if (nx > 0 && nx <= 100 && ny > 0 && ny <= 100) {
					if (map[ny][nx] == '1' && visited[ny][nx] == false) {
						visited[ny][nx] = true;
						p.first = nx;
						p.second = ny;
						Q.push(p);
					}
				}
			}
		}
		dis++;
	}
}


int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> map[i][j];
	cout << bfs()+1;
}
