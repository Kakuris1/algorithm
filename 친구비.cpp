#include<iostream>
using namespace std;
int p[10001];
int N, M, K;
int f_cost[10001];

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
	for (int i = 1; i <= N; i++) { cin >> f_cost[i]; }
	for (int i = 1; i <= M; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
	}
}
