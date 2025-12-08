#include<bits/stdc++.h>
using namespace std;

vector<int> buildNext(string &p){
    vector<int> next(p.length()+1);
    int k= next[0] = -1;
    int m=p.length();
    for(int j=0;j<m;j++){
        while(k>-1 && p[k]!=p[j]) 
            k=next[k];
        next[j+1]=++k;
    }
    return next;
}

int KMP(string &s, string &p, vector<int> &next){
    int n=s.length();
    int m=p.length();
    // int j=-1;
    // int cnt=0;
    // for(int i=0;i<n;i++){
    //     while(j>-1 && p[j+1]!=s[i]) j=next[j];
    //     if(p[j+1]==s[i]) j++;
    //     if(j==m-1){
    //         cnt++;
    //         j=next[j];
    //     }
    // }
    int j=0,i=0,cnt=0;
    while(j<m && i<n){
        if(j==-1 || s[i]==p[j]){
            i++;
            j++;
        }else{  
            j=next[j];
        }
        if(j==m){
            cnt++;
            j=next[j];
        }
    }
    return cnt;
}

int getP(string &s, vector<int> &next){
    int n=s.length();
    int L=next[n-1];
    priority_queue<int> cand;
    for(int i=1;i<n;i++){
        string sub = s.substr(i,n-1);
        vector<int> subNext = buildNext(sub);
        if(KMP(s,sub,subNext)>1) return n-i;
    }
    return 0;
    // string s2;
    // for(int i=s.length()-1;i>=0;i--){
    //     s2+=s[i];
    // }
    // vector<int> next2 = buildNext(s2);
    // int max=0;
    // for(int i=0;i<=s2.length();i++){
    //     if(next2[i]>max) max=next2[i];
    // }
    // return max;
}

int getQ(string &s, vector<int> &next){
    if(s.length()<=2) return 0;
    int n=s.length();
    int L=next[next[n]];
    if(L<=0) return n;
    int ans=n-2*L;
    if(ans<0) return 0;
    return ans; 
}

int main(){
    string s;
    while(getline(cin,s)){
        vector<int> next = buildNext(s);
        int p = getP(s,next);
        int q = getQ(s,next);
        cout<<p+q<<endl;
    }
    return 0;
}