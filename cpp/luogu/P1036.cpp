#include<iostream>
#include <math.h>
using namespace std;

int x[30], k, n,ans=0;

bool check(int a){
    for(int i=2;i<sqrt(a);i++){
        if(a%i==0) return false;
    };

    return true;
}


void dfs(int num,int sum,int start){
    if(num>=k){
            if(check(sum)) ans++;
            return;
    }
    for(int i=start;i<n;i++){    
        dfs(num+1,sum+x[i],i+1);
    }
}
int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>x[i];
    dfs(0,0,0);
    cout<<ans;
    return 0;
}