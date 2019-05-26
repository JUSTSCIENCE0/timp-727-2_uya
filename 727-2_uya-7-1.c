#include <stdio.h>
#include <stdlib.h>

int sorting_function(int *arr, int left, int right)
{
    int l=left, r=right, tmp;
    int piv = arr[(l+r)/2];
    while (l <= r)
    {
    while (arr[l] < piv)
      l++;
    while (arr[r] > piv)
      r--;
    if (l <= r)
      {
          tmp=arr[l];
          arr[l]=arr[r];
          arr[r]=tmp;
          l++; r--;
      }
    }
    if (left<r) sorting_function(arr, left, r);
    if (right>l) sorting_function(arr, l, right);
    return 0;
}

int main()
{
    int *a;
    int i, n;
    scanf("%d", &n);
    a=(int*)malloc(n * sizeof(int));
    for (i=0; i<n; i++) scanf("%d", &a[i]);
    sorting_function(a, 0, n-1);
    for (i=0; i<n-1; i++) printf("%d ", a[i]);
    printf("%d\n", a[i]);
    return 0;
}
