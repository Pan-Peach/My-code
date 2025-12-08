#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

void buildNext(string &p, vector<int> &next){
    int k=next[0]=-1;
    int m=p.length();
    for(int j=0;j<m;j++){
        while(k>-1 && p[k+1]!=p[j+1]) k=next[k];
        next[j+1]=++k;
    }
    return;
}

int KMP(string &s, string &p, vector<int> &next){
    int n=s.length();
    int m=p.length();
    int j=-1;
    int cnt=0;
    for(int i=0;i<n;i++){
        while(j>-1 && p[j+1]!=s[i]) j=next[j];
        if(p[j+1]==s[i]) j++;
        if(j==m-1){
            cnt++;
            j=next[j];
        }
    }
    return cnt;
}

int main(){
    string p0 = "edgnb";
    string p1 = p0;
    for(int i=0;i<10;i++) p0 += p0;
    vector<int> next(MAXN);
    buildNext(p0,next);
    int T; cin>>T; getchar();
    string s;
    while(T--){
        getline(cin,s);
        int times;
        cin>>times; getchar();
        string p;
        for(int i=0;i<times;i++) p += p1;
        int ans = KMP(s,p,next);
        cout<<ans<<endl;
    }
    return 0;
}