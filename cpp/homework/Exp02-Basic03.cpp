#include<bits/stdc++.h>
using namespace std;
int x,a[19],ans=0;
int main(){
    cin>>x>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];  
    for(int i=0;i<5;i++){
        if(a[i]%x==0) ans+=a[i];
    }
    cout<<ans;
    return 0;
}