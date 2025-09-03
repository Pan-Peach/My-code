#include<bits/stdc++.h>
using namespace std;
int a[7];
int main(){
    string s,st="{}[]()";
    char ch;
    while((ch=getchar())!='@'){
        switch (ch){
        case '{' : a[0]++;break;
        case '}' : a[1]++;break;
        case '[' : a[2]++;break;
        case ']' : a[3]++;break;
        case '(' : a[4]++;break;
        case ')' : a[5]++;break;
        default:
            break;
        }
    }
    if(a[0]!=a[1]) cout<<"{}";
    if(a[2]!=a[3]) cout<<"[]";
    if(a[4]!=a[5]) cout<<"()";
    if(a[0]==a[1]&&a[2]==a[3]&&a[4]==a[5]) cout<<"NULL";
    return 0;
}