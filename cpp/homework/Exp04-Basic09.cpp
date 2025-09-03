#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a[11][11];
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    bool check=1;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(a[i][j]!=a[j][i]) check=0;
        }
    }
    if(check) cout<<"YES";
    else cout<<"NO";
    return 0;
}