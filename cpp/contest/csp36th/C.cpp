#include<bits/stdc++.h>
using namespace std;



class CacheSet{
public:
    list<pair<int,bool>> line;
    int cap;
    CacheSet(int n){
        cap=n;
    }
    CacheSet(){
        cap=0;
    }

    void read(int idx){
        for(auto it=line.begin();it!=line.end();it++){
            if((*it).first==idx){
                line.push_front(*it);
                line.erase(it);
                return;
            }
        }

        if(line.size()>=cap){
            if(!line.empty()&&line.back().second){
                cout<<"1"<<' '<<line.back().first<<'\n';
            }
            line.pop_back();
        }
        cout<<"0"<<' '<<idx<<'\n';
        line.push_front({idx,0});
        return;
    }

    void write(int idx){

        read(idx);
        for(auto& it:line){
            if(it.first==idx){
                it.second=1;
                break;
            }
        }

        return;
    }

};

class Cache{
public:
    vector<CacheSet> group;
    int N,n;

    Cache(int num,int Num){
        N=Num;
        n=num;
        group.resize(N);
        for(int i=0;i<N;i++){
            group[i]=CacheSet(n);
        }

    }

    int CptIdx(int idx){
        return (idx/n)%N;
    }

    void read(int idx){
        group[CptIdx(idx)].read(idx);
        return;
    }

    void write(int idx){
        group[CptIdx(idx)].write(idx);
        return;
    }
};

int main(){
    int n,N,q;
    cin>>n>>N>>q;
    Cache Ch(n,N);
    for(int i=0;i<q;i++){
        int o,a;
        cin>>o>>a;
        if(o==0){
            Ch.read(a);
        }
        else if(o==1){
            Ch.write(a);
        }
        else{
            cout<<"Wrong Operation"<<'\n';
        }
    }
    return 0;
}