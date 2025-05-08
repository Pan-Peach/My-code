#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;
const int maxn=100001;
struct student{
    student* pre;
    int num;
    student* next;
}que[maxn];

typedef student* studentptr;

studentptr insert(studentptr head, int n,int index,int dir){
    que[n].num=n;
    if(dir==0){
        if(que[index].pre==nullptr){
            que[n].next=que+index;
            que[index].pre=que+n;
            head=que+n;
        }
        else{
            que[n].next=que+index;
            que[n].pre=que[index].pre;
            que[n].pre->next=que+n;
            que[index].pre=que+n;
        }                                                                                                       
    }
    else{
        if(que[index].next==nullptr){
            que[index].next=que+n;
            que[n].pre=que+index;
        }
        else{
            que[n].pre=que+index;
            que[n].next=que[index].next;
            que[index].next=que+n;
            que[n].next->pre=que+n;
        }
    }
    return head;
}

studentptr deletstu(studentptr head,int index){
    if(que[index].pre==nullptr){
        head=que[index].next;
        que[index].pre=nullptr;
    }
    else if(que[index].next==nullptr){
        que[index].pre->next=nullptr;
    }
    else{
        que[index].pre->next=que[index].next;
        que[index].next->pre=que[index].pre;
    }
    return head;
}

void printstu(studentptr head){
    studentptr cur=head;
    if(head==nullptr) return;
    while(cur->next!=nullptr){
        printf("%d ",cur->num);
        cur=cur->next;
    }
    printf("%d",cur->num);
    return;
}

int main(){
//    freopen("P1160_3.in","r",stdin);
    bool hasdelete[maxn];
    memset(hasdelete,0,sizeof hasdelete);
    int n,m,index,dir;
    studentptr head=que+1;
    que[1].num=1;que[1].next=nullptr;que[1].pre=nullptr;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d %d",&index,&dir);
        head = insert(head,i,index,dir);
    }
    cin>>m;
    for(int i=0;i<m;i++){
        scanf("%d",&index);
        if(!hasdelete[index]){
        head=deletstu(head,index);
        hasdelete[index]=1;
        }
    }
    printstu(head);
    return 0;
}
