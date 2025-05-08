#include<iostream>
using namespace std;
int a[20000][21000],b[21010],ans[100100],cnt=0;
int m,n,p,q,act,t,a1,a2;

void initialize(){
    for(int i=0;i<p+1;i++){
        for(int j=0;j<q+1;j++){
            a[i][j]=0;
        }
    }
}
void filla(){
    initialize();
    for(int i=0;i<p;i++){
        for(int j=0;j<q;j++){
            a[i][j]=b[i*q+j];
        }
    }
}

void reverse(){
    for(int i=0;i<q;i++){
        for(int j=0;j<p;j++){
            b[i*p+j]=a[j][i];
        }
    }
    initialize();
    int temp=p;
    p=q;
    q=temp;
    filla();
}

void fillb(){
    for(int i=0;i<p;i++){
         for(int j=0;j<q;j++){
               b[i*q+j]=a[i][j];
         }
     }
}

int main(){

    cin>>n>>m>>t;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=0;i<n;i++){
         for(int j=0;j<m;j++){
               b[i*m+j]=a[i][j];
         }
     } 
     p=n;q=m; 
    while(t--){
        cin>>act>>a1>>a2;
        if(act==1) {
            p=a1;q=a2;
            filla();
        }
        if(act==2) {
            reverse();
        }
        if(act==3){
            ans[cnt]=a[a1][a2];
            cnt++;
        }
    }
    for(int i=0;i<cnt;i++) cout<<ans[i]<<"\n";
    return 0;
}