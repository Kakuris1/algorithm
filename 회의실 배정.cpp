#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N;
pair<int, int>I[100000];
int curr_time = 0;
int conference_cnt = 0;

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> I[i].second >> I[i].first; // 시작시간 sec, 끝나는 시간 first
	}
	sort(I, I+N);
	for (int i = 0; i < N; i++) {
		if (I[i].second >= curr_time) {
			conference_cnt++;
			curr_time = I[i].first;
		}
	}
	cout << conference_cnt;
}
