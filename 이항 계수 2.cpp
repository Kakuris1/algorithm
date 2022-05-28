#include<iostream>
using namespace std;

int N, K;
int dp[1001][1001] = { 0, };
int B_C(int n, int k);

int main()
{
	cin >> N >> K;
	for (int i = 0; i < 1001; i++) {
		for (int j = 0; j < 1001; j++) {
			dp[i][j] = -1;
		}
	}
	cout << B_C(N, K);
}

int B_C(int n, int k)
{
	if (k == 0 || n == k) { return 1; }
	if (dp[n][k] != -1) { return dp[n][k]; }

	int result = B_C(n - 1, k) % 10007 + B_C(n - 1, k - 1) % 10007;
	dp[n][k] = result % 10007;
	return result % 10007;
}
