//1회차
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N;
bool can_put[10][10];
int board[10][10];
int result_max_bishop = 0;

int tmp_cnt = 0;

void bishop(int x, int y, int cnt_bishop)
{
	//cout <<"\n"<< x << ", " << y << " :";
	if (can_put[y][x] == false) {
		//cout << "pass\n";
		if (x == N-1 && y == N-1) {
			result_max_bishop = max(result_max_bishop, cnt_bishop);
			//cout << "result : " << cnt_bishop;
			tmp_cnt++;
			//if (tmp_cnt == 30) { exit(0); }
		}
		else if (x == N-1) {
			bishop(0, y + 1, cnt_bishop);
		}
		else {
			bishop(x + 1, y, cnt_bishop);
		}
	}
	else if (can_put[y][x]) {
		//cout << "\n" << x << ", " << y << " :";
		vector<int> memo; // 메모
		for (int d = 1; d < N; d++) {
			if (can_put[y + d][x + d] && x + d < N && y + d < N) {
				can_put[y + d][x + d] = false;
				memo.push_back((x + d) * 10 + (y + d)); // xy 를 메모
			}
			if (can_put[y - d][x + d] && x + d < N && y - d >= 0) {
				can_put[y - d][x + d] = false;
				memo.push_back((x + d) * 10 + (y - d));
			}
			if (can_put[y + d][x - d] && x - d >= 0 && y + d < N) {
				can_put[y + d][x - d] = false;
				memo.push_back((x - d) * 10 + (y + d));
			}
			if (can_put[y - d][x - d] && x - d >= 0 && y - d >= 0) {
				can_put[y - d][x - d] = false;
				memo.push_back((x - d) * 10 + (y - d));
			}
		}
		//cout << " put\nmemo : ";
		//for (int v_size = 0; v_size < memo.size(); v_size++) { cout << memo[v_size] << ", "; }
		//cout << "\n";

		// x, y에 비숍을 놓고, 다음 시행
		if (x == N-1 && y == N-1) {
			result_max_bishop = max(result_max_bishop, cnt_bishop + 1);
			//cout << "result : " << cnt_bishop;
			tmp_cnt++;
			//if (tmp_cnt == 230) { exit(0); }
		}
		else if (x == N-1) {
			bishop(0, y + 1, cnt_bishop + 1);
		}
		else {
			bishop(x + 1, y, cnt_bishop + 1);
		}
		//cout << "\n" << x << ", " << y << " : 놓지 않음";
		//cout << "\n복구 : ";

		// 메모내용 복구
		for (int v_size = 0; v_size < memo.size(); v_size++)
		{
			//cout << memo[v_size] << ", ";
			int tmp_x = memo[v_size] / 10;
			int tmp_y = memo[v_size] % 10;

			can_put[tmp_y][tmp_x] = true;
		}
		//cout << "\n";

		// x, y에 비숍을 놓지 않고, 다음 시행
		if (x == N-1 && y == N - 1) {
			result_max_bishop = max(result_max_bishop, cnt_bishop);
		}
		else if (x == N - 1) {
			bishop(0, y + 1, cnt_bishop);
		}
		else {
			bishop(x + 1, y, cnt_bishop);
		}
	}
}

int main()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
			if (board[y][x] == 1) { can_put[y][x] = true; }
		}
	}

	bishop(0, 0, 0);
	cout << result_max_bishop;
}
//
