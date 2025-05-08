#include<iostream>
using namespace std;

int main(){
    for(int i=0;i<1000;i+=7){
        if((i%2==1)&&(i%3==2)&&(i%5==4)&&(i%6==5)&&(i%7==0)){
            cout<<i;
            break;
        }
    }
    return 0;
}