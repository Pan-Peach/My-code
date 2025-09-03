
#include<bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> adjlist;
vector<int> dfslist,bfslist;

void dfs(const adjlist& adj,int n,int cur,vector<bool>& visited){
    visited[cur]=true;
    dfslist.push_back(cur);
    for(int i=0;i<adj[cur].size();i++){
        int next=adj[cur][i];
        if(!visited[next]) dfs(adj,n,next,visited);
    }
    return;
}

void bfs(const adjlist& adj,int n){
    vector<bool> visited(n+1);
    queue<int> q;
    q.push(1);
    visited[1]=true;
    while(!q.empty()){
        int u=q.front();
        bfslist.push_back(u);
        q.pop();
        for(int i=0;i<adj[u].size();i++){
            if(!visited[adj[u][i]]){
            q.push(adj[u][i]);
            visited[adj[u][i]]=true;
            }
        }
    }
    return;
}

int main(){
    int n,m,x,y;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>x>>y;
        adj[x].push_back(y);   
    }
    for(int i=1;i<=n;i++){
        if(adj[i].begin()!=adj[i].end())
        sort(adj[i].begin(),adj[i].end());
    }
    vector<bool> visited(n+1);
    visited[1]=true;
    dfs(adj,n,1,visited);
    for(int i=0;i<dfslist.size();i++){
        if(i>0) cout<<" ";
        cout<<dfslist[i];
    }
    cout<<"\n";
    bfs(adj,n);
    for(int i=0;i<bfslist.size();i++){
        if(i>0) cout<<" ";
        cout<<bfslist[i];
    }
    
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> adjlist;
vector<int> dfslist, bfslist;

// 深度优先搜索函数
void dfs(const adjlist &adj, int cur, vector<bool> &visited) {
    visited[cur] = true;             // 当前节点标记为已访问
    dfslist.push_back(cur);          // 将当前节点加入 DFS 结果
    for (int i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (!visited[next]) {        // 如果未访问，递归访问邻居
            dfs(adj, next, visited);
        }
    }
}

// 广度优先搜索函数
void bfs(const adjlist &adj, int n) {
    vector<bool> visited(n + 1);     // 访问标记数组
    queue<int> q;                    // 队列
    q.push(1);                       // 从节点 1 开始
    visited[1] = true;               // 标记节点 1 为已访问
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfslist.push_back(u);        // 将当前节点加入 BFS 结果
        for (int i = 0; i < adj[u].size(); i++) {
            int next = adj[u][i];
            if (!visited[next]) {    // 如果未访问，将其加入队列
                q.push(next);
                visited[next] = true;
            }
        }
    }
}

int main() {
    int n, m, x, y;
    cin >> n >> m;
    adjlist adj(n + 1);              // 邻接表
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);         // 添加边 x -> y
    }

    // 对邻接表的每个节点的邻居排序
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    // 执行 DFS
    vector<bool> visited(n + 1);     // DFS 的访问标记数组
    dfs(adj, 1, visited);

    // 输出 DFS 结果
    for (int i = 0; i < dfslist.size(); i++) {
        if (i > 0) cout << " ";
        cout << dfslist[i];
    }
    cout << "\n";

    // 执行 BFS
    bfs(adj, n);

    // 输出 BFS 结果
    for (int i = 0; i < bfslist.size(); i++) {
        if (i > 0) cout << " ";
        cout << bfslist[i];
    }

    return 0;
}
*/