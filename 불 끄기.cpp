#include<iostream>
#include<algorithm>
using namespace std;
bool light[11][11];
int dx[5] = { 0,0,0,1,-1 };
int dy[5] = { 0,1,-1,0,0 };
void switch_on(int x, int y);
void turn_light(int x, int y);
int min_result = 101;

void back_tracking(int x, int y, int click_cnt)
{
	if (x == 11) { x = 1; y = y + 1; } // 아랫 줄 이동
	if (y == 11) {  // 마지막줄 완성되었는지 확인 후 완료
		for (int i = 1; i <= 10; i++) {
			if (light[10][i]) { return; } // 남아 있는 전구가 있으면 되돌아감
		}
		min_result = min(click_cnt, min_result);
		return;
	}
	
	if(y==1) {
		// 안 누름
		back_tracking(x + 1, y, click_cnt);
		// 누름
		switch_on(x, y);
		back_tracking(x + 1, y, click_cnt + 1);
		switch_on(x, y); // 복구
	}
	else {
		if (light[y - 1][x] == true) { // 윗칸이 켜져있으면
			// 스위치 누름
			switch_on(x, y);
			back_tracking(x + 1, y, click_cnt + 1);
			switch_on(x, y); // 복구
		}
		else { // 윗칸이 꺼져있으면
			// 안 누름
			back_tracking(x + 1, y, click_cnt);
		}
	}
	return;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	char tmp;
	for (int y = 1; y <= 10; y++) {
		for (int x = 1; x <= 10; x++) {
			cin >> tmp;
			if (tmp == 'O') { light[y][x] = true; }
		}
	}
	back_tracking(1, 1, 0);
	if (min_result == 101) { cout << -1; }
	else{ cout << min_result; }
}

void turn_light(int x, int y)
{
	if (light[y][x]) { light[y][x] = false; }
	else { light[y][x] = true; }
}

void switch_on(int x, int y)
{
	for (int i = 0; i < 5; i++) { // 전구 on/off
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx>10 || ny>10) { continue; } //범위 벗어나면 패스
		turn_light(nx, ny); // 전구 상태 바꿈
	}
}
