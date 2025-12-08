#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,op;
    cin>>n;
    stack<int> s;
    for(int i=0;i<n;i++){
        cin>>op;
        if(op==1) s.push(1);
        else{
            if(!s.empty()) s.pop();
            else{
                cout<<0<<endl;
                return 0;
            }
        }
    }
    if (s.empty()) cout<<1<<endl;
    else cout<<0<<endl;
    return 0;
}