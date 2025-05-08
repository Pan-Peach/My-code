#include<bits/stdc++.h>
using namespace std;
const float pai=3.1415926;

int main(){
    float a,x,y;
    cin>>a>>x;
    float ans=sin(x)/(a*x)+abs(cos(pai*x/2));
    printf("%.3f",ans);
    return 0;
}