#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_V = 20000;
const int INF = 1000000000;
typedef pair<int, int> P;
int V, E, K; // V:정점 E:간선 K:시작점
vector<P> adj[MAX_V];


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> V >> E >> K;
	K--;
	for (int i = 0; i < E; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u - 1].push_back(P(v - 1, w));
	}

	int dist[MAX_V];
	fill(dist, dist + MAX_V, INF);
	bool visited[MAX_V] = { 0 };
	priority_queue<P, vector<P>, greater<P>> PQ;

	dist[K] = 0; // 시작점 0
	PQ.push(P(0, K)); // PQ 원소 : (K로부터 거리, 정점 번호)
	while (!PQ.empty())
	{
		int curr;
		do {
			curr = PQ.top().second;
			PQ.pop();
		} while (!PQ.empty() && visited[curr]); // curr가 방문한 정점이면 패스
		if (visited[curr]) break; // 모든 정점이 방문한 상태면 종료
		// 더 이상 방문할 수 있는 정점이 없으면 종료

		visited[curr] = true; //방문
		for (auto& p: adj[curr]) {
			int next = p.first, d = p.second;
			if (dist[next] > dist[curr] + d) {
				dist[next] = dist[curr] + d;
				PQ.push(P(dist[next], next));
			}
		}
	}

	for (int i = 0; i < V; i++) {
		if (dist[i] == INF) cout << "INF\n";
		else cout << dist[i] << "\n";
	}
}
