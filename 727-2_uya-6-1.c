#include <stdio.h>
#include <stdlib.h>

int sorting_function(int *arr, int arr_len)
{
    int Activities=0, i, intstep, tmp;
    double fakt = 1.2473309;
    double step = arr_len - 1;
    while (step >= 1)
    {
        intstep=(int)(step+0.5);
        for (i = 0; i + intstep < arr_len; i++)
        {
            Activities++;
            if (arr[i] > arr[i + intstep])
            {

                tmp=arr[i];
                arr[i]=arr[i + intstep];
                arr[i+intstep]=tmp;
                Activities++;
            }
        }
        step /= fakt;
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
