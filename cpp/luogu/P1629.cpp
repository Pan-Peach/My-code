#include <bits/stdc++.h>
using namespace std;

const int noedge = 1e9;

class Point{
    public:
    int node;
    int edge;

    public:
        Point(int n,int e){
            node=n;
            edge=e;
        }
    
    inline bool operator < (const Point& p)const{
        return p.edge<edge;
    }
};


void Floyd(vector<vector<int>> &graph) {
    int n = graph.size() - 1;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) { 
                if (graph[i][k] != noedge && graph[k][j] != noedge) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }            
            }
        }
    }
}

void Dijstra(vector<vector<pair<int,int> > >& graph, vector<int>& dis,int n ){
    priority_queue<Point> pq;
    vector<bool> flag(n+1,0);
    pq.push(Point(1,0));

    while(!pq.empty()){
        Point top=pq.top();
        pq.pop();
        if(flag[top.node]) continue;
        flag[top.node]=1;
        for(auto edge:graph[top.node]){
            int u,w;
            u=edge.first;w=edge.second;
            dis[u] = min(dis[u],w+dis[top.node]);
            pq.push(Point(u,w+dis[top.node]));
        }

    }
    return;
}

int main() {
    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, noedge));
    vector<vector<pair<int,int> > > graph2(n + 1);
    vector<vector<pair<int,int> > > graph3(n + 1);
    vector<int> dis(n+1,noedge);
    vector<int> dis2(n+1,noedge);
    dis[1]=0;
    dis2[1]=0;
    for (int i = 1; i <= n; i++) graph[i][i] = 0;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph2[u].push_back({v,w});
        graph3[v].push_back({u,w});
    }
//    Floyd(graph);
    Dijstra(graph2,dis,n);
    Dijstra(graph3,dis2,n);
    int ans1 = 0,ans2=0;
    for(int i=1;i<=n;i++){
        ans1+=dis[i];
        ans2+=dis2[i];
    }
    cout<<ans1+ ans2 <<endl;
    return 0;
}