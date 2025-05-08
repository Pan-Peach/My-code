#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,a[100];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int k=0;k<n;k++){
    for(int i=0;i<n;i++){
        if(a[i]==0){
            for(int j=i+1;j<n;j++){
                a[j-1]=a[j];
            }
            a[n-1]=0;
        }
    }
    }
    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }
    return 0;
}