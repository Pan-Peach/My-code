#include<iostream>
using namespace std;
#define ll long long

ll fact(int a){
    if(a==0) return 1;
    ll b=1;
    for(ll i=1;i<=a;i++){
        b*=i;
    }
    return b;
}

long double fastpow(long double x,int n){
    if(n==0) return 1;
    if(n==1) return x;
    long double tmp=fastpow(x,n/2);
    if(n%2==1) return tmp*tmp*x;
    return tmp*tmp;
}

int main(){
    long double x;long double ans=0;
    cin>>x;
    for(int i=0;i<50;i++){
        double tmp=fastpow(x,i);
        for(int k=0;k<=i;k++){
            if(k==0){
                tmp/=1;
            }
            else{
                tmp/=k;
            }
        }
        ans+=tmp;
    }
    printf("%.2Lf",ans);
    return 0;
}