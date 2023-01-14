#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int, int>P;
const int MAX_N = 800;
const int INF = 200000000;
int N, E;
vector<P>adj[MAX_N]; // (거리, 위치)

int Dijkstra(int s, int t)
{
	priority_queue<P, vector<P>, greater<P>> PQ; // PQ (거리, 위치)
	PQ.push(P(0, s));
	bool visited[MAX_N] = { 0, };

	int dist[MAX_N];
	fill(dist, dist + MAX_N, INF);
	dist[s] = 0;

	while (!PQ.empty())
	{
		int curr; // 현위치
		do {
			curr = PQ.top().second;
			PQ.pop();
		} while (!PQ.empty() && visited[curr]);
		if (visited[curr]) break;
		visited[curr] = true;

		for (int i = 0; i < adj[curr].size(); i++)
		{
			int next = adj[curr][i].second;
			int d = adj[curr][i].first;
			if (dist[next] > dist[curr] + d) {
				dist[next] = dist[curr] + d;
				PQ.push(P(dist[next], next));
			}
		}
	}
	return dist[t];
}

int main()
{
	cin >> N >> E;
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a - 1].push_back(P(c, b - 1));
		adj[b - 1].push_back(P(c, a - 1));
	}
	int v1, v2;
	cin >> v1 >> v2;
	v1--; v2--;
	// 1->v1 = A1 / v1->v2 = C / v2->N = A2 / 1->v2 = B1 / v1->N = B2
	int A1 = Dijkstra(0, v1);
	int A2 = Dijkstra(v2, N-1);
	int B1 = Dijkstra(0, v2);
	int B2 = Dijkstra(v1, N-1);
	int C = Dijkstra(v1, v2);
	if (A1 == INF || A2 == INF || B1 == INF || B2 == INF || C == INF) { 
		cout << -1; 
		return 0;
	}
	if (A1 + A2 > B1 + B2) { cout << B1 + B2 + C; }
	else { cout << A1 + A2 + C; }
}
