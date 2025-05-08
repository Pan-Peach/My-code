#include<bits/stdc++.h>
using namespace std;

int n,a[1000];

int main(){
    cin>>n;
    while(true){
        int cnt=0,ans=0;
        do{
            cin>>a[cnt];
            cnt++;
            if(a[cnt-1]==0||a[cnt-1]==-1) break;
        }while(a[cnt-1]!=0||a[cnt-1]!=-1);
        if(a[cnt-1]==-1) break;
        sort(a,a+cnt-1);
        for(int i=1;i<cnt;i++){
            for(int j=0;j<i;j++){
                if(a[i]%a[j]==0&&a[i]/a[j]==n) ans++;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}