#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int N;
pair<int, int>I[200000];
priority_queue<int, vector<int>, greater<int>> room_time;

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> I[i].first >> I[i].second; // 시작시간 first, 끝나는 시간 second
	}
	sort(I, I + N);
  
	room_time.push(0);
	for (int i = 0; i < N; i++) {
		if (room_time.top() <= I[i].first) {
			room_time.pop();
		}
		room_time.push(I[i].second);
	}
	cout << room_time.size();
}
