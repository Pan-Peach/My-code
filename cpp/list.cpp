#include<bits/stdc++.h>
using namespace std;

int n,m;

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
    cin>>n>>m;
    buildnode();
    ysf();
    return 0;
}
