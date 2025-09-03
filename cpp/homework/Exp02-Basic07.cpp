#include<iostream>
using namespace std;

int main(){
    bool check[100]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    int a;
    cin>>a;
    if(a%3==0) check[3]=1;
    if(a%5==0) check[5]=1;
    if(a%7==0) check[7]=1;
    int cnt=0;
    for(int i=1;i<8;i++){
        if(check[i]==1) {
            if(cnt!=0) cout<<',';
            cout<<i;
            cnt++; 
        }    
            
    }
    if(cnt==0) cout<<"NULL";
    return 0;
}