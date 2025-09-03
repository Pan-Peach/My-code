#include<bits/stdc++.h>
using namespace std;

double hermite(double n,double x){
    if(n==0) return 1;
    if(n==1) return 2*x;
    if(n>1) return 2*x*hermite(n-1,x)-2*(n-1)*hermite(n-2,x);
    return 0;
}

int main(){
    double n,x;
    cin>>n>>x;
    printf("%.2f",hermite(n,x));
    return 0;
}