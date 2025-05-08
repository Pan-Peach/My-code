#include<bits/stdc++.h>
using namespace std;

string s1,s2;
int nextval[1000001];

void prenext(){
    int j=0;
    for(int i=1;i<s2.size();i++){
        if(s2[j]==s2[i]){
            nextval[i]=++j;
            continue;
        }
        else{
            while(j>0){
                j=nextval[j-1];
                if(s2[j]==s2[i]){
                    nextval[i]=++j;
                    break;
                }
            }
        }
    }
}

void kmp(){
    int i=0,j=0;
    while(i<=s1.size()-s2.size()+1){
        while(j<s2.size()){
            if(s2[j]!=s1[i+j]) break;
            j++;
        }
        if(j==s2.size()){
            cout<<i+1<<'\n';
        }
        if(j==0){
            i++;
            continue;
        }
        else{
            i+=j-nextval[j-1];
            j=nextval[j-1];
        }
    }
}

int main(){
    cin>>s1>>s2;
    prenext();
    kmp();
    for(int i=0;i<s2.size()-1;i++){
        cout<<nextval[i]<<' ';
    }
    cout<<nextval[s2.size()-1];
    return 0;
}
