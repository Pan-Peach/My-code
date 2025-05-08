#include<stdio.h>
#include<malloc.h>
struct cell{//单链表结点结构体定义
int x;
struct cell*next;
};
struct cell*build(void){//新建单链表，并将建好的单链表首结点地址返回
struct cell*head,*tmp,*p;
head=tmp=p=NULL;
int n;
scanf("%d",&n);
if(n==0) return head;
head=(struct cell*)malloc(sizeof(struct cell));
head->x=n;
p=head;
p->next=NULL;
while(~scanf("%d",&n)){
    if(n==0) return head;
    p->next=(struct cell*)malloc(sizeof(struct cell));
    p=p->next;
    p->x=n;
    p->next=NULL;
}
return head;//返回单链表头
}
struct cell*back(struct cell*head,int k){//求链表倒数第k个结点，head是单链表首结点指针
    struct cell* cur=head;
    int len=0;
    if(head==NULL) return head;
    while(cur!=NULL){
        len++;
        cur=cur->next;
    }
    int desti=len-k;
    cur=head;
    if(desti<0) return NULL;
    while(desti--){
        cur=cur->next;
    }
    return cur;
}
struct cell*sort(struct cell*head){//递增排序链表，head是单链表首结点指针
if(head==NULL) return head;
struct cell*p,*p0,*r,*r0,*q,*cur;
p=p0=r=r0=q=NULL;
p=head;
cur=head;
bool  flag=true;
int len=0;
while(cur!=0){
    len++;
    cur=cur->next;
}
if(len==1) return head;
p0=head->next;
while(flag){
    flag=0;
    p=head;
    p0=head->next;
    while(p0!=NULL){
        if(p->x>p0->x){
            int tmp=p->x;
            p->x=p0->x;
            p0->x=tmp;
            flag=1;
        }
        p=p0;
        p0=p0->next;        
    }
}
return head;
}/*sort*/
void print(struct cell* head) {//打印整个单链表,head是单链表首结点指针
    if(head==NULL) printf("NULL");
    struct cell* cur=head;
    while(cur->next!=NULL){
        printf("%d ",cur->x);
        cur=cur->next;
    }
    printf("%d",cur->x);
    return;
}
void release(struct cell*head){//释放单链表空间,head是单链表首结点指针
    struct cell* pre=head,*cur;
    if(head==NULL) return;
    cur=pre->next;
    while(cur!=NULL){
        free(pre);
        pre=cur;
        cur=cur->next;
    }
    return;
}
int main(void){
 struct cell* head;
 head= build();
 if (head != NULL) {
 head = sort(head);
 print(head);
 }else
 printf("NULL");
 release(head);
 return 0;
}