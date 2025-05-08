#include<bits/stdc++.h>
const int maxn=1000001;
int pre[maxn],in[maxn],post[maxn],pr,innum,po;
class bTree{
    public  :
        int val;
        bTree* l;
        bTree* r;
        bTree(){
            val=0;
            l=nullptr;
            r=nullptr;
        } 
        void preorder(bTree* cur){
            if(cur==nullptr) return;
            if(cur->val!=0)pre[pr++]=cur->val;
            preorder(cur->l);
            preorder(cur->r);
        }
        void printpre(){
            for(int i=0;i<pr-1;i++){
                std::cout<<pre[i]<<' ';
            }
            printf("%d",pre[pr-1]);
        }
        void inorder(bTree* cur){
            if(cur==nullptr) return;
            inorder(cur->l);
            in[innum++]=cur->val;
            inorder(cur->r);
        } 
        void printin(){
            for(int i=0;i<innum-1;i++){
                std::cout<<in[i]<<' ';
            }
            printf("%d",in[innum-1]);
        }        
        void postorder(bTree* cur){
            if(cur==nullptr) return;
            postorder(cur->l);
            postorder(cur->r);
            post[po++]=cur->val;
        }  
        void printpost(){
            for(int i=0;i<po-1;i++){
                std::cout<<post[i]<<' ';
            }
            printf("%d",post[po-1]);
        }        
};
bTree que[maxn];
        bTree* bulid(bTree* head){
            int n,lv,rv;           
            scanf("%d",&n);
            for(int i=1;i<=n;i++){
                scanf("%d %d",&lv,&rv);
                que[i].val=i;
                if(lv!=0)que[i].l=que+lv;
                if(rv!=0)que[i].r=que+rv;
            }
            return que+1;
        } 

int main(){
    freopen("B3642_e.in","r",stdin);
    bTree* head;
    head=bulid(head); 
    head->preorder(head);
    head->printpre();
    std::cout<<'\n';
    head->inorder(head);
    head->printin();
    std::cout<<'\n';
    head->postorder(head);
    head->printpost();
    return 0;
}