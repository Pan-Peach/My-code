#include<bits/stdc++.h>
using namespace std;
#define MAXN 400005

vector<int> dis;

class Node{
public:
    int u, d;
    Node(int u, int d):u(u),d(d){}
    bool operator<(const Node& other) const{
        return d>other.d;
    }
};

void BFS(int s, int t, vector<vector<int>>& g){
    int n = g.size();
    dis.assign(n, MAXN);
    dis[t] = 0;
    queue<int> q;
    q.push(t);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v:g[u]){
            if(dis[v]>dis[u]+1){
                dis[v] = dis[u]+1;
                q.push(v);
            }
        }
    }
    
}

int min_path_to(int x, int s, vector<int>& dis){
    if(x<s) return x+1;
    else if(x==s) return 0;
    else return x;
}

int solve(int n, int m, int s, int t, vector<vector<int>>& g){
    BFS(s, t, g);
    int ans = MAXN;
    for(int i=0;i<=n;i++){
        ans = min(ans, min_path_to(i, s, dis)+dis[i]);
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int n,m,s,t;
        cin >> n >> m >> s >> t;
        vector<vector<int>> g(n+1);
        for(int i=0;i<m;i++){
            int u,v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            
        }
            cout << solve(n, m, s, t, g) ;
            if(T!=0) cout << endl;
    }
    return 0;
}