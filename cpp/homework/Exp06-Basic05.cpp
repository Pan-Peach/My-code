#include<bits/stdc++.h>
using namespace std;

int search(int* a,int index,int n,int key){
    if(a[index]==key) return index;
    if(index>=n) return -1;
    return search(a,index+1,n,key);
}

int main(){
    int n,key,a[100];
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    cin>>key;
    int ans=search(a,0,n,key);
    if(ans==-1) cout<<"NULL";
    else cout<<ans;
    return 0;
}