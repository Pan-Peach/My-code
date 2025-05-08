#include<bits/stdc++.h>
using namespace std;
const int maxn=300000;
int c,m,n,p[maxn],x[maxn];

void outans(){
    int ans=0;
    for(int i=0;i<c;i++){
        if(x[i]!=0) ans++;
    }
    cout<<ans<<'\n';
}
void explode(int action){
    x[action]=0;
    for(int i=action;i>=0;i--){
        if(x[i]!=0){
            x[i]+=1;
            break;
        }
    }
    for(int i=action;i<c;i++){
        if(x[i]!=0){
            x[i]+=1;
            break;
        }
    }
    return;
}
bool checkwater(){
    for(int i=0;i<c;i++){
        if(x[i]>4){
            return false;
         }
    }
    return true;
}
void act(int action){
    x[action]+=1;
    return;
}
void dfs(int index){
    if(checkwater()){
        return;
    }
    for(int i=index;i<c;i++){
        if(x[i]>4){
            explode(i);
            int frontindex=0;
            for(i=index;i>=0;i--){
                if(x[i]!=0){
                    frontindex=i;
                    break;
                }
            }
            dfs(frontindex);
        }
    }
    return;
}

int main(){
    cin>>c>>m>>n;
    int tmp;
    for(int i=0;i<m;i++){
        cin>>tmp;
        cin>>x[tmp-1];
    }
    for(int i=0;i<n;i++){
        cin>>p[i];
        p[i]-=1;
    }
    for(int i=0;i<n;i++){
        act(p[i]);
        if(x[p[i]]>4){
            dfs(p[i]);
        }
        outans();
    }
    return 0;
}