#include<bits/stdc++.h>
using namespace std;
//#define DEBU


class stree{
private:
    class node{
    public:
        int l, r;
        long long sum, lazy;
        node(): l(0), r(0), sum(0), lazy(0) {}
        node(int l, int r): l(l), r(r), sum(0), lazy(0) {}
    };
    vector<node> tree;
    vector<long long> oridata;
public:
    stree(int n){
        tree.resize(4*n+1);
        oridata.resize(n+1);
    }

    void read_data(int n){
        for(int i=1; i<=n; i++){
            scanf("%lld", &oridata[i]);
        }
    }

    void ori_sum(){
        long long ans=0;
        int n=oridata.size();
        for(int i=1;i<n;i++){
            ans+=oridata[i];
        }
        printf("%lld\n",ans);
        return;
    }

    void build(int l, int r, int idx){
        tree[idx].l=l;
        tree[idx].r=r;
        if(l==r){
            tree[idx].sum=oridata[l];
            return;
        }            
        int mid=(l+r)/2;
        build(l,mid,idx*2);
        build(mid+1,r,idx*2+1);
        tree[idx].sum=tree[idx*2].sum+tree[idx*2+1].sum;
        return;
    }

    void pushup(int idx){
        tree[idx].sum=tree[idx*2].sum+tree[idx*2+1].sum;
        return;
    }

    void pushdown(int idx){
        if(tree[idx].l==tree[idx].r){
            tree[idx].lazy=0;
            return;
        } 
        if(tree[idx].lazy){
            int left=idx*2;
            int right=idx*2+1;
            tree[left].sum+=tree[idx].lazy*(tree[left].r-tree[left].l+1);
            tree[right].sum+=tree[idx].lazy*(tree[right].r-tree[right].l+1);
            tree[left].lazy+=tree[idx].lazy;
            tree[right].lazy+=tree[idx].lazy;
            tree[idx].lazy=0;
        }
        return;
    }
    
    void add(int l, int r, long long val, int idx){
        if(tree[idx].l>=l&&tree[idx].r<=r){
            tree[idx].sum+=val*(tree[idx].r-tree[idx].l+1);
            tree[idx].lazy+=val;
            return;
        }
        pushdown(idx);
        pushup(idx);
        int mid=(tree[idx].l+tree[idx].r)/2;
        if(r<=mid) add(l,r,val,idx*2);
        else if(l>mid) add(l,r,val,idx*2+1);
        else{
            add(l,mid,val,idx*2);
            add(mid+1,r,val,idx*2+1);
        }
        pushup(idx);
        return;
    }

    long long query(int l, int r, int idx){
        if(l>r) return -1;
        if(tree[idx].l>=l&&tree[idx].r<=r){
            return tree[idx].sum;
        }
        pushdown(idx);
        int mid=(tree[idx].l+tree[idx].r)/2;
        long long ans=0;
        if(r<=mid) ans+= query(l,r,idx*2);
        else if(l>mid) ans+= query(l,r,idx*2+1);
        else ans+= query(l,mid,idx*2)+query(mid+1,r,idx*2+1);
        return ans;
    }
    
};

int main(){
    #ifdef DEBU
    freopen("P3372_20.in", "r", stdin);
    #endif
    int n,m;
    cin >> n >> m;
    stree tree(n);
    tree.read_data(n);
    tree.build(1,n,1);
//    tree.ori_sum();
    for(int i=0;i<m;i++){
        int op;
        scanf("%d", &op);
        if(op==1){
            int x,y;
            long long k;
            scanf("%d%d%lld", &x, &y, &k);
            tree.add(x,y,k,1);
        }
        else if(op==2){
            int x,y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", tree.query(x,y,1));
        }
        else{
            printf("Error\n");
        }
    }
    return 0;
}