#include<bits/stdc++.h>
using namespace std;
const int maxn =10;
char post[maxn],in[maxn],pre[maxn];
int precnt=0;
bool done[maxn];
class bTree{
    private:
        char val;
        bTree *l,*r;
    public:
        bTree(){
            val=0;
            l=nullptr;
            r=nullptr;
        }
        bTree* build(char* l, char* r,bTree* root,int n){
            if(l>=r) return nullptr;
            char* mid;
            bool flag=0;
            for(int i=n-1;i>=0;i--){
                if(done[i]) continue;
                for(char* j=l;j<r;j++){
                    if(post[i]==*j){
                        mid=j;
                        root=new bTree();
                        root->val=*mid;
                        done[i]=1;
                        flag=1;
                        break;
                    }
                }
                break;
            }
            if(!flag) return nullptr;
            root->r=build(mid,r,root->r,n);
            root->l=build(l,mid,root->l,n);
            return root;
        }
        void preorder(bTree* root){
            if(root==nullptr) return;
            pre[precnt++]=root->val;
            preorder(root->l);
            preorder(root->r);
        }
};

int main(){
//    freopen("P1030.in","r",stdin);
    scanf("%s",in);
    scanf("%s",post);
    bTree* root;
    root=root->build(in,in+strlen(in),root,strlen(in));
    root->preorder(root);
    for(int i=0;i<precnt;i++){
        cout<<pre[i];
    }
    return 0;
}