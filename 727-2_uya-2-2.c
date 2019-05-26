#include <stdio.h>

int main()
{
 int i, n, a, sum;
 scanf("%d", &n);
 sum=0;
 for(i=0; i<n; i++)
 {
  scanf("%d", &a);
  sum=sum+a*a;
 }
 printf("%d\n", sum);
}

