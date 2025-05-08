#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  /* char c1='\376',c2='\377',c3='\400';
    int i1=c1,i2=c2,i3=c3;
    printf("%d,%d,%d",i1,i2,i3);
    return 0; */
    char name[100];char account[100];char password[100];
    while(scanf("%s%s%s",name,account,password)==3){
        printf("%s %s %s\n",name,account,password);
    }
    
    return 0;
}