#include<bits/stdc++.h>
using namespace std;
int maxx;
void search(int* a,int index){
    if(index<0) return;
    if(a[index]>maxx) maxx=a[index];
    search(a,index-1);
    return;
}

int main(){
    int n,a[100];
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    search(a,n-1);
    cout<<maxx;
    return 0;
}