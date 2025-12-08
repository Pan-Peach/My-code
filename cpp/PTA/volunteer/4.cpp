#include<bits/stdc++.h>
using namespace std;

bool check(vector<int> &v, int m, int n){
    int cur=0;
    stack<int> s;
    for(auto num:v){
        if(num>cur){
            while(cur<num){
                s.push(++cur);
                if(s.size()>m) return false;
            }
            s.pop();
            
        }
        else{
            if(s.empty() || s.top()!=num) return false;
            s.pop();

        }
    }
    return true;
}

int main(){
    int m,n,k;
    cin>>m>>n>>k;
    vector<int> v(n);
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++) cin>>v[j];
        if(check(v,m,n)) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}