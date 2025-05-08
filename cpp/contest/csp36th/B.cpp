#include<bits/stdc++.h>
using namespace std;

class land{
public:
    vector<int> a;
    vector<int> b;
    vector<int> w;

    land(int n){
        a.resize(n+1,0);
        b.resize(n+1,0);
        w.resize(n+1,0);
    }

    void read(int n){
        for(int i=0;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
        }
        return;
    }

    void CptW(int n){
        int str=0,now=0;
        for(int i=1;i<=n;i++){
            int mem=b[i];
            b[i]=0;
            str=0;now=0;
            for(int j=0;j<=n;j++){
                int dif=now-a[j];
                if(dif<0){
                    str+=-dif;
                    now=0;
                }
                else{
                    now-=a[j];
                }
                if(j+1>n) continue;
                now+=b[j+1];
            }
            w[i]=str;
            b[i]=mem;
        }
        return;
    }

    void prtans(int n){
        for(int i=1;i<=n;i++){
            if(i>1) cout<<' ';
            cout<<w[i];
        }
        return;
    }

};

int main(){
    int n;
    cin>>n;
    land land(n);
    land.read(n);
    land.CptW(n);
    land.prtans(n);
    return 0;
}