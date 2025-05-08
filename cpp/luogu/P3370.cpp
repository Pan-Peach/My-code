#include<bits/stdc++.h>
using namespace std;

map<string,int> hashh;
string s[10000];

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s[i];
    }
    for(int i=0;i<n;i++){
        hashh.insert(pair<string,int>(s[i],i));
    }
    cout<<hashh.size();
    return 0;
}