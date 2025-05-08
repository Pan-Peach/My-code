#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int n;
map<int,int> mp;

void first(vector<int>& list){
    for(int i=1;i<=n;i++){
        if(list[i]!=i){
            int min_pos=mp[i];
            swap(list[i],list[min_pos]);
            mp[list[i]] = i;
            mp[list[min_pos]] = min_pos;             
            return;
        }
    }
}

void second(vector<int>& list){
    for(int i=1;i<=n;i++){
        if(list[i]!=n-i+1){
            int max_pos=mp[n-i+1];
            
            swap(list[i],list[max_pos]);
            mp[list[i]] = i;
            mp[list[max_pos]] = max_pos;
            return;
        }
    }
}

int main(){
    
    scanf("%lld%d",&t,&n);
    vector<int> list(n+1,0);
    for(int i=1;i<=n;i++){
        scanf("%d",&list[i]);
        mp[list[i]]=i;
    }
/*    if(t&1){
        first(list);
    }
    else{
        first(list);
        second(list);
    }
        */
    for(int i=1;i<=t;i++){
        if(i&1) first(list);
        else second(list);
    }
    for(int i=1;i<=n;i++){
        if(i>1) printf(" ");
        printf("%d",list[i]);
    }
    return 0;
}