#include<bits/stdc++.h>
using namespace std;

int a[100],n;

void dfs(int now,int len){
    
    if(now==0){
        if(a[1]==n) return;
        cout<<a[0]<<'=';
        for(int i=1;i<len-1;i++){
           cout<<a[i]<<'+';
        }
        cout<<a[len-1]<<'\n';
        return;
    }
    for(int i=now;i>0;i--){
        if(i<=a[len-1]){
            a[len]=i;
            dfs(now-i,len+1);
        }
    }
    return;
}
int main(){
    cin>>n;
    a[0]=n;
    dfs(n,1);
    return 0;
}

//哥，dfs都写半天，明明早就写出来了，格式不会控制