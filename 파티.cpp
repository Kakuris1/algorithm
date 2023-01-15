#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int, int> P;
const int INF = 100000;
const int MAX_N = 1000;
int N, M, X;
vector<P> adj[MAX_N]; // (거리, 위치)
vector<P> adj_reverse[MAX_N];

int main()
{
	cin >> N >> M >> X;
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a - 1].push_back(P(c, b - 1));
		adj_reverse[b - 1].push_back(P(c, a - 1));
	}

	// X에서 집으로 돌아가는 최단 거리
	priority_queue<P, vector<P>, greater<P>> PQ; //(거리, 위치)
	bool visited[MAX_N] = { 0, };

	PQ.push(P(0, X - 1));
	int dist_comeback[MAX_N];
	fill(dist_comeback, dist_comeback + MAX_N, INF);
	dist_comeback[X - 1] = 0;
	while (!PQ.empty())
	{
		int curr;
		do
		{
			curr = PQ.top().second;
			PQ.pop();
		} while (!PQ.empty()&&visited[curr]);
		if (visited[curr]) break;

		for (int i = 0; i < adj[curr].size(); i++) {
			int next = adj[curr][i].second;
			int d = adj[curr][i].first;
			if (dist_comeback[next] > dist_comeback[curr] + d) {
				dist_comeback[next] = dist_comeback[curr] + d;
				PQ.push(P(dist_comeback[next], next));
			}
		}
	}
	// 집에서 X까지 가는 최단거리
	fill(visited, visited + MAX_N, false);
	PQ.push(P(0, X - 1));
	int dist_go[MAX_N];
	fill(dist_go, dist_go + MAX_N, INF);
	dist_go[X - 1] = 0;
	while (!PQ.empty())
	{
		int curr;
		do
		{
			curr = PQ.top().second;
			PQ.pop();
		} while (!PQ.empty() && visited[curr]);
		if (visited[curr]) break;

		for (int i = 0; i < adj_reverse[curr].size(); i++) {
			int next = adj_reverse[curr][i].second;
			int d = adj_reverse[curr][i].first;
			if (dist_go[next] > dist_go[curr] + d) {
				dist_go[next] = dist_go[curr] + d;
				PQ.push(P(dist_go[next], next));
			}
		}
	}
  
	int result = 0;
	for (int i = 0; i < N; i++) {
		
		if (dist_go[i] + dist_comeback[i] > result) { result = dist_go[i] + dist_comeback[i]; }
	}
	cout << result;
}
