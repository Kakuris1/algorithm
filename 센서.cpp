#include<iostream>
#include<algorithm>
using namespace std;

int N, K;
int sensor[10000];
int dis[10000];

bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	cin >> N >> K;
	for (int i = 0; i < N; i++) { cin >> sensor[i]; }
	sort(sensor, sensor + N);

	for (int i = 0; i < N-1; i++) { dis[i] = sensor[i+1] - sensor[i]; }
	sort(dis, dis + N - 1, cmp);
	int sum = 0;
	for (int i = 0; i < K - 1; i++) { sum += dis[i];}
	cout << sensor[N - 1] - sensor[0] - sum;
}
