#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int N; // N*N 공간
int map[20][20];
bool visited[20][20];
pair<int, int>shark_start;
int babyshark_size = 2;
int babyshark_eat_history = 0;
int total_move = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int attempt = 1;

int Baby_Shark(pair<int,int>start)
{
	fill(&visited[0][0], &visited[19][20], false); // 방문 초기화
	queue<pair<int, int>>Q;
	Q.push(make_pair(start.first, start.second));
	visited[start.second][start.first] = true;

	int distance = 0; // 아기상어에서의 거리
	while (!Q.empty())
	{
		priority_queue<int, vector<int>, greater<int> >can_eat; // 이번 레벨(거리)에서 먹을 수 있는 물고기 좌표 (y*100 + x)
		int Qsize = Q.size();
		for (int Qfor = 0; Qfor < Qsize; Qfor++) 
		{
			pair<int, int>curr = Q.front(); // 현 위치
			Q.pop();
			for (int i = 0; i < 4; i++)
			{
				int next_x = curr.first + dx[i];
				int next_y = curr.second + dy[i];
				if (next_x < 0 || next_y < 0 || next_x >= N || next_y >= N || visited[next_y][next_x]) { continue; } // 맵 벗어남

				if (map[next_y][next_x] > babyshark_size) { continue; } // 물고기가 더 크면 못지나감

				if (map[next_y][next_x] == 0 || map[next_y][next_x] == babyshark_size) {	// 빈칸 이동
					Q.push(make_pair(next_x, next_y));
					visited[next_y][next_x] = true;
					continue;
				}

				if (map[next_y][next_x] < babyshark_size) { // 먹을 수 있는 물고기 발견
					can_eat.push(next_y * 100 + next_x);
				}
			}
		}
		distance++;

		if(!can_eat.empty()){ // 이번 레벨에 먹을 수 있는 물고기가 있다면
			int next_x = can_eat.top() % 100;
			int next_y = can_eat.top() / 100;
			// 상어 먹이, 성장 계산
			map[next_y][next_x] = 0; // 먹어서 없어짐 (이부분 두번틀림)
			babyshark_eat_history++;
			if (babyshark_size == babyshark_eat_history) { // 크기만큼 먹음
				babyshark_size++; // 성장
				babyshark_eat_history = 0;
			}
			// 이동거리 계산
			total_move += distance;

			// 다음 먹이 찾아 떠남
			Baby_Shark(make_pair(next_x, next_y));
		}
	}
	cout << total_move;
	exit(0);
}

int main()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 9) { shark_start = make_pair(x, y); map[y][x] = 0; }
		}
	}
	Baby_Shark(shark_start);
}
