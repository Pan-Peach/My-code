#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    string s;
    cin>>n>>s;
    for(int i=0;i<s.size();i++){
        s[i]=97+((s[i]-97+n)%26);
    }
    cout<<s;
    return 0;
}