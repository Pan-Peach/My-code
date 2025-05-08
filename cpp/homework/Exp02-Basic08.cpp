#include<bits/stdc++.h>
using namespace std;

int main(){
    for(int i=100;i<1000;i++){
        int a1,a2,a3,k;
        k=i;
        a1=k/100;
        a2=(k/10)%10;a3=k%10;
        if(i==pow(a1,3)+pow(a2,3)+a3*a3*a3) cout<<i<<' ';
    }
    return 0;
}