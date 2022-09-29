#include<iostream>
#include<algorithm>
using namespace std;
int n, m;
int p[1000001];

int find(int n)
{
	if (p[n] < 0) return n; // 루트 노드이면 그대로 리턴
	p[n] = find(p[n]); // 부모 노드를 루트로 변경
	return p[n]; // 루트 노드 리턴
}

void union_f(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b) return; // 같은 집합이면 그냥 리턴
	p[b] = a; // 다른 집합이면 a가 포함된 집합의 루트노드를, b가 포함된 집합 루트노드의 부모노드로 (합집합)
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	fill(p, p + 1000001, -1);
	cin >> n >> m;
	while (m--)
	{
		int cal, a, b;
		cin >> cal >> a >> b;
		if (cal == 0) {
			union_f(a, b);
		}
		else if (cal == 1) {
			int tmp1 = find(a);
			int tmp2 = find(b);
			if (tmp1 == tmp2) { cout << "YES\n"; }
			else { cout << "NO\n"; }
		}
	}
}
