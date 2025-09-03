#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int greater(int x,int y){
    if(x>y) return x;
    else return y;
}
int main(){
    int a[150],b[150];
    int topa=0,topb=0;
    memset(a,0,sizeof a);
    memset(b,0,sizeof b);
    char ch;
    freopen("testT3.txt","r",stdin);
    for(int i=0;i<2;i++){
        while((ch=getchar())!='\n'&&(ch=getchar())!=EOF){
            if(i==0){
                if(ch>='0'&&ch<='9') a[topa++]=ch-'0';
            }
            else{
                if(ch>='0'&&ch<='9') b[topb++]=ch-'0';
            }
        }
    }
    for(int i=0;i<topa;i++) printf("%d",a[i]);
    printf(" ");
    for(int i=0;i<topb;i++) printf("%d",b[i]);
    printf(" ");
    for(int i=topa-1;i>=topa/2;i--){
        int tmp=a[i];
        a[i]=a[topa-i-1];
        a[topa-i-1]=tmp;
    }
    for(int i=topb-1;i>=topb/2;i--){
        int tmp=b[i];
        b[i]=b[topb-i-1];
        b[topb-i-1]=tmp;
    }
    
    int c=greater(topa,topb);
    int cnt=0;
    for(int i=0;i<c;i++){
        int tmp=a[i]+b[i];
        if(tmp>=10){
            cnt++;
            a[i+1]++;
            tmp-=10;
        }
        a[i]=tmp;
    }
    printf("%d ",cnt);
    return 0;
}