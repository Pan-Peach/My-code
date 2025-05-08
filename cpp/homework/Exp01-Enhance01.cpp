#include<bits/stdc++.h>
using namespace std;

int main(){
    float x,y,z,A,B,C,D,d;
    cin>>x>>y>>z>>A>>B>>C>>D;
    d=abs(A*x+B*y+C*z+D)/sqrt(A*A+B*B+C*C);
    printf("%.3f",d);
    return 0;
}