#include<bits/stdc++.h>
using namespace std;

void printPath(const string &path){
    cout<<'{';
    for(int i=0;i<path.size();i++){
        if(i) cout<<",";
        cout<<path[i];
    }
    cout<<'}'<<endl;
    return;
}

void dfs(int start, int n, string &path){
    printPath(path);
    
    for(int i=start;i<n;i++){
        path.push_back('a'+i);
        dfs(i+1,n,path);
        path.pop_back();
    }
    return;
}

int main(){
    int n;
    cin>>n;
    string path;
    dfs(0,n,path);
    return 0;
}