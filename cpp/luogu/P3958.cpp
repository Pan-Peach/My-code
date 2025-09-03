#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class DSU{
    public:
    vector<int> pa;
    DSU(int n){
        pa.resize(n+1);
        for(int i=1;i<=n;i++) pa[i] = i;
    }
    int find(int x){
        if(pa[x] != x) pa[x] = find(pa[x]);
        return pa[x];
    }
    void merge(int a,int b){
        int paA = find(a);
        int paB = find(b);
        if(paA != paB) pa[paA] = paB;
    }
};

ll calcDist(ll x1,ll y1,ll z1,ll x2,ll y2,ll z2){
    ll dx=abs(x1-x2);
    ll dy=abs(y1-y2);
    ll dz=abs(z1-z2);
    // if(dx>=(1LL<<21)||dy>=(1LL<<21)||dz>=(1LL<<21)) return LLONG_MAX;
    return dx*dx+dy*dy+dz*dz;
}

class Node{
    public:
    ll x,y,z;
    Node(ll x=0,ll y=0,ll z=0):x(x),y(y),z(z){}

    bool connected(const Node &b, ll r){
        ll dx = abs(x - b.x);
        ll dy = abs(y - b.y);
        ll dz = abs(z - b.z);
        if(dx > 2*r || dy > 2*r || dz > 2*r) return false;
        return calcDist(x,y,z,b.x,b.y,b.z) <= 4*r*r;
    }
};

int main(){
    int T;
    cin >> T;
    while(T--){
        ll n,h,r;
        cin >> n >> h >> r;
        vector<Node> nodes(n+1);
        vector<int> in;
        vector<int> out;
        for(int i=1;i<=n;i++){
            ll x,y,z;
            cin >> x >> y >> z;  
            nodes[i] = Node(x,y,z);
            if(z <= r) in.push_back(i);   
            if(z >= h-r) out.push_back(i);    
        }
        if(in.empty() || out.empty()) {
            cout << "No" << endl;
            continue;
        }
        DSU dsu(n);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(nodes[i].connected(nodes[j],r)){
                    dsu.merge(i,j);
                }
            }
        }
        bool flag = false;
        for(auto &i:in){
            for(auto &j:out){
                if(dsu.find(i) == dsu.find(j)){
                    flag = true;
                    break;
                }
            }
        }
        if(flag) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}