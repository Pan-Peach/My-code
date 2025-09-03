#include<bits/stdc++.h>
using namespace std;
const int maxn=92347895;
int main(){
    int n,a[500];
    map<int,int> hash;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        hash.insert(pair<int,int>(a[i],0));
    }
    for(int i=0;i<n;i++){
        hash[a[i]]+=1;
    }
    for(int i=n-1;i>=0;i--){
        if(hash[a[i]]>1){
            hash[a[i]]--;
            a[i]=maxn;
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]!=maxn) cout<<a[i]<<' ';
    }
    return 0;
}