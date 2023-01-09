#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> P;
const int MAX_N = 1000;
const int INF = 1000000000;
int N, M;
vector<P> adj[MAX_N];// 도착점, 거리

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b, dis;
		cin >> a >> b >> dis;
		adj[a - 1].push_back(P(b-1, dis));
	}
	int start, end;
	cin >> start >> end;
	start--; end--;

	int dist[MAX_N];
	fill(dist, dist + MAX_N, INF);
	bool visited[MAX_N] = { 0, };
	priority_queue<P, vector<P>, greater<P>> PQ;

	dist[start] = 0;
	PQ.push(P(start, 0));
	while (!PQ.empty())
	{
		int curr;
		do {
			curr = PQ.top().first;
			PQ.pop();
		} while (!PQ.empty() && visited[curr]);
		if (visited[curr])break;
		visited[curr] = true;
		//cout << "현위치 : " << curr << endl;

		for (int i = 0; i < adj[curr].size(); i++) {
			int next = adj[curr][i].first, d = adj[curr][i].second;
			//cout << "next : " << next << " dist : " << d;
			//cout << " 기존 : " << dist[next]<<endl;
			if (dist[next] > dist[curr] + d) {
				dist[next] = dist[curr] + d;
				PQ.push(P(next, dist[next]));
				//cout << "갱신 : " << dist[next] << endl;
			}
		}
		cout << endl;
	}
	cout << dist[end];
}
