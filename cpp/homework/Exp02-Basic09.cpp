#include<bits/stdc++.h>
using namespace std;

int main(){
    long long big=1,small=0,pragnet,n;
    cin>>n;
    for(int i=0;i<n;i++){
        int tmp=small;
        small+=pragnet;
        pragnet=big;
        big+=small;
        small=0;
    }
    cout<<big+small;
    return 0;
}