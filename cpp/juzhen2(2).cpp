#include<iostream>
using namespace std;

int p,q,t,act,a1,a2;
int a[10050],b[10050],ans[100005],cnt=0;

void reverse(){
    for(int i=0;i<q*p;i++) b[i]=a[i];
    swap(p,q);
    for(int i=0;i<p;i++){
        for(int j=0;j<q;j++){
            a[i*q+j]=b[j*p+i];
        }
    }
    
}

int main(){
    cin>>p>>q>>t;
    for(int i=0;i<p*q;i++) cin>>a[i];
    while(t--){
        cin>>act>>a1>>a2;
        if(act==1){
            p=a1;q=a2;
        }
        if(act==2) reverse();
        if(act==3){
            ans[cnt]=a[q*a1+a2];
            cnt++;
        }
    }
    for(int i=0;i<cnt;i++) cout<<ans[i]<<"\n";
    return 0;
}