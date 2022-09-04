#include<iostream>
using namespace std;
int N[10][10];
int blank[82];
int blank_cnt = 0;
int answer[10][10];
bool printed;

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
    if (curr == blank_cnt + 1) {//가능
        for (int y = 1; y <= 9; y++) {
            for (int x = 1; x <= 9; x++) {
                cout << N[y][x] << " ";
            }
            cout << endl;
        }
        exit(0);
        return;
    }
    int x = blank[curr] / 10;
    int y = blank[curr] % 10;

    for (int value = 1; value <= 9; value++) {
        bool can_put_R = true;
        bool can_put_C = true;
        bool can_put_Sec = true;
        //가로 판별
        for (int i = 1; i <= 9; i++) {
            if (N[y][i] == value) { can_put_R = false; }
        }
        //세로 판별
        for (int i = 1; i <= 9; i++) {
            if (N[i][x] == value) { can_put_C = false; }
        }
        //구역 판별
        can_put_Sec = judge_area(x, y, value);
        if (can_put_R && can_put_C && can_put_Sec) {
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
            }
        }
    dfs(1);
    for (int y = 1; y <= 9; y++) {
        for (int x = 1; x <= 9; x++) {
            cout << answer[y][x] << " ";
        }
        cout << '\n';
    }
}
