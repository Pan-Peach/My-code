#include<bits/stdc++.h>
using namespace std;

int getMex(vector<bool> &S, int n){
    for(int i=0;i<n;i++){
        if(!S[i]) return i;
    }
    return n;
}

class Node{
    public:
    int now,dis;
    vector<bool> S;
    Node(int now, int dis, vector<bool> S):now(now),dis(dis),S(S){}

    bool operator<(const Node &b) const{
        return dis > b.dis;
    }
};

int Bfs(vector<vector<int>> &G, int s, int t){
    int n = G.size()-1;
    queue<Node> q;
    vector<bool> initS(n,false);
    initS[s] = true;
    q.push(Node(s,0,initS));
    vector<bool> vis(n+1,false);    
    while(!q.empty()){
        Node u = q.front(); q.pop();
        if(u.now == t) return u.dis;
        for(int v:G[u.now]){
            if(!u.S[v]){
                vector<bool> S = u.S;
                S[v] = true;
                q.push(Node(v,u.dis+1,S));
            }          
        }
        int mex = getMex(u.S,n);
        vector<bool> S = u.S;
        S[mex] = true;
        q.push(Node(mex,u.dis+1,S));

    }
    return -1;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int n,m,s,t;
        cin >> n >> m >> s >> t;
        vector<vector<int>> G(n+1);
        for(int i=0;i<m;i++){
            int u,v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int ans = Bfs(G,s,t);
        cout << ans;
        if(T>0) cout << endl;
    }
    return 0;
}