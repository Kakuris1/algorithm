#include<iostream>

using namespace std;
int N[10][10];
int blank[82];
int blank_cnt = 0;
int answer[10][10];

bool judge_area(int x, int y, int curr)
{
    int dx[9] = { -3,0,3,-3,0,3,-3,0,3 };
    int dy[9] = { -3,-3,-3,0,0,0,3,3,3 };
    for (int i = 0; i < 9; i++)
    {
        int x_range_min = 4 + dx[i];
        int x_range_max = 6 + dx[i];
        int y_range_min = 4 + dy[i];
        int y_range_max = 6 + dy[i];
        if (x_range_min <= x && x <= x_range_max && y_range_min <= y && y <= y_range_max) {
            for (int a = x_range_min; a <= x_range_max; a++) {
                for (int b = y_range_min; b <= y_range_max; b++) {
                    if (N[b][a] == curr) { return false; }
                }
            }
            return true;
        }
    }
}

void dfs(int curr)
{
    //cout << "curr : "<< curr << "\n";
    if (curr == blank_cnt + 1) {//가능
        for (int y = 1; y <= 9; y++)
            for (int x = 1; x <= 9; x++) {
                answer[y][x] = N[y][x];
            }
    }
    int x = blank[curr] / 10;
    int y = blank[curr] % 10;
    for (int value = 1; value <= 9; value++) {
        bool can_put = true;
        //가로 판별
        for (int i = 1; i <= 9; i++) {
            if (N[y][i] == value) { can_put = false; }
        }
        //세로 판별
        for (int i = 1; i <= 9; i++) {
            if (N[i][x] == value) { can_put = false; }
        }
        //구역 판별
        can_put = judge_area(x, y, value);
        if (can_put) {
            N[y][x] = value;
            dfs(curr + 1);
        }
    }
    N[y][x] = 0;//돌아갈때 다시 초기화
}

int main()
{
    for (int y = 1; y <= 9; y++)
        for (int x = 1; x <= 9; x++) {
            cin >> N[y][x];
            if (N[y][x] == 0) {
                blank_cnt++;
                blank[blank_cnt] = 10 * x + y;
                cout << blank[blank_cnt] << endl;
            }
        }
    cout << "A";
    dfs(1);
    cout << "B";
    for (int y = 1; y <= 9; y++) {
        for (int x = 1; x <= 9; x++) {
            cout << answer[y][x];
        }
        cout << '\n';
    }
}

//cout<<"A"
/*
0 3 5 4 6 9 2 7 8
7 8 2 1 0 5 6 0 9
0 6 0 2 7 8 1 3 5
3 2 1 0 4 6 8 9 7
8 0 4 9 1 3 5 0 6
5 9 6 8 2 0 4 1 3
9 1 7 6 5 2 0 8 0
6 0 3 7 0 1 9 5 2
2 5 8 3 9 4 7 6 0
*/
