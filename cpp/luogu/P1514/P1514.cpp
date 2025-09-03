#include<bits/stdc++.h>
using namespace std;
const int maxn=10;
int a[maxn][maxn],n,m;

void dfs(int dph,int n){
    
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m;i++){
        dfs(0,i);
    }
    return 0;
}