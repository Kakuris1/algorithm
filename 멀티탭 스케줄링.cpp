#include<iostream>
#include<algorithm>
using namespace std;
int N, K;
int use[100];
int plug[100];
int cnt_change_plug = 0;

int main()
{
	cin >> N >> K;
	for (int i = 0; i < K; i++) { cin >> use[i]; }

	// 빈 플러그에 그냥 꽂고, 꽂힌 것 중에 사용할 것이 있으면 넘김
	bool full = false;
	int used = 0;
	for (int i = 0; i < K; i++) { 
		for (int put = 0; put < N; put++)
		{
			if (plug[put] == 0) { 
				plug[put] = use[i];
				if (put == N - 1) { full = true; used = i; }
			}
			if (plug[put] == use[i]) { break; }
		}
		if (full) { break; }
	}

	// 그 이후 플러그를 뽑아야하는지 체크
	for (int p = used; p < K; p++) {
		//이미 필요한 용품이 꽂혀 있으면 뽑지 않고 pass
		bool already_in = false;
		for (int i = 0; i < N; i++) {
			if (use[p] == plug[i]) { already_in = true; break; }
		}
		if (already_in) { continue; }

		//뽑아야할 경우
		int memo_max_dis = 0;
		int memo_farthest_plug = 0;
		for (int i = 0; i < N; i++) {
			bool recycle = false;
			for (int c = p + 1; c < K; c++) {
				if(plug[i]==use[c]){			// i번째 플러그가 c번째 사용된다면
					if (memo_max_dis < c) {		// 가장 늦게 재사용 된다면
						memo_max_dis = c;		
						memo_farthest_plug = i;	// 해당 플러그 메모
					}
					recycle = true;
					break; //한번이라도 재사용 되면 break
				}
			}
			if (recycle) { continue; }
			//한번도 사용되지 않는다면
			memo_max_dis = K;
			memo_farthest_plug = i; // 해당 플러그 메모
		}
		plug[memo_farthest_plug] = use[p];
		cnt_change_plug++; // 플러그 뽑은 횟수 +1
	}

	cout << cnt_change_plug;
}
