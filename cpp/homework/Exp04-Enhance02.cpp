#include<bits/stdc++.h>
using namespace std;

int n,m,s;

struct listnode{
    int v;
    listnode* nxt;
};
listnode* head;
listnode* tail;

void buildnode(){
    listnode* head=new listnode();
    head->v=1;
    tail=head;
    for(int i=2;i<=n;i++){
        listnode* newnode;
        newnode=new listnode();
        newnode->v=i;
        newnode->nxt=NULL;
        tail->nxt=newnode;
        tail=newnode;
    }
    tail->nxt=head;
    return;
}

void ysf(){
    head=tail->nxt;
    listnode* cur=head,*tmp,*pre=tail;
    int cnt=0;
    while(cur!=pre){
        cnt++;
        if(cnt==m){
            cout<<cur->v<<' ';
            tmp=cur->nxt;
            free(cur);
            pre->nxt=tmp;
            cur=pre->nxt;
            cnt=0;
        }
        else{
            pre=cur;
            cur=cur->nxt;
        }
    } 
    cout<<cur->v;  
    return;
}

int main(){
    int a[1000];
    cin>>n>>s>>m;
/*    buildnode();
    ysf(); */
    for(int i=0;i<n;i++) a[i]=i+1;
    int cur=s-1;
    while(n>=1){
        cur+=m-1;
        if(cur>=n) cur%=n;
        cout<<a[cur]<<' ';
        for(int i=cur;i<n;i++){
            a[i]=a[i+1];
        }
        n--;
    }
    return 0;
}