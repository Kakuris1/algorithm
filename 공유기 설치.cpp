#include<iostream>

using namespace std;

int N, C, X[200000];

int main()
{
	cin >> N >> C;
	for(int i=0; i<N; i++){ cin>>X[i]; }
	
	int tmp;	//삽입 정렬
	for(int i=1; i<N; i++)
	{
		tmp=X[i];
		for(int j=i-1; j>=0; j--)
		{
			if(X[j]<tmp){ break; }
			else
			{
				X[j+1]=X[j];
				X[j]=tmp;
			}
		}
	}
	
	int lo=1;
	int hi=X[N-1]-X[0];
	while(lo<=hi)
	{
		int mid=(lo+hi)/2;
		int count=1;
		long long Dis=0;
		for(int i=0; i<N-1; i++)
		{
			Dis+=X[i+1]-X[i];
			if(Dis>=mid)
			{
				Dis=0;
				count++;
			}
		}
		if(count>=C){ lo=mid+1; }
		else{ hi=mid-1; }
	}
	cout<<hi;
}
