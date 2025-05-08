#include <stdio.h>
#include <malloc.h>
struct cell { //单链表结点结构体定义
 int x;
 struct cell* next;
};
struct cell* build(void) { //新建单链表，并将建好的单链表首结点地址返回
    struct cell* head,*tmp,*p;
    head = tmp = p = NULL;
    int n;
    scanf("%d",&n);
    if(n==0) return head;
    else{
        head=(struct cell*)malloc(sizeof(struct cell));
        head->x=n;
        head->next=(struct cell*)malloc(sizeof (struct cell));
    }
    p=head->next;
    while(~scanf("%d",&n)){
        if(n==0){
            p->next=NULL;
            break;
        }
        else{
            p->x=n;
            p->next=(struct cell*)malloc(sizeof (struct cell));
            p=p->next;
        }
    }

 return head;//返回单链表头
}
void print(struct cell* head) {//打印整个单链表,head是指向单链表首结点的指针
    struct cell* p=head;
    if(head==NULL){
        printf("NULL");
        return;
    }
    while(p->next->next!=NULL){
        printf("%d ",p->x);
        p=p->next;
    }
    printf("%d",p->x);
    return;
}
struct cell* del2one(struct cell* head) {//删除重复结点只保留一个，head是单链表首结点指针
    struct cell* p1=head,*p2=head,*tmp,*fro;
    int n;
    if(head==NULL) return head;
    while(p1->next!=NULL){
        n=p1->x;
        fro=p1;
        p2=p1->next;
        while(p2->next!=NULL){
            if(p2->x==n){
                tmp=p2;
                fro->next=p2->next;
                p2=fro->next;
                free(tmp);
            }
            else{fro=fro->next;
            p2=p2->next;}
        }
        p1=p1->next;
    }

    return head;//返回删除重复结点的单链表头
}
struct cell* mid(struct cell* head){//寻找链表中间位置结点地址并返回，head是单链表首结点指针
    int len=0;
    struct cell* cur=head;
    if(head==NULL) return head;
    while(cur->next!=0){
        len++;
        cur=cur->next;
    }
    cur=head;
    int mid=len/2;
    if(mid==0) return head;
    else if(len%2==0) mid=mid-1;
    while(mid--){
        cur=cur->next;
    }
    return cur;
}
void release(struct cell* head) {//释放单链表空间,head是指向单链表首结点的指针
    struct cell* p=head,*tmp;
    if(head==NULL) return;
    while(p->next!=NULL){
        tmp=p->next;
        free(p);
        p=tmp;
    }
    free(p);
    return;
}
	int main(void) {
 struct cell* head,*half;
 head = build();
 half = mid(head);
 if(half!=NULL)
        print(half);
    else
        printf("NULL");
 release(head);
}