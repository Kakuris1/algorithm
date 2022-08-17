#include<iostream>
#include<queue>
using namespace std;

int N, K;
bool visited[100001];
int dx[3] = { -1,1,0 };

int main()
{
	cin >> N >> K;
	if (N == K) { cout << 0; return 0; }

	queue<int> Q;
	Q.push(N);
	visited[N] = true;
	int cnt = 0;
	while (!Q.empty())
	{
		int Qsize = Q.size();
		for (int Qfor = 0; Qfor < Qsize; Qfor++)
		{
			int curr = Q.front();
			Q.pop();
			for (int i = 0; i < 3; i++)
			{
				int nx = curr + dx[i];
				if (i == 2) { nx *= 2; }
				if (nx == K) { cout << cnt + 1; return 0; } // 한칸 전일때 탈출
				if (nx >= 0 && nx <= 100000 && visited[nx] == false) {
					Q.push(nx);
					visited[nx] = true;
				}
			}
		}
		cnt++;
	}
}
