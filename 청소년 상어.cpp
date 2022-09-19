#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int, int> P;
pair<int, int> fish_pos[17]; // 물고기 위치 0=상어 1~16번은 물고기
int direction[17]; // 물고기 방향
bool fish_dead[17];
int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
void swap(int a, int b);
int result_max_value = 0;

void Boy_Shark(int eat_num_sum)
{
	//물고기 이동
	for (int fish_num = 1; fish_num <= 16; fish_num++) {
		if (fish_dead[fish_num]) { continue; }// 이미 먹혔으면 패스
		while (true)
		{
			int next_x = fish_pos[fish_num].first + dx[direction[fish_num]];
			int next_y = fish_pos[fish_num].second + dy[direction[fish_num]];
			//공간을 벗어나거나, 상어가 있을때
			if (next_x < 0 || next_y < 0 || next_x>3 || next_y>3 || fish_pos[0] == make_pair(next_x, next_y)) { 
				direction[fish_num]++;	// 45도 회전/ 방향 전환
				if (direction[fish_num] > 8) { direction[fish_num] = 1; }
				continue; 
			}
			//위치 이동 (물고기 교환)
			int next_fish;
			for (int i = 1; i <= 16; i++) {
				if (fish_pos[i] == make_pair(next_x, next_y)) { next_fish = i; }
			}
			swap(fish_num, next_fish);

			break;
		}
	}

	//상어 이동 전 상황 메모
	P memo_fish_pos[17];
	int memo_direction[17];
	for (int i = 0; i <= 16; i++) { memo_fish_pos[i] = fish_pos[i]; memo_direction[i] = direction[i]; }
	
	//상어 이동
	bool can_move = false;
	for (int move_cnt = 1; move_cnt < 4; move_cnt++)
	{
		int next_x = fish_pos[0].first + move_cnt * dx[direction[0]];
		int next_y = fish_pos[0].second + move_cnt * dy[direction[0]];

		// 맵을 벗어나서는 이동 못함
		if (next_x < 0 || next_y < 0 || next_x>3 || next_y>3) { continue; }

		// 이미 먹은 물고기면 못먹음
		int next_fish=0;
		for (int i = 1; i <= 16; i++) {
			if (fish_pos[i] == make_pair(next_x, next_y)) { next_fish = i; }
		}
		if (fish_dead[next_fish]) { continue; }

		// 상어 방향 바꿈
		direction[0] = direction[next_fish];
		fish_dead[next_fish] = true;
		swap(0, next_fish); // 상어 위치 이동

		Boy_Shark(eat_num_sum + next_fish); // 먹은 물고기

		for (int i = 0; i <= 16; i++) { 
			fish_pos[i] = memo_fish_pos[i]; // 물고기들 + 상어 위치 복구
			direction[i] = memo_direction[i]; // 물고기들 + 상어 방향 복구
		}
		fish_dead[next_fish] = false;

		// 한번이라도 이동하면 true
		can_move = true;
	}
	//한번도 이동 못하면 완료, 최댓값일시 값 갱신
	if (!can_move) { result_max_value = max(eat_num_sum, result_max_value); }
}

int main()
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int tmp = 0;
			cin >> tmp;
			cin >> direction[tmp];
			fish_pos[tmp] = make_pair(x, y);
		}
	}

	int first_fish;
	for (int i = 1; i <= 16; i++) {
		if (fish_pos[i] == make_pair(0, 0)) { first_fish = i; }
	}
	fish_pos[0] = make_pair(0, 0); // 시작 좌표
	fish_pos[first_fish] = make_pair(-1, -1); // 첫 물고기 좌표 제외
	direction[0] = direction[first_fish]; // 시작 방향
	fish_dead[first_fish] = true; // 첫 물고기 먹힘 처리

	Boy_Shark(first_fish);

	cout << result_max_value;
}

void swap(int a, int b)
{
	P tmp;
	tmp = fish_pos[a];
	fish_pos[a] = fish_pos[b];
	fish_pos[b] = tmp;
}

/*
놓친 부분
- 상어 출발점에 안놓음 (시작좌표, 시작방향 설정)
- 상어 이동 후 함수 탈출 후 다시 복구할때, 상어만 복구하고 물고기 복구하는 것 생각못함 (전역함수로 설정 된 값들이라 계속 바뀜)
- 물고기 이동에서 물고기 좌표, 방향이 바뀜 / 상어 이동에서 상어 좌표, 방향이 바뀜
 ㄴ 이것들을 한번에 메모해둔걸 복구하면 되는데, 코드가 복잡해져 
*/
