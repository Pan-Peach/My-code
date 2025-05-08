#include<stdio.h>

void qsort(int* a,int start,int end){
    if(start>=end) return;
    int i=start,j=end;
    int tmp=a[i];
    while(i<j){
        while(i<j&&tmp<=a[j]) j--;
        a[i]=a[j];
        while(i<j&&tmp>=a[i]) i++;
        a[j]=a[i];
    }
    a[i]=tmp;
    qsort(a,start,i-1);
    qsort(a,j+1,end);
    return;
}

int main(){
    int n,m,a[2505];
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int tmp;
            scanf("%d",&tmp);
            a[i*m+j]=tmp;
        }
    }
    qsort(a,0,n*m-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d",a[i*m+j]);
            if(j!=m-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}