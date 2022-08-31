include<iostream>

using namespace std;
int N[10][10];
int blank[82];
int blank_cnt=0;

bool judge_area()

void dfs(int curr)
{
    if(curr==blank_cnt+1){;}//가능
    int x = blank[curr]/10;
    int y = blank[curr]%10;
    for(int value=1; value<=9; value++){
        bool can_put=true;
        //가로 판별
        for(int i=1; i<=9; i++){
            if(N[y][i]==value) {can_put=false;}
        }
        //세로 판별
        for(int i=1; i<=9; i++){
            if(N[i][x]==value) {can_put=false;}
        }
        //구역 판별
        can_put=judge_area();
        if(can_put){
            N[y][x]=value;
            dfs(curr+1);
        }
    }
    N[y][x]=0;//돌아갈때 다시 초기화
}

int main()
{
    for(int y=1; y<=9; y++)
        for(int x=1; x<=9; x++){
            cin >> N[y][x];
            if(N[y][x]==0){
                blank_cnt++;
                blank[blank_cnt]=10*x+y;
            }
        }
}
