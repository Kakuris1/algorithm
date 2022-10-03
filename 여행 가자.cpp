#include<iostream>
#include<algorithm>
using namespace std;
int N, M;
int p[201];

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
	for (int i = 0; i < 201; i++) {
		p[i] = i;
	}
	cin >> N >> M;
	int tmp;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> tmp;
			if (i > j) { continue; } // 중복 제거
			if (tmp == 0) { continue; }
			Union(i, j);
		}
	}

	int tmp1, tmp2;
	cin >> tmp1;
	for (int i = 1; i < M; i++) {
		cin >> tmp2;
		if (find(tmp1) != find(tmp2)) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
}
