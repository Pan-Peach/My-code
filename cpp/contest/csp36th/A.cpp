#include<bits/stdc++.h>
using namespace std;

class robot{
public:
    int size;
    int x,y;
    robot(int siz){
        size=siz;
    }

    bool isin(){
        if(x>=1&&x<=size&&y>=1&&y<=size) return 1;
        return 0;
    }

    void f(){
        y++;
        if(isin()) return;
        y--;
    }
    void b(){
        y--;
        if(isin()) return;
        y++;
    }
    void l(){
        x--;
        if(isin()) return;
        x++;
    }
    void r(){
        x++;
        if(isin()) return;
        x--;
    }
    void move(int sx,int sy,string op){
        x=sx;y=sy;
        for(auto it:op){
            if(it=='f') f();
            else if(it=='b') b();
            else if(it=='l') l();
            else if(it=='r') r();
            else {};
        }
        cout<<x<<' '<<y<<'\n';
        return;
    }
};

int main(){
    int n,k;
    cin>>n>>k;
    robot robot(n);

    for(int i=0;i<k;i++){
        int sx,sy;
        string op;
        cin>>sx>>sy>>op;
        robot.move(sx,sy,op);
    }
    return 0;
}