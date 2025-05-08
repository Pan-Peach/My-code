#include<bits/stdc++.h>
using namespace std;

string s;
map<char,int> mapp;

bool check(int difference){
    switch(difference){
        case 0: return 0;break;
        case 1: return 0;break;
        case 2: return 1;break;
    }
    for(int i=2;i<sqrt(difference);i++){
        if(difference%i==0) return false;
    }
    return true;
}

int minuss(){
    for(int i=0;i<s.size();i++){
        mapp[s[i]]+=1;
    }
    int maxn=0,minn=1000000;
    for(int i=0;i<s.size();i++){
        if(mapp[s[i]]>maxn) maxn=mapp[s[i]];
        if(mapp[s[i]]<minn) minn=mapp[s[i]];
    }
    return maxn-minn;
}

int main(){
    cin>>s;
    for(int i=0;i<s.size();i++) mapp.insert(pair<char,int>(s[i],0));
    int dif=minuss();
    if(check(dif)) cout<<"Lucky Word"<<'\n'<<dif;
    else cout<<"No Answer"<<'\n'<<0;
    return 0;
}