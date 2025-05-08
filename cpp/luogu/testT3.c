#include<stdio.h>
#include<string.h>
char str[20][100];
int main(){
    memset(str,0,sizeof str);
    int n;
    scanf("%d",&n);
    char chh;
    chh=getchar();
    for(int i=0;i<n;i++){
        int cnt=0;
        char ch;
        while((ch=getchar())!='\n'){
            str[i][cnt++]=ch;
        }
    }

    int flag=1;
    char strch[54];
    while(flag){
        flag=0;
        for(int i=0;i<n-1;i++){
            if(strcmp(str[i],str[i+1])>0){
                memset(strch,0,sizeof strch);
                strcpy(strch,str[i]);
                strcpy(str[i],str[i+1]);
                strcpy(str[i+1],strch);
                flag=1;
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%s\n",str[i]);
    }
    return 0;
}