#include <stdio.h>
int odd (int m)
{
  
  m=3*m+1;
  return m;
}
int even (int n)
{
  
  n=n/2;
  return n;
}
int calculate (int l)
{
  
  if (l%2==0)
  {
    l=even(l);
  }
  else
  {
    l=odd(l);
  }
    return l;
}
int main()
{
  int i;
  printf("A N+ please:\n");
  scanf("%d",&i);
  while (i!=1)
  {
  i=calculate(i);
  printf("%d",i);
  }
  return 0;
}