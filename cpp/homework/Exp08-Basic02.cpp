#include<bits/stdc++.h>
using namespace std;

int checkerboard[100][100];
int n,cnt;

bool check(int x,int y){
    for(int i=0;i<x;i++){
        if(checkerboard[i][y]) return false;
    }

    for(int i=1;x-i>=0&&y-i>=0;i++){
        if(checkerboard[x-i][y-i]) return false;
    }
    for(int i=1;x-i>=0&&y+i>=0;i++){
        if(checkerboard[x-i][y+i]) return false;
    }
    return true;
}

void dfs(int x){
    if(x==n){
        cnt++;
        return;
    }
    for(int i=0;i<n;i++){
        if(check(x,i)){
            checkerboard[x][i]=1;
            dfs(x+1);
            checkerboard[x][i]=0;
        }
    }
    return;
}

int main(){
    cin>>n;
    dfs(0);
    cout<<cnt;
    return 0;
}