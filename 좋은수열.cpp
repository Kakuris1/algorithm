#include<iostream>
#include<algorithm>
using namespace std;
int N;
int Sequence[80];

int choose_next(int curr, int value)
{
	Sequence[curr] = value;
	if (curr == N - 1) {
		for (int i = 0; i < N; i++) { cout << Sequence[i]; }
		exit(0);
	}
	for (int next_value = 1; next_value <= 3; next_value++)
	{
		if (next_value == value) { continue; } // 연속한 두 숫자는 패스
		bool can_put = true;
		for (int i = 1; i < (curr + 2) / 2; i++) 
		{
			int sum_A = 0;
			int sum_B = 0; 
			int A = curr + 1;
			int B = curr - i;
			Sequence[A] = next_value;

			int d = 1;
			for (int j = 0; j <= i; j++)
			{
				sum_A += d*Sequence[A - j];
				sum_B += d*Sequence[B - j];
				d *= 10;
			}
			if (sum_A == sum_B) { can_put = false; break; }
		}
		if (can_put) { choose_next(curr + 1, next_value); }
	}
}

int main()
{
	cin >> N;
	choose_next(0, 1);
}
