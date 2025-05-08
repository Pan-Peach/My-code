#include<bits/stdc++.h>
using namespace std;

int main(){
    float a[4]={0,0,0,0};
    float a1,a2,a3;
    cin>>a1>>a2>>a3;
    a[0]=a1;a[1]=a2;a[2]=a3;
    sort(a,a+3);
    for(int i=0;i<3;i++) printf("%.1f ",a[i]);
    return 0;
}
