#include<iostream>
using namespace std;

int main(){
    int gender,age;
    cin>>gender>>age;
    if(gender==1){
        if(age>70) cout<<70;
        if(age>65&&age<=70) cout<<50;
        if(age<=65) cout<<"NULL";
    }
    if(gender==2){
        if(age>65) cout<<70;
        if(age>60&&age<=65) cout<<45;        
        if(age<=60) cout<<"NULL";
    }
    return 0;
}