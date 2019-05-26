#include <stdio.h>
#include <stdlib.h>

int sorting_function(int *arr, int arr_len)
{
    int Activities=0;
    int i, j, k, tmp;
    for(k=arr_len/2; k>0; k /= 2)
        for (i=k; i< arr_len; i++)
        {
            tmp=arr[i];
            for (j=i; j >= k; j -= k)
            {
                Activities++;
                if (tmp < arr[j-k])
                {
                    Activities++;
                    arr[j] = arr[j-k];
                }
                else break;
            }
            arr[j]=tmp;
        }
    return Activities;
}

int main()
{
    int *a;
    int i, n;
    scanf("%d", &n);
    a = (int*)malloc(sizeof(int) * n);
    for (i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }
    sorting_function(a, n);
    for (i=0; i<n-1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[i]);
    return 0;
}
