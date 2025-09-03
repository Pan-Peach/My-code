#include<bits/stdc++.h>
using namespace std;
int a[12][22];
int main(){
    int n;cin>>n;
    a[1][1]=1;
    for(int i=2;i<=10;i++){
        for(int j=1;j<=i;j++){
            a[i][j]=j;
        }
        for(int j=i+1;j<=2*i-1;j++){
            a[i][j]=2*i-j;
        }
    }
    a[10][10]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<2*n-2*i+1;j++) 
            cout<<' ';
        for(int j=1;j<2*i;j++)
            if(j==2*i-1) cout<<a[i][j];
            else{
                cout<<a[i][j]<<' ';
            }
        cout<<'\n';
    }
    return 0;
}