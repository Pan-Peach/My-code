#include<bits/stdc++.h>
using namespace std;
string s,st="{}[]()";

char pos[1000];

int main(){
    bool yes=1;
    stack<char> check;
    char ch; string s;
    cin>>s;
    for(int j=0;j<s.size()&&s[j]!='@';j++){
        ch=s[j];
        for(int i=0;i<st.size();i++){
            if(ch==st[i]&&i%2==0){
                check.push(ch);
            }
            else if(ch==st[i]&&i%2==1){
                if(check.top()!=st[i-1]) yes=0;
                check.pop();
            }
        }
    }
    if(yes) cout<<"YES";
    else cout<<"NO";
    return 0;
}