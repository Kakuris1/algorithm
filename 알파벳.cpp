#include<iostream>
#include<algorithm>
using namespace std;
int R, C; // 세로R 가로C
char board[20][20]; // 알파벳 보드 0~19
bool used[26];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int max_result = 0;

void dfs(int x, int y, int attempt)
{
	used[board[y][x] - 'A'] = true; // 알파벳 사용 기록

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || ny < 0 || C - 1 < nx || R - 1 < ny) { continue; } // 보드 판 벗어날 때, 방문했었을때
		if (used[board[ny][nx] - 'A'] == false) { dfs(nx, ny, attempt + 1); }
	}
	//방문 전으로 되돌림
	used[board[y][x] - 'A'] = false;

	max_result = max(max_result, attempt);
}

int main()
{
	cin >> R >> C;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> board[y][x];
		}
	}
	dfs(0, 0, 1);
	cout << max_result;
}



/* 시간 초과된 코드
#include<iostream>
#include<algorithm>
using namespace std;
int R, C; // 세로R 가로C
char board[20][20]; // 알파벳 보드 0~19
char check[27];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int max_result = 0;

void dfs(int x, int y, int attempt)
{
	check[attempt] = board[y][x]; // 알파벳 기록
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || ny < 0 || C - 1 < nx || R - 1 < ny) { continue; } // 보드 판 벗어날 때

		bool can_put = true; // 겹치는 알파벳 여부
		for (int j = 1; j <= attempt; j++) {
			if (board[ny][nx] == check[j]) { can_put = false; }
		}

		if (can_put) { dfs(nx, ny, attempt + 1); } // check은 초기화 되기에 따로 초기화 안해두 됨
	}
	max_result = max(max_result, attempt);
}

int main()
{
	cin >> R >> C;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> board[y][x];
		}
	}
	dfs(0, 0, 1);
	cout << max_result;
}
*/
