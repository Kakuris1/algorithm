#include<iostream>
#include<cstdlib>
using namespace std;

int N, cnt;
int Queen[15];

void dfs(int x, int y)
{
	if (y == N) { cnt++; return; }
	Queen[y] = x;
	for (int next_x = 1; next_x <= N; next_x++)
	{
		bool can_put = true;
		for (int pre_y = 1; pre_y <= y; pre_y++)
		{
			if (next_x == Queen[pre_y] || abs(next_x - Queen[pre_y]) == y + 1 - pre_y) {
				can_put = false;
			}
		}
		if(can_put){ dfs(next_x, y + 1); }
	}
}

int main()
{
	cin >> N;
	cnt = 0;
	for (int i = 1; i <= N; i++) {
		dfs(i, 1);
	}
	cout << cnt;
}
