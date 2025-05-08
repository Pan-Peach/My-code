#include<bits/stdc++.h>
using namespace std;

struct fushu{double real;double image;}c;

void out(){
    printf("%.2f",c.real);
    if(c.image!=0){
        if(c.image>0) printf("+%.2fi",c.image);
        else printf("-%.2fi",fabs(c.image));
    }
}

int main(){
    struct fushu a,b;
    cin>>a.real>>a.image>>b.real>>b.image;
    c.real=a.real+b.real;
    c.image=a.image+b.image;
    out();cout<<"    ";
    c.real=a.real-b.real;
    c.image=a.image-b.image;
    out();cout<<"    ";
    c.real=a.real*b.real-a.image*b.image;
    c.image=a.real*b.image+a.image*b.real;
    out();
    return 0;
}