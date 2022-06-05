#include <stdio.h>
#include <stdlib.h>

struct info_Node
{
    double key;
};

struct Node
{
    struct info_Node info;
    struct Node *link;
};

void push_in_list(struct Node **a, struct Node *new_info);
void read_list(FILE *f, struct Node **a);
void display_list(struct Node *a);
__int8_t is_empty(FILE *f);
void merge_sort(struct Node **a);
void split(struct Node *a, struct Node **left_sublist, struct Node **right_sublist);
struct Node *_merge(struct Node *x, struct Node *y);
void clear_memory(struct Node **a);

__int32_t main()
{
    FILE *f = fopen("data.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopen() failed at line #%d at opening file in %s\n", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
    }
    struct Node *a = NULL;
    read_list(f, &a);
    fclose(f);
    printf("Original list:\n");
    display_list(a);
    merge_sort(&a);
    printf("List after sorting:\n");
    display_list(a);
    clear_memory(&a);
    exit(EXIT_SUCCESS);
}

void clear_memory(struct Node **a)
{
    while (*a)
    {
        struct Node *temp = *a;
        *a = (*a)->link;
        temp->link = NULL;
        free(temp);
    }
}

void merge_sort(struct Node **a)
{
    if (!(*a) || !((*a)->link))
    {
        return;
    }
    struct Node *x, *y, *head = *a;
    split(head, &x, &y);
    merge_sort(&x);
    merge_sort(&y);
    *a = _merge(x, y);
}

void split(struct Node *a, struct Node **x, struct Node **y)
{
    struct Node *leftmid = a, *leftlast = a->link;
    while (leftlast)
    {
        leftlast = leftlast->link;
        if (leftlast)
        {
            leftmid = leftmid->link;
            leftlast = leftlast->link;
        }
    }
    *x = a;
    *y = leftmid->link;
    leftmid->link = NULL;
}

struct Node *_merge(struct Node *x, struct Node *y)
{
    struct Node *new_a = NULL;
    if (!x)
        return y;
    if (!y)
        return x;
    if (x->info.key <= y->info.key)
    {
        new_a = x;
        new_a->link = _merge(x->link, y);
    }
    else
    {
        new_a = y;
        new_a->link = _merge(x, y->link);
    }
    return new_a;
}

void display_list(struct Node *a)
{
    if (!a)
    {
        printf("The list is empty.\n");
        return;
    }
    while (a)
    {
        printf("%.2lf ", a->info.key);
        a = a->link;
    }
    printf("\n");
}

__int8_t is_empty(FILE *f)
{
    if (getc(f) == EOF)
        return 1;
    return 0;
}

void read_list(FILE *f, struct Node **a)
{
    if (is_empty(f))
    {
        *a = NULL;
        return;
    }
    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
        struct Node *new_info = (struct Node *)malloc(sizeof(struct Node));
        fscanf(f, "%lf ", &(new_info->info.key));
        push_in_list(&(*a), new_info);
    }
}

void push_in_list(struct Node **a, struct Node *new_info)
{
    new_info->link = *a;
    *a = new_info;
}