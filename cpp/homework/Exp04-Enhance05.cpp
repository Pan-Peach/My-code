#include<bits/stdc++.h>
using namespace std;
int n,cnt=1,a[31][31];
void  fill(int index){
    for(int i=index;i<n-index;i++){
        a[index][i]=cnt;
        cnt++;
    }
    for(int i=index+1;i<n-index;i++){
        a[i][n-index-1]=cnt;
        cnt++;
    }
    for(int i=n-index-2;i>=index;i--){
        a[n-index-1][i]=cnt;
        cnt++;
    }
    for(int i=n-index-2;i>index;i--){
        a[i][index]=cnt;
        cnt++;
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n/2;i++){
        fill(i);
    }
    if(n%2==1) a[n/2][n/2]=n*n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout.width(4);
            cout<<a[i][j];
        }
        cout<<'\n';
    }
    return 0;
}