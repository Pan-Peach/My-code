#include<bits/stdc++.h>
using namespace std;

int main(){
    int second,minute,hour,in;
    cin>>in;
    hour=(in-in%3600)/3600;
    in=in-hour*3600;
    minute=(in-in%60)/60;
    in=in-minute*60;
    second=in;
    if(hour>24) hour%=24;
    if(hour<10) cout<<0;
    cout<<hour<<':';
    if(minute<10) cout<<0;
    cout<<minute<<':';
    if(second<10) cout<<0;
    cout<<second;
    return 0;
}