#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> Pr;

Pr Find(Pr n)
{
	if (P[n.second][n.first] == n) { return n; }
	return P[n.second][n.first] = Find(P[n.second][n.first]);
}
void Union(Pr a, Pr b)
{
	Pr A = Find(a);
	Pr B = Find(b);
	if (A == B) { return; }
	P[B.second][B.first] = A;
	return;
}

int main()
{
	
}
