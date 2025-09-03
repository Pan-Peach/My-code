#include<bits/stdc++.h>
using namespace std;

vector<int> ans;

vector<int> add(const vector<int>& a,const vector<int>& b){
    int lena=a.size();
    int lenb=b.size();
    int len=max(lena,lenb);
    vector<int> sum(len+1,0);
    for(int i=0;i<len;i++){
        if(i<lena) sum[i]+=a[i];
        if(i<lenb) sum[i]+=b[i];
        if(sum[i]>=10){
            sum[i+1]++;
            sum[i]%=10;
        }
    }
    if(sum.back()==0) sum.pop_back();

    return sum;
}

vector<int> mult(const vector<int>& a,int b){
    int len=a.size();
    vector<int> product;
    product=a;
    for(int i=1;i<b;i++){
        product=add(a,product);
    }
    return product;
}

vector<int> fact(int n){
    vector<int> ans;
    for(int i=1;i<=n;i++){
        vector<int> fac;
        fac.push_back(1);
        for(int j=1;j<=i;j++){
            fac=mult(fac,j);
        }
        ans=add(ans,fac);
    }
    return ans;
}

void printVector(const vector<int>& v) {
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it;
    }
    cout << endl;
}

int main(){
    int n;
    cin>>n;
    vector<int> ans;
    ans=fact(n);
    printVector(ans);
    return 0;
}