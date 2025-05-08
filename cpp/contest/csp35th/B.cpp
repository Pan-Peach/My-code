#include<bits/stdc++.h>
using namespace std;
map<char,char> mp;

void F(string &s){
    for(int i=1;i<s.size()-1;i++){
        if(mp[s[i]]){
            s[i]=mp[s[i]];
        }
    }
    return;
}

int main(){
    string s;
    getline(cin,s);
    for(int i=1;i<s.size()-1;i++){
        mp[s[i]]=s[i];
    } 
    int n,m;
    cin>>n;
    vector<string> f(n);
    cin.ignore();
    for(int i=0;i<n;i++){
        getline(cin,f[i]);
        mp[f[i][1]]=f[i][2];
    }
    cin>>m;
    vector<int> check(m);
    int max=0;
    for(int i=0;i<m;i++){
        cin>>check[i];
        if(check[i]>max){
            max=check[i];
        }
    }
    vector<string> ans(10000,"");

    ans[0]=s;
    string s0=s;
    int mod=1;
    bool flag[2]={0,0};
    for(int i=1;i<=max;i++){
        F(s);
        ans[i]=s;
        mod=i;
        if(s==s0){
            flag[0]=1;
            break;
        }
        if(s==ans[i-1]){
            flag[1]=1;
            break;
        }
    }
    for(int i=0;i<check.size();i++){
        if(flag[0]){
            int index=check[i]%mod;
            cout<<ans[index]<<"\n";
            continue;
        }
        if(flag[1]){
            int index;
            if(check[i]>=mod){
                index=mod;
            }
            else{
                index=check[i];
            }
            cout<<ans[index]<<"\n";
            continue;
        }
        else{
            cout<<ans[check[i]]<<"\n";
        }
    }
    return 0;
}