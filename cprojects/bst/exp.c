#include <stdio.h>
#include <stdlib.h>

struct info
{
    double x;
    int y;
    int a[3];
};

struct nod
{
    struct info info;
    struct nod *next;
};

int main()
{
    struct nod *n1 = (struct nod *)malloc(sizeof(struct nod));
    struct nod *n2 = (struct nod *)malloc(sizeof(struct nod));
    n1->info.x = 5.3;
    n1->info.y = 28;
    n1->info.a[0] = 1;
    n1->info.a[1] = 2;
    n1->info.a[2] = 10;
    n2->info = n1->info;
    n1->next = NULL;
    n2->next = NULL;
    printf("%lf\n%d\n%d %d %d\n", n2->info.x, n2->info.y, n2->info.a[0], n2->info.a[1], n2->info.a[2]);
    return 0;
}