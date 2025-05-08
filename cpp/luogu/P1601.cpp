#include<bits/stdc++.h>
using namespace std;

string a,b;
int aa[100],bb[100],c[100];
int top;

void highplus(){ 
    top=max(a.size(),b.size());  
    for(int i=0;i<top;i++){
        c[i]+=(aa[i]+bb[i]);
        if(c[i]>=10){
            if(i==top-1) top++;
            int tmp=c[i]/10;
            c[i]=c[i]%10;
            c[i+1]+=tmp;
        }
    }
}

int main(){
    cin>>a;
    cin>>b;
    for(int i=a.size()-1;i>=0;i--){
        aa[a.size()-i-1]=a[i]-48;
    }
    for(int i=b.size()-1;i>=0;i--){
        bb[b.size()-i-1]=b[i]-48;
    }
    highplus();
    for(int i=top-1;i>=0;i--) cout<<c[i];
    return 0;
}