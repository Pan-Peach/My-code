#include<iostream>
using namespace std;
int a[10000][10000],b[10000];
int main(){
    int m,n,p,q;
    cin>>n>>m>>p>>q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            b[i*m+j]=a[i][j];
        }
    }

    for(int i=0;i<p;i++){
        for(int j=0;j<q;j++){
            cout<<b[i*q+j]<<" ";
            while(j==q-1) {
                cout<<"\n";
                break;
            }
        }
    }
    return 0;
}