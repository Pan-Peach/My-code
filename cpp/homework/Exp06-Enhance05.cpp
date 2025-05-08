#include<bits/stdc++.h>
using namespace std;

char trans(int num){
    if(num<10) return num+'0';
    return num-10+'A';
}

int main(){
    unsigned int n,b;
    cin>>n>>b;
    int a[100];
    int index=0;
    while(n>=b){
        int tmp=n%b;
        a[index++]=tmp;
        n=(n-tmp)/b;
    }
    a[index++]=n;
    for(int i=index-1;i>=0;i--){
        cout<<trans(a[i]);
    }
    return 0;
}