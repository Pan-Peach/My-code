#include <stdio.h>
#include <malloc.h>

struct cell {  // 单链表结点结构体定义
    int x;
    struct cell *next;
};

struct cell *build(void) {  // 新建单链表，并将建好的单链表首结点地址返回
    struct cell *head, *tmp, *tail;
    head = tmp = tail = NULL;
    int n;
    scanf("%d",&n);
    while(n!=0){
        tmp=(struct cell*)malloc(sizeof(struct cell));
        tmp->x=n;
        tmp->next=NULL;
        if(head==NULL){
            head=tmp;
            tail=head;
        } 
        else{
            tail->next=tmp;
            tail=tail->next;
        }
        scanf("%d",&n);
    }
    return head;  
}

struct cell *sort(struct cell *head) {
    struct cell *p, *p0, *r, *r0, *q;
    p = p0 = r = r0 = q = NULL;
    p = head;
    while(p!=NULL){
        int flag=0;
        r=p->next;
        r0=p;
        while(r!=NULL){
            if(p->x>r->x){
                if(p0==NULL){
                    head=r;
                }
                else{
                    p0->next=r;
                }
                r0->next=p;
                q=p->next;
                p->next=r->next;
                r->next=q;
                p0=r;
                r0=p;
                flag=1;
            }
            else{
                r0=r;
            }
            r=r->next;
        }
        //printf("p0=%d p=%d r0=%d r=%d\n",p0->x,p->x,r0->x,r->x);
        if(flag){
            p=head;
            p0=NULL;
            continue;
        }
        p0=p;
        p=p->next;
    }
    return head;
}



void print(struct cell *head) {
    struct cell *t=head;
    while(t!=NULL){
        printf("%d ",t->x);
        t=t->next;
    }
}

void release(struct cell *head) {
    struct cell* t=head,*next;
    while(t!=NULL){
        next=t->next;
        free(t);
        t=next;
    }
    t=NULL;
}

int main(void) {
    struct cell *head;
    head = build();
    if (head!= NULL) {
        head = sort(head);
        print(head);
    } else
        printf("NULL");
    release(head);
    return 0;
}//真正的链表节点交换