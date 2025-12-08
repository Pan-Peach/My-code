#include<bits/stdc++.h>
using namespace std;

string solve(string s){
    string ss;
    for(int i=0;i<s.size();i+=2){
        ss.push_back(s[i]);
    }
    int j=0;
    if(s.size()%2==1) j=s.size()-2;
    else j=s.size()-1;
    for(;j>=0;j-=2){
        ss.push_back(s[j]);
    }
    return ss;
}

int main(){
    string s;
    cin>>s;
    cout<<solve(s);
    return 0;
}