#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    double ans=1;
    for(int i=1;i<=n;i++){
        double k=i;
        ans*=(2*k/(2*k-1)*(2*k/(2*k+1)));
    }
    printf("%.10f",2*ans);
    return 0;
}