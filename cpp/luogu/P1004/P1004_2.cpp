#include<bits/stdc++.h>
using namespace std;
int a[11][11],n;
bool mem[11][11];
class nxtm{
    public:
        int val;
        nxtm* b;
        nxtm* r;
        nxtm(){val=0;b=nullptr;r=nullptr;}
        nxtm* build(nxtm* cur, int x,int y){
            for(int j=0;j<n;j++){
                for(int i=0;i<n;i++){
                    if(a[i][j]&&!mem[i][j]){
                        cur->b=new nxtm();
                        cur->b->val=a[i][j];
                        mem[i][j]=1;                         
                    }
                }
            }
        }
};

int main(){
    cin>>n;
    int x,y,tmp;
    for(int i=0;i<100;i++){
        cin>>x>>y>>tmp;
        a[x][y]=tmp;
        if(x==0&&y==0) break;
    }
}