#include<iostream>
using namespace std;
int main(){
    int data;
    cin>>data;
    for(int i=0;i<data;i++){
        if(i%11==0) cout<<i<<' ';
    }
    return 0;
}