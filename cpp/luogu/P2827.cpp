// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;

void solve(int m, int q, double p, int t, priority_queue<int>& origin){
    int n=origin.size();
    vector<ll> cuts;
    vector<ll> ans;
    ll delta=0;
    for(int i=1;i<=m;i++){
        ll top=origin.top()+delta;
        // if(i%t==0) cout<<top<<' ';
        cuts.push_back(top);
        origin.pop();
        ll l=top*p;
        ll r=top-l;
        delta+=q;
        origin.push(l-delta);
        origin.push(r-delta);

    }
    while(!origin.empty()){
        ans.push_back(origin.top()+delta);
        origin.pop();
    }
    for(int i=t-1;i<cuts.size();i+=t) printf("%lld ",cuts[i]);
    // cout<<endl;
    printf("\n");
    for(int i=t-1;i<ans.size();i+=t) printf("%lld ",ans[i]);

}

void solve2(int m, int q, double p, int t, priority_queue<int>& origin, int u, int v){
    int n=origin.size();
    queue<ll> left;
    queue<ll> right;
    vector<ll> ans;
    ll delta=0;
    for(int i=1;i<=m;i++){
        ll top1=origin.empty()?0:origin.top()+delta;
        ll top2=left.empty()?0:left.front()+delta;
        ll top3=right.empty()?0:right.front()+delta;
        ll top=max(top1,max(top2,top3));
        if(top==top1){
            origin.pop();
        }
        else if(top==top2){
            left.pop();
        }
        else{
            right.pop();
        }
        if(i%t==0) cout<<top<<' ';
        ll l=top*u/v;
        ll r=top-l;
        delta+=q;
        left.push(l-delta);
        right.push(r-delta);
    }
    cout<<endl;
    for(int i=1;i<=n+m;i++){
        ll top1=origin.empty()?0:origin.top()+delta;
        ll top2=left.empty()?0:left.front()+delta;
        ll top3=right.empty()?0:right.front()+delta;
        ll top=max(top1,max(top2,top3));
        if(top==top1){
            origin.pop();
        }
        else if(top==top2){
            left.pop();
        }
        else{
            right.pop();
        }
        if(i%t==0) cout<<top<<' ';
    }

}

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n,m,q,u,v,t;
    // cin>>n>>m>>q>>u>>v>>t;
    scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
    priority_queue<int> origin;
    for(int i=1; i<=n; i++){
        int x;
        // cin>>x;
        scanf("%d",&x);
        origin.push(x);
    }
    int time=m/t;
    double p = (double)u/v;
    solve2(m,q,p,t,origin,u,v);
    return 0;
}