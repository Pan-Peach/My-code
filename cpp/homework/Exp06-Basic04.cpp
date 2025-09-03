#include<bits/stdc++.h>
using namespace std;

int gcd(int a,int b){
    int tmp=a%b;
    if(tmp==0) return b;
    return gcd(b,tmp);
}

int main(){
    int a,b;
    cin>>a>>b;
    if(a>b) cout<<gcd(a,b);
    else cout<<gcd(b,a);
    return 0;
}