// 3회차 set lower_bound 활용 
#include<iostream>
#include<set>
using namespace std;
int Gate_num, Plane_num;
int g[100001];
set<int, greater<int>> doke_yet;
int doke_cnt = 0;

int main()
{
	cin >> Gate_num >> Plane_num;
	for (int i = 0; i < Plane_num; i++) { cin >> g[i]; }
	for (int i = 1; i <= Gate_num; i++) { doke_yet.insert(i); }

	set<int>::iterator iter;
	for (int i = 0; i < Plane_num; i++){
		iter = doke_yet.lower_bound(g[i]);
		if (iter != doke_yet.end()) {
			cout << *iter << "에 도킹\n";
			doke_yet.erase(iter);
			doke_cnt++; // 도킹 수 +1
		}
		else { break; }
	}
	cout << doke_cnt;
}

/* 1회차 시간복잡도 O(N*N)  
#include<iostream>
using namespace std;
int Gate_num, Plane_num;
int g[100001];
bool already_doking[100001];
int doke_cnt = 0;

int main()
{
	cin >> Gate_num >> Plane_num;
	for (int i = 0; i < Plane_num; i++)
	{
		cin >> g[i];
	}
	for (int i = 0; i < Plane_num; i++)
	{
		bool can_doke = false;
		for (int put = g[i]; put >= 1; put--)
		{
			if (already_doking[put]) { continue; }
			already_doking[put] = true;
			can_doke = true;
			doke_cnt++;
			break;
		}
		if (!can_doke) { cout << doke_cnt; break; }
	}
}
*/

/* 2회차 set 활용 풀이
#include<iostream>
#include<set>
using namespace std;
int Gate_num, Plane_num;
int g[100001];
set<int> doke_yet;
int doke_cnt = 0;

int main()
{
	cin >> Gate_num >> Plane_num;
	for (int i = 0; i < Plane_num; i++)
	{
		cin >> g[i];
	}
	set<int>::iterator iter;
	set<int>::reverse_iterator r_iter;
	for (int i = 0; i < Plane_num; i++)
	{
		cout << i + 1 << "번째 비행기가 찾는중 : ";
		if (*doke_yet.begin() > g[i]) { break; } //g[i] 보다 낮은 게이트가 없으면 종료

		iter = doke_yet.find(g[i]);
		if (iter != doke_yet.end()) { // g[i] 게이트가 있을 경우
			doke_yet.erase(iter); // 게이트 도킹 , 지움
		}
		else { // 없을경우
			if (doke_yet.size() == 1) { doke_yet.erase(doke_yet.begin()); }
			doke_yet.insert(g[i]);
			for (iter = doke_yet.find(g[i]); iter != doke_yet.begin(); iter--) {
				if (*iter < g[i]) { doke_yet.erase(iter); }
			}
		}
		doke_cnt++; // 도킹 수 +1
	}
	cout << doke_cnt;
}
*/
