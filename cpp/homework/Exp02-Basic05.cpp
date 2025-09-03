#include<iostream>
using namespace std;
 int main(){
    float a;
    cin>>a;
    a=1+1/(1+1/(1+1/(1+1/(1+1/a))));
    printf("%.3f",a);
    return 0;
 }