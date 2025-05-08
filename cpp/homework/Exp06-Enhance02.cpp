#include<bits/stdc++.h>
using namespace std;

void out(int*a,int n){
    if(n<0) return;
    if(n>0){
        cout<<a[n]<<' ';
    }
    if(n==0) cout<<a[n];
    out(a,n-1);
    return;
}

int main(){
    int a[100],n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    out(a,n-1);
    return 0;
}