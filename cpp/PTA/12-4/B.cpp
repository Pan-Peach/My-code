#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
class Edge{
    public:
    int to,len;
    Edge(int to,int len):to(to),len(len){}

    bool operator<(const Edge& other) const {
        return len > other.len;
    }
};
    

void Dijkstra(int s, int t, vector<vector<Edge>>& g, vector<int>& dist) {
    priority_queue<Edge> pq;
    dist[s] = 0;
    pq.push(Edge(s, 0));
    while (!pq.empty()) {
        Edge curr = pq.top();
        pq.pop();
        int u = curr.to;
        if (curr.len > dist[u]) continue;
        for (auto& edge : g[u]) {
            int v = edge.to;
            int len = edge.len;
            if (dist[u] + len < dist[v]) {
                dist[v] = dist[u] + len;
                pq.push(Edge(v, dist[v]));
            }
        }
    }
    return;
}

int main(){
    int n,s,t;
    int m,k;
    while(cin>>n>>s>>t){
        cin>>m;
        vector<vector<Edge>> bus(n+1);
        vector<vector<Edge>> bus_reverse(n+1);
        vector<vector<Edge>> metro(n+1);
        for(int i=0;i<m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            bus[u].push_back(Edge(v,w));
            bus_reverse[v].push_back(Edge(u,w));
        }
        cin>>k;
        for(int i=0;i<k;i++){
            int u,v,w;
            cin>>u>>v>>w;
            metro[u].push_back(Edge(v,w));
        }
        vector<int> dist_bus(n+1,INF);
        vector<int> dist_bus_reverse(n+1,INF);
        Dijkstra(s,t,bus,dist_bus);
        Dijkstra(t,s,bus_reverse,dist_bus_reverse);
        
        int ans=dist_bus[t];
        int idx=-1;
        for(int i=1;i<=n;i++){
            for(auto& edge:metro[i]){
                int v=edge.to;
                int w=edge.len;
                if(dist_bus[i]+w+dist_bus_reverse[v]<ans){
                    ans=dist_bus[i]+w+dist_bus_reverse[v];
                    idx=i;
                }
            }
        }
        cout<<ans<<endl;
        if(ans==dist_bus[t]){
            cout<<"no metro"<<endl;
        }else{
            cout<<idx<<endl;
        }

    }

    return 0;
}