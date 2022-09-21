#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int, int>P;
P N[1000];
bool done[1000];
int longest_period = 0;
int n;
int total_score = 0;

bool cmp(P& a, P& b)
{
	if (a.second == b.second)
		return a.first > b.first;
	return a.second > b.second;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> N[i].first >> N[i].second;
		if (N[i].first > longest_period) { longest_period = N[i].first; }
	}
	sort(N, N + n, cmp);

	for (int t = longest_period; t > 0; t--)
	{
		for (int i = 0; i < n; i++)
		{
			if (done[i] || N[i].first < t) { continue; } // 이미 한 과제 / 기한이 지난 과제
			total_score += N[i].second;
			done[i] = true;
			break;
		}
	}
	cout << total_score;
}
