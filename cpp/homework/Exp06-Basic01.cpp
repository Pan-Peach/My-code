#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll combination(ll m,ll n){
    if(n<0) return 0;
    if(n==0) return 1;
    if(n==1) return m;
    if(m<2*n) return combination(m,m-n);
    if(m>=2*n) return combination(m-1,n-1)+combination(m-1,n);
    return 0;
}

int main(){
    ll m,n;
    cin>>m>>n;
    cout<<combination(m,n);
    return 0; 
}