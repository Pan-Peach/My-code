#include<bits/stdc++.h>
using namespace std;

string one[10]={"zero","one","two","tree","four","five","six","seven","eight","nine"};
string ten[10]={"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
string jishi[10]={"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

int main(){
    string s;
    cin>>s;
    int n=s.size()-1;
    for(int i=0;i<s.size()/2;i++){
        char ch=s[i];
        s[i]=s[n-i];
        s[n-i]=ch;
    }
    int tmp=n;
    if(n>2){
        cout<<"ERR";
        return 0;
    }
    while(tmp>=0){
        if(tmp==2){
            if(s[tmp]=='0'){
                tmp--;
                continue;
            }
            cout<<one[s[tmp]-'0']<<' '<<"houdred";
        } 
        if(tmp==1){
            if(s[tmp]=='0'){
                if(s[0]!='0'){
                cout<<' '<<"and"<<' '<<one[s[0]-'0'];
                break;
                }
                else{
                    break;
                }
            }
            if(n>1) cout<<' '<<"and"<<' ';
            if(s[tmp]=='1') cout<<ten[s[tmp-1]-'0'];
            else if(s[0]=='0') cout<<jishi[s[tmp]-'0'-2];
            else{
                cout<<jishi[s[tmp]-'0'-2]<<'-'<<one[s[0]-'0'];
            }     
        }
        if(n==0) cout<<one[s[tmp]-'0'];
        tmp--;
    }
    return 0;
}