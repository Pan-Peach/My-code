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
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            swap(a[i][j],a[j][i]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==n-1) cout<<a[i][j];
            else cout<<a[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}