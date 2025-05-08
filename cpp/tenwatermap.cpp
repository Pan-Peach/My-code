#include<bits/stdc++.h>
using namespace std;

map<int,int> x;
int c,m,n,ans[1000],p[1000];

void act(int action){
    x[action]+=1;
}

bool check(){
    for(auto i=x.begin();i!=x.end();i++){
        if(i->second>4) return false;
    }
    return true;
}

void explode(){
    for(auto i=x.begin();i!=x.end();i++){
        auto it=i;
        if(i->second>4){
            if(it!=x.begin()){
                auto frontit=--it;it++;
                x[frontit->first]+=1;
            }
            if(it!=x.end()){
                auto backit=++it;it--;
                x[backit->first]+=1;
            }
            x.erase(it);
            break;
        }
    }
    return;
}

int main(){
    cin>>c>>m>>n;
    for(int i=0;i<m;i++){
        int xx,w;
        cin>>xx>>w;
        x.insert(pair<int,int>(xx,w));
    }
    for(int i=0;i<n;i++){
        cin>>p[i];        
    }
    for(int i=0;i<n;i++){
        act(p[i]);
        if(x[p[i]]>4) 
        while(!check())
        explode();
        ans[i]=x.size();
    }
    for(int i=0;i<n;i++) cout<<ans[i]<<'\n';
    return 0;
}