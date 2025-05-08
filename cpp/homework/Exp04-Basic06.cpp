#include<bits/stdc++.h>
using namespace std;
int a[101],n,j;
void move(){
    int  tail=a[n-1];
    for(int i=n-1;i>=0;i--){
        a[i]=a[i-1];
    }
    a[0]=tail;
}

int main(){
    cin>>n>>j;
    for(int i=0;i<n;i++) cin>>a[i];
    while(j--) move();
    for(int i=0;i<n;i++) cout<<a[i]<<' ';
    return 0;
}