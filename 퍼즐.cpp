#include<iostream>
#include<queue>
using namespace std;

int p[10];
bool visited[876543211];
int Comb();
void swap(int A, int B);
void Div(int curr);

int main()
{
	for (int i = 1; i <= 9; i++){
		cin >> p[i];
	}
	int S = Comb();
	queue<int>Q;
	Q.push(S);
	visited[S] = true;

	int cnt = 0;
	while (!Q.empty())
	{
		int Qsize = Q.size();
		for (int Qfor = 0; Qfor < Qsize; Qfor++)
		{
			int curr = Q.front();
			Div(curr);
			Q.pop();
			if (!(p[1] == 0 || p[2] == 0 || p[3] == 0)) { // 위로 움직임
				swap(curr, curr - 3);
				int tmp = Comb();
				if (!visited[tmp]) { Q.push(tmp); visited[tmp] = true; }
				swap(curr, curr - 3);
			}
			// 아래 좌, 우
		}
	}
}

void swap(int A, int B)
{
	int tmp = p[A];
	p[A] = p[B];
	p[B] = tmp;
}

int Comb()
{
	int result = p[1];
	for (int i = 2; i <= 9; i++)
	{
		result *= 10;
		result += p[i];
	}
	return result;
}

void Div(int curr)
{
	int i = 10;
	while (i--)
	{
		p[i] = curr % 10;
		curr /= 10;
	}
}
