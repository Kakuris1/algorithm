#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

int T, F;
int p[200001];
map<string, int> person;	// 이름 -> n 번째 사람
map<int, int> cnt;			// n 번째 -> 친구 수


int find(int n)
{
	if (p[n] == n) return n;
	p[n] = find(p[n]);
	return p[n];
}

void Union(int f1, int f2)
{
	int a = find(f1);
	int b = find(f2);
	if (a == b) { return; }
	cnt[a] += cnt[b];
	p[b] = a;	//f1 그룹에 f2를 종속
	return;
}

int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--)
	{
		cin >> F;
		int friend_num = 0;
		person.clear(); cnt.clear();
		fill(p, p + 200001, 0);
		for (int i = 0; i < F; i++) {
			string tmp1, tmp2;
			cin >> tmp1;
			cin >> tmp2;
			if (person[tmp1] == 0) { // tmp1 이 처음 입력된 경우
				friend_num += 1;
				person[tmp1] = friend_num; // 번호 매기기
				cnt[friend_num] = 1;		// 친구수 = 1
				p[friend_num] = friend_num; // 부모 노드 = 자기자신
			}
			if (person[tmp2] == 0) { // tmp2 이 처음 입력된 경우
				friend_num += 1;
				person[tmp2] = friend_num; // 번호 매기기
				cnt[friend_num] = 1;		// 친구수 = 1
				p[friend_num] = friend_num; // 부모 노드 = 자기자신
			}
			Union(person[tmp1], person[tmp2]);
			cout << cnt[find(person[tmp1])] << "\n";
		}
	}
}
