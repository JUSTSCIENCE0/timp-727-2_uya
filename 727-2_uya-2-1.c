#include <stdio.h>

int main()
{
 int new, last, res, n, i;
 res=1;
 scanf("%d", &n);
 scanf("%d", &new);
 for (i=2; i<=n; i++)
 {
  last=new;
  scanf("%d", &new);
  if (new<last) res=0;
 }
 printf("%d\n", res);
}

