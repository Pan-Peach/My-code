#include<stdio.h>
#include<malloc.h>
struct farlei_item{
int numerator,denominator;//分子、分母
struct farlei_item*next;//连接部分
};
typedef struct farlei_item*farleipointer;
void buildfarlei(farleipointer left,farleipointer right,int n);
int gcd(int x,int y){/*求最大公约数*/
    int tmp=x;
    if(y>x){
        x=y;
        y=tmp;
    }
    if(y==0) return x;
    return gcd(y,x%y);
}
/*构造法雷序列,并返回序列头指针*/
farleipointer farlei(int n){
int i,j;
farleipointer fn,r,r0,p;
fn=r=r0=p=NULL;
if(n<1)return NULL;//如果n<=0,则没有法雷序列
fn=(farleipointer)malloc(sizeof(struct farlei_item));//构造0/1
fn->numerator=0;
fn->denominator=1;
p=(farleipointer)malloc(sizeof(struct farlei_item));//构造1/1
p->numerator=1;
p->denominator=1;
fn->next=p;
p->next=NULL;
buildfarlei(fn,p,n);
return fn;
}

void buildfarlei(farleipointer left,farleipointer right,int n){
    int a,b;
    farleipointer mid=(farleipointer)malloc(sizeof(struct farlei_item));
    a=left->numerator+right->numerator;
    b=left->denominator+right->denominator;
    a/=gcd(a,b);
    b/=gcd(a,b);
    if(b<=n){

        mid->numerator=a;mid->denominator=b;
        left->next=mid;mid->next=right;
        buildfarlei(left,mid,n);buildfarlei(mid,right,n);
    }
    return;
}

void print(farleipointer fn){//输出fn引导的法雷序列
    farleipointer cur=fn;
    while(cur->next!=NULL){
        printf("%d/%d ",cur->numerator,cur->denominator);
        cur=cur->next;
    }
    printf("%d/%d",cur->numerator,cur->denominator);
    return;
}
void release(farleipointer head){//释放单链表空间,head是单链表首结点指针
    farleipointer pre,cur;
    if(head==NULL) return;
    pre=head;
    cur=pre->next;
    while(cur!=NULL){
        free(pre);
        pre=cur;
        cur=cur->next;
    }
    return;
}
int main(void){
int n;
farleipointer fn;
scanf("%d",&n);
fn=farlei(n);//生成n级法雷序列
if(fn!=NULL)
print(fn);
else
printf("NULL");
release(fn);
return 0;
}