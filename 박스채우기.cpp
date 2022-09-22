#include<iostream>
#include<algorithm>
using namespace std;

int length, width, height;//length, width, height
int n; // 큐브 종류 수
int cube[20]; // 종류별 큐브 개수
bool filled;

int Answer(int x, int y, int z, int l, int w, int h)
{
	if (x == l || y == w || z == h) { return 0; } // 못 채움
	
	for (int i = 19; i >= 0; i--) {
		int cube_size = (1 << i); // 시프트 연산 -> 2의 거듭제곱
		if (cube[i] == 0 || x + cube_size > l || y + cube_size > w || z + cube_size > h) { continue; } // 갯수부족 or 크기 초과

		cube[i]--; filled = true;
		return Answer(x + cube_size, y, z, l, y + cube_size, z + cube_size)
			+ Answer(x, y + cube_size, z, x + cube_size, w, z + cube_size)
			+ Answer(x, y, z + cube_size, x + cube_size, y + cube_size, h)
			+ Answer(x + cube_size, y + cube_size, z, l, w, z + cube_size)
			+ Answer(x, y + cube_size, z + cube_size, x + cube_size, w, h)
			+ Answer(x + cube_size, y, z + cube_size, l, y + cube_size, h)
			+ Answer(x + cube_size, y + cube_size, z + cube_size, l, w, h)
			+ 1;
	}
	filled = false;
	return 0;
}

int main()
{
	cin >> length >> width >> height;
	cin >> n;
	int j;
	for (int i = 0; i < n; i++) { cin >> j; cin >> cube[j]; }

	int ans = Answer(0, 0, 0, length, width, height);
	if (!filled) { cout << -1; }
	else { cout << ans; }
}
