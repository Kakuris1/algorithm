#include<iostream>
#include<queue>
#include<algorithm>
#include<tuple>
using namespace std;
typedef tuple<int, int, int> T;
int p, w, c, v;

struct cmp {
	bool operator()(T& a, T& b) {
		if (get<2>(a) == get<2>(b)) {
			return get<0>(a) > get<0>(b);
		}
		else {
			return get<2>(a) < get<2>(b);
		}
	}
};
priority_queue<T, vector<T>, cmp> Q;

int parent[1001];
int Find(int n)
{
	if (parent[n] == n) { return n; }
	return parent[n] = Find(parent[n]);
}
void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a == b) { return; }
	parent[b] = a;
	return;
}

int main()
{
	for (int i = 1; i <= 1000; i++) { parent[i] = i; }
	cin >> p >> w; // 노드 p 간선 w
	cin >> c >> v; // 출발 c 도착 v
	while (w--)
	{
		int W_start, W_end, W_width;
		cin >> W_start >> W_end >> W_width;
		Q.push(make_tuple(W_start, W_end, W_width));
	}
	while (!Q.empty())
	{
		cout << get<2>(Q.top()) << " 너비의 길\n";
		Union(get<0>(Q.top()), get<1>(Q.top()));
		if (Find(c) == Find(v)) {
			cout << get<2>(Q.top());
			return 0;
		}
		Q.pop();
	}
}
