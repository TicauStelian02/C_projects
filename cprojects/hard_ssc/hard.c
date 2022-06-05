#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, x, a[100000], count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &n);
        int st = 0, dr = count;
        while (st <= dr)
        {
            int m = (st + dr) / 2;
            if (a[m] < x)
            {
                dr = m - 1;
            }
            else
            {
                st = m + 1;
            }
        }
        if (st > count)
        {
            a[++count] = x;
        }
        else
        {
            a[st] = x;
        }
    }
    printf("%d\n", count);
    exit(EXIT_SUCCESS);
}