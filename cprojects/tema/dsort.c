#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct info
{
    double nr;
} Info;

typedef struct Node
{
    Info inf;
    struct Node *link;
} List;

List *read_list(FILE *fin);
void display_list(List *head);
void split(List *head, List **x, List **y);
void merge_sort(List **head, int8_t compare(const void *a, const void *b));
List *merge(List *x, List *y, int8_t compare(const void *a, const void *b));
void clear(List **head);
int8_t compare_cresc(const void *a, const void *b);
int8_t compare_descresc(const void *a, const void *b);
int8_t dont_compare();

int32_t main()
{
    FILE *fin = fopen("elem.in", "r");
    if (!fin)
    {
        fprintf(stderr, "fopen() failed at line #%d in file %s\n", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
    }
    List *head = NULL;
    if (getc(fin) != EOF)
    {
        fseek(fin, 0, SEEK_SET);
        head = read_list(fin);
    }
    fclose(fin);
    printf("Original list:\n");
    (head) ? (display_list(head), printf("\n")) : printf("List is empty\n");
    List *first_part, *second_part;
    if (head)
    {
        split(head, &first_part, &second_part);
        merge_sort(&first_part, compare_descresc);
        merge_sort(&second_part, compare_cresc);
        head = merge(first_part, second_part, dont_compare);
    }
    printf("Sorted list according to condition:\n");
    (head) ? (display_list(head), printf("\n")) : printf("List is empty\n");
    clear(&head);
    exit(EXIT_SUCCESS);
}

int8_t dont_compare()
{
    return 1;
}

int8_t compare_cresc(const void *a, const void *b)
{
    return ((List *)a)->inf.nr < ((List *)b)->inf.nr;
}

int8_t compare_descresc(const void *a, const void *b)
{
    return ((List *)a)->inf.nr > ((List *)b)->inf.nr;
}

void display_list(List *head)
{
    if (!head)
    {
        return;
    }
    printf("%.2lf ", head->inf.nr);
    display_list(head->link);
}

List *read_list(FILE *fin)
{
    if (feof(fin))
        return NULL;
    List *new_node = (List *)malloc(sizeof(List));
    fscanf(fin, "%lf ", &(new_node->inf.nr));
    new_node->link = read_list(fin);
    return new_node;
}

void merge_sort(List **head, int8_t compare(const void *a, const void *b))
{
    if (!(*head) || !((*head)->link))
    {
        return;
    }
    List *x, *y, *temp = *head;
    split(temp, &x, &y);
    merge_sort(&x, compare);
    merge_sort(&y, compare);
    *head = merge(x, y, compare);
}

void split(List *head, List **x, List **y)
{
    List *slowptr = head, *fastptr = head->link;
    if (fastptr)
    {
        fastptr = fastptr->link;
    }
    while (fastptr)
    {
        fastptr = fastptr->link;
        if (fastptr)
        {
            slowptr = slowptr->link;
            fastptr = fastptr->link;
        }
    }
    *x = head;
    *y = slowptr->link;
    slowptr->link = NULL;
}

List *merge(List *x, List *y, int8_t compare(const void *a, const void *b))
{
    List *new_head = NULL;
    if (!x)
    {
        return y;
    }
    if (!y)
    {
        return x;
    }
    if (compare(x, y))
    {
        new_head = x;
        new_head->link = merge(x->link, y, compare);
    }
    else
    {
        new_head = y;
        new_head->link = merge(x, y->link, compare);
    }
    return new_head;
}

void clear(List **head)
{
    if (!(*head))
    {
        return;
    }
    clear(&((*head)->link));
    free(*head);
}