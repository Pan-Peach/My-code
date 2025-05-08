#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a[101];
    bool check=1;
    cin>>n;
    for(int i=0;i<n*n;i++) cin>>a[i];
    map<int,int> hash;
    for(int i=0;i<n*n;i++) hash.insert(pair<int,int>(a[i],0));
    for(int i=0;i<n*n;i++){
        hash[a[i]]++;
        if(hash[a[i]]>1){
            check=0;
            break;
        }
    }
    if(check) cout<<"NO";
    else cout<<"YES";
    return 0;
}