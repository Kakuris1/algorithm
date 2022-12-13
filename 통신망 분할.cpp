#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> Pr;
int N, M, Q;
Pr Edge[100001];
int P[100001];
bool Remove[100001];
int sequence[100001];
int cnt_size[100001];
int Total_cost = 0;

int Find(int n)
{
	if (P[n] == n) { return n; }
	return P[n] = Find(P[n]);
}
void Union(Pr n)
{
	int A = Find(n.first);
	int B = Find(n.second);
	if (A == B) { return; }
	P[B] = A;
	cnt_size[A] += cnt_size[B];
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	fill(cnt_size, cnt_size + 100001, 1); // cnt_size 초기화
	cin >> N >> M >> Q;
	for (int i = 1; i <= M; i++){
		P[i] = i;							// P 초기화
		int X, Y;
		cin >> X >> Y;
		Edge[i] = make_pair(X, Y);
	}

	for (int i = 1; i <= Q; i++) {
		int tmp;
		cin >> tmp;
		sequence[i] = tmp;
		Remove[tmp] = true;
	}

	for (int i = 1; i <= M; i++) {
		if (!Remove[i]) { Union(Edge[i]); }
	}

	for (int i = Q; i >= 1; i--) {
		if (Find(Edge[sequence[i]].first) != Find(Edge[sequence[i]].second)) { // 다른 그룹이면
			Total_cost += cnt_size[Find(Edge[sequence[i]].first)] * cnt_size[Find(Edge[sequence[i]].second)];
		}
		Union(Edge[sequence[i]]);
	}

	cout << Total_cost;
}
/* 오답 내역
*  1. 55번줄 cnt_size[] 놓침
*  2. Total_cost 자료형 int -> long long 
*/
