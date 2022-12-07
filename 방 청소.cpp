#include<iostream>
using namespace std;

int N, L;
int P[300001];
bool have_blank[300001];

int Find(int n)
{
	if (P[n] == n) { return n; }
	return P[n] = Find(P[n]);
}
void Union(int a, int b)
{
	int A = Find(a);
	int B = Find(b);
	if (A == B) { have_blank[A] = false; return; }
	P[B] = A;
	return;
}


int main()
{
	for (int i = 0; i < 300001; i++) { P[i] = i; have_blank[i] = true; }
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		int A, B;
		cin >> A >> B;

		if (have_blank[Find(A)]) {
			if (A == Find(A)) {	// 1번 경우
				Union(B, A);
			}
			else if (B == Find(B) && have_blank[Find(B)]) { // 2번 경우
				Union(A, B);
			}
			else { // 3번 경우
				Union(B, A);
			}
			cout << "LADICA\n";
		}
		else if (have_blank[Find(B)]) {
			Union(A, B);
			cout << "LADICA\n";
		}
		else { cout << "SMECE\n"; }
	}
}
