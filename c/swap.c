#include<stdio.h>
const int N=30;
void swap(char *x,char *y)
{
	for(int i=0;i<N;i++){
        char temp=*(x+i);
        *(x+i)=*(y+i);
        *(y+i)=temp;
    }
    return;
		
}
int main()
{
	char str1[N];
	char str2[N];
	printf("请输入个字符串：\n");
	gets(str1);
	printf("请输入另一个字符串：\n");
	gets(str2);
	printf("交换前:\n");
	puts(str1);
	puts(str2);
	swap(str1,str2);
	printf("交换后:\n");
	puts(str1);
	puts(str2);
	return 0;
}