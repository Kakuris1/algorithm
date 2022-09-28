#include<iostream>
using namespace std;

int R, C; //R:세로 C:가로
bool can[10000][500];

int main()
{
	cin >> R >> C;
	cout << can[9999][499];
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cout << "f";
			cin >> can[y][x];
		}
	}
}
