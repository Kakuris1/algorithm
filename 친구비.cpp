#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int p[10001];
int N, M, K;
int f_cost[10001];
priority_queue<int, vector<int>, greater<int>>Q[10001]; // 작은것 부터 출력

int find(int n)
{
	if (p[n] == n) { return n; }
	p[n] = find(p[n]);
	return p[n];
}

void Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b) { return; }
	p[b] = a;
	return;
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) { p[i] = i; }
	for (int i = 1; i <= N; i++) { cin >> f_cost[i]; }
	for (int i = 1; i <= M; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		Union(min(tmp1, tmp2), max(tmp1, tmp2));
	}

	for (int i = 1; i <= N; i++) { 
		find(i);	// p[i]가 항상 루트노드를 가리키고 있는건 아니므로, find(i)를 한번씩 시행해줌
		Q[p[i]].push(f_cost[i]);
	}
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		if (Q[i].empty()) { continue; }
		sum+=Q[i].top();
	}
	if (sum <= K) { cout << sum; }
	else { cout << "Oh no"; }
}
