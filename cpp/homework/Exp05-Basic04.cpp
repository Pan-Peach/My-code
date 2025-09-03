#include<stdio.h>
#include<string.h>

void deletc(char* str,int start,int* len){
    for(int i=start;i<=(*len);i++){
        str[i]=str[i+1];
    }
    return;
}

int main(){
    int v,w;
    scanf("%d%d",&v,&w);
    char in[270];
    int len=0;
    char ch;
    ch=getchar();
    gets(in);
    len=strlen(in);
    while(w--){
        deletc(in,v-1,&len);
    }
    len=strlen(in);
    for(int i=0;i<len;i++) printf("%c",in[i]);
    return 0;
}