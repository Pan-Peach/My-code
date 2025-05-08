#include<iostream>
using namespace std;

void Selection_sort(int *a,int n){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(a[j]<a[i]) swap(a[j],a[i]);
        }
    }
    return;
}

int main(){
    int a[100005]={0},n=0;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    Selection_sort(a,n);
    cout<<a[0];
    for(int i=1;i<n;i++) cout<<' '<<a[i];
    return 0;
}