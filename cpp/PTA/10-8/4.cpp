#include<iostream>
#include<string>
#include<vector>
using namespace std;

void buildNext(string p, vector<int>& next, int m){
    next[0] = -1;
    int k = -1;
    for(int j=0;j<m-1;j++){
        while(k>=0 && p[j]!=p[k]) k = next[k];
        k++;
        next[j+1] = k;
    }
    return;
}

void KMP(string s, string p, int n, int m){
    vector<int> next(m, 0);
    buildNext(p,next,m);
    cout<<next[m/4]<<" "<<next[m/2]<<" "<<next[m*3/4]<<" \n";
    int i=0,j=0;
    while(i<n && j<m){
        if(s[i]==p[j]){
            i++;
            j++;   
        }
        else if(j==0) i++;
        else j=next[j];

        if(j==m){
            cout<<i-j<<" ";
            return;
        }
    }
    cout<<"-1"<<" ";
    return;
}

int main(){
    string s,p;
    int n,m;
    n=m=0;
    cin>>s>>p;
    while(s[n]) n++;
    while(p[m]) m++;
    KMP(s,p,n,m);
    return 0;
}
