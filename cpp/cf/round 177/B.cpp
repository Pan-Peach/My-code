#include<bits/stdc++.h>
using namespace std;

int solu(int n,int k,int x){
    vector<int> a(n);
    vector<int> prefix(n);
    for(int i=0;i<=n;i++){
        cin>>a[i];
        if(i>0) prefix[i]+=prefix[i-1]+a[i];
        else prefix[i]=a[i];
    }
    int len=1;
    int ans=0;
    
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,k,x;
        cin>>n>>k>>x;
        
    }
}