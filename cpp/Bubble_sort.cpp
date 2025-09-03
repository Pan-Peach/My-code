#include<iostream>
using namespace std;

void Bubble_sort(int* arr  ,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);            
        }
    }
    return;
}

int main(){
    int a[100005]={0},n=0;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    Bubble_sort(a,n);
    for(int i=0;i<n;i++){
        if(i<n-1) cout<<a[i]<<' ';
        else cout<<a[i];
    }
    return 0;
}