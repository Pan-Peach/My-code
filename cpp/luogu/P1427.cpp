#include<iostream>
using namespace std;
int main(){
    int a[110]={0};
    int i=0;
    while(cin>>a[i]){
        if(a[i]==0) break;
        i++;
    }
    i--;
    while(i>=0){
        cout<<a[i]<<' ';
        i--;
    }
    return 0;
}