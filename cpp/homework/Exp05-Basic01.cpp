#include<stdio.h>

int strlen(char* str){
    char ch;
    int len=0;
    while((ch=getchar())!=EOF){
        str[len]=ch;
        len++;
    }
    return len;
}

int main(){
    char in[1000];
    printf("%d",strlen(in));
    return 0;
}