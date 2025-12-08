#include<bits/stdc++.h>
using namespace std;

class ST{
private:
    int n;
    vector<int> lg2;
    vector<vector<int>> st;
public:
    ST(const vector<int>& a){
        n = a.size();
        lg2.resize(n+1);
        for(int i=2; i<=n; i++) lg2[i] = lg2[i/2] + 1;
        int k = lg2[n];
        st.resize(n, vector<int>(k+1));
        for(int i=0; i<n; i++) st[i][0] = a[i];
        for(int j=1; j<=k;j++){
            for(int i=0; i+(1<<j)<=n; i++){
                int a = st[i][j-1];
                int b = st[i+(1<<(j-1))][j-1];
                st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r){
        int k = lg2[r-l+1];
        return max(st[l][k], st[r-(1<<k)+1][k]);
    }
};

int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for(int i=0; i<n; i++) scanf("%d", &a[i]);  
//    vector<pair<int,int>> q(m);
    ST st(a);
    for(int i=0; i<m; i++){
        int l,r;
        scanf("%d%d", &l, &r);
        printf("%d\n", st.query(l-1, r-1));
    }
    return 0;
}