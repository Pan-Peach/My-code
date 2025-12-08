#include<bits/stdc++.h>
using namespace std;

int fac[21];

int factorial(int n){
    if(n==0 || n==1) return 1;
    if(fac[n]!= 0) return fac[n];
    else fac[n] = n * factorial(n-1);
    return fac[n];
}

int main(){
    int n;
    cin>>n;
    cout<<factorial(n)<<endl;
    return 0;
}