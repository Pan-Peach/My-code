#include<bits/stdc++.h>
using namespace std;
double a[100];
int main(){
    int n;double x;
    cin>>x>>n;
    a[0]=1;a[1]=x;
    for(int i=2;i<=23;i++){
        double j=i;
        a[i]=((2*j-1)/j)*x*a[i-1]-((j-1)/j)*a[i-2];       
    }
    printf("%.2f",a[n]);
    return 0;
}