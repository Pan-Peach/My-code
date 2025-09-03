#include<bits/stdc++.h>
using namespace std;
int cnt=1;
void cut(int len,int k){
    if(len<=k) return;
    int a,b;
    a=len*2/5.0+0.5;
    b=len-a;
    cnt++;
    if(a>k) cut(a,k);
    if(b>k) cut(b,k);
    return;
}

int main(){
    int n,k;
    cin>>n>>k;
    cut(n,k);
    cout<<cnt;
    return 0;
}