#include<stdio.h>

void count(char * str, int * upper, int *lower, int *space, int *num, int*other,int len){
    int i=0;
    for(int i=0;i<len;i++){
        if(str[i]>='A'&&str[i]<='Z') (*upper)++;
        else if(str[i]>='a'&&str[i]<='z') (*lower)++;
        else if(str[i]==' ') (*space)++;
        else if(str[i]>='0'&&str[i]<='9') (*num)++;
        else (*other)++;
    }
}

int main(){
    char in[1000];
    char ch;
    int len=0;
    int upper=0,lower=0,space=0,num=0,other=0;
    while((ch=getchar())!=EOF){
        in[len++]=ch;
    }
    count(in,&upper,&lower,&space,&num,&other,len);
    printf("%d %d %d %d %d",upper,lower,space,num,other);
    return 0;
}