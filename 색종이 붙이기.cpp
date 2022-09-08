#include<iostream>
#include<algorithm>
using namespace std;

int paper[10][10];
int cnt_use_paper[6] = { 0, };
int result_min_value = 26;
int call_cnt = 0;

int can_attach(int x, int y)
{
	// 1x1 만 가능
	if (9 <= x || 9 <= y) { return 1; } 
	// 2x2 가능한지
	for (int i = y; i <= y + 1; i++) {
		for (int j = x; j <= x + 1; j++) {
			if (paper[i][j] == 0) { return 1; }
		}
	}
	// 2x2 만 가능
	if (8 <= x || 8 <= y) { return 2; }
	// 3x3 가능한지
	for (int i = y; i <= y + 2; i++) {
		for (int j = x; j <= x + 2; j++) {
			if (paper[i][j] == 0) { return 2; }
		}
	}
	// 3x3 만 가능
	if (7 <= x || 7 <= y) { return 3; }
	// 4x4 가능한지
	for (int i = y; i <= y + 3; i++) {
		for (int j = x; j <= x + 3; j++) {
			if (paper[i][j] == 0) { return 3; }
		}
	}

	// 4x4 만 가능
	if (6 <= x || 6 <= y) { return 4; }
	// 5x5 가능한지
	for (int i = y; i <= y + 4; i++) {
		for (int j = x; j <= x + 4; j++) {
			if (paper[i][j] == 0) { return 4; }
		}
	}

	// 5x5까지 가능
	return 5;
}

void attach(int x, int y)
{
	call_cnt++;
	if (paper[y][x] == 1) {		// 1이 있으면
		int can_attach_cnt = can_attach(x, y); // 종이 붙일 수 있는 종류 계산
		for (int i = can_attach_cnt; i >= 1; i--) // 큰 종이부터 가장 작은 종이까지 시행
		{
			for (int a = 0; a < i; a++) {
				for (int b = 0; b < i; b++) {
					paper[y + a][x + b] = 0;		// 붙였으면 0으로 바꾸기
				}
			}
			cnt_use_paper[i]++;						// 붙인 종이 수 카운트++

			if (cnt_use_paper[i] > 5) {}//cout << "over\n"; } // 한 종류를 5개 이상 사용시 패스
			else 
			{
				if (x == 9 && y == 9) { // 9, 9 도착했을 경우 종료시키기
					int sum = 0;
					for (int t = 1; t <= 5; t++) {
						sum += cnt_use_paper[t];	// 사용한 종이 수 합
					}
					result_min_value = min(result_min_value, sum); // 최소 일 경우 결과값 최신화
				}
				else if (x == 9) {	// x가9일때 다음줄로
					attach(0, y + 1);
				}
				else {				// 다음칸으로
					attach(x + 1, y);
				}
			}

			// 이전상태로 복구
			for (int a = 0; a < i; a++) {
				for (int b = 0; b < i; b++) {
					paper[y + a][x + b] = 1;
				}
			}
			cnt_use_paper[i]--;
		}
	}
	else
	{
		if (x == 9 && y == 9) { // 9, 9 도착했을 경우 종료시키기
			int sum = 0;
			for (int t = 1; t <= 5; t++) {
				sum += cnt_use_paper[t];	// 사용한 종이 수 합
			}
			result_min_value = min(result_min_value, sum); // 최소 일 경우 결과값 최신화
		}
		else if (x == 9) {	// x가9일때 다음줄로
			attach(0, y + 1);
		}
		else {				// 다음칸으로
			attach(x + 1, y);
		}
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			cin >> paper[i][j];
	attach(0, 0);
	if (result_min_value == 26) { cout << -1; }
	else{ cout << result_min_value; }
}
