#include<bits/stdc++.h>
using namespace std;

void Topo(vector<vector<int>>& g,vector<int>& indeg){
    priority_queue<int,vector<int>,greater<int>> pq;
    vector<int> out;
    for(int i=0;i<indeg.size();i++){
        if(indeg[i]==0){
            pq.push(i);
        }
    }
    while(!pq.empty()){
        int u=pq.top();
        pq.pop();
        out.push_back(u);
        for(auto& v:g[u]){
            indeg[v]--;
            if(indeg[v]==0){
                pq.push(v);
            }
        }
    }

    for(int i=0;i<indeg.size();i++){
        if(indeg[i]>0){
            cout<<"unworkable project"<<endl;
            return;
        }
    }

    for(auto& v:out){
        cout<<v<<" ";
    }
    cout<<endl;

}

int main(){
    int n,e;
    cin>>n>>e;
    vector<int> indeg(n);
    vector<vector<int>> g(n);
    for(int i=0;i<e;i++){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        indeg[b]++;
    }
    Topo(g,indeg);
    return 0;
}