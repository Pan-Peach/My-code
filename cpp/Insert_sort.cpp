#include<iostream>
using namespace std;

void Insert_sort(int *a,int n){
    for(int i=1;i<n;i++){
        if(a[i]<a[i-1]){
            int temp=a[i];
            for(int j=0;j<i;j++){
                if(temp<a[j]){
                    for(int k=i;k>j;k--) 
                    a[k]=a[k-1];
                    a[j]=temp;
                    break;
                }
               
            }
        }
    }
    return;
}

int main(){
    int a[100005],n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    Insert_sort(a,n);
    for(int i=0;i<n;i++) cout<<a[i]<<' ';
    cout<<endl;
  return 0;  
}