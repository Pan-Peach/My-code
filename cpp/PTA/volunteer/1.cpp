#include<bits/stdc++.h>
using namespace std;

int findMax(vector<int> &v, int start, int end){
    if(start==end) return v[start];
    int mid = start + (end - start)/2;
    int rmax = findMax(v, mid+1, end);
    int lmax = findMax(v, start, mid);
    return max(rmax, lmax);
}

int main(){
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    cout<<findMax(v, 0, n-1)<<endl;
    return 0;
}