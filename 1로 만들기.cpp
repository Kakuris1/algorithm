#include<iostream>
#include<algorithm>
using namespace std;

int N, Min_Calc[1000001];

int main()
{
	cin >> N;
	Min_Calc[1]=0;
	for(int i=2; i<=N; i++){ Min_Calc[i]=1000000000; }
	for(int i=1; i<N; i++)
	{
		Min_Calc[i+1]= min(Min_Calc[i+1], Min_Calc[i]+1);
		if(i*2<1000001){ Min_Calc[i*2]= min(Min_Calc[i*2], Min_Calc[i]+1); }
		if(i*3<1000001){ Min_Calc[i*3]= min(Min_Calc[i*3], Min_Calc[i]+1); }
	}
	cout << Min_Calc[N];
}

