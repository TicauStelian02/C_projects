#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node
{
    uint8_t nr;
    struct Node *link;
} Stack;

void push(Stack **st, uint8_t val);
uint8_t pop(Stack **st);
void print(Stack *st);
void back(Stack *sol, uint8_t k, uint8_t n);
uint8_t is_sol(uint8_t k, uint8_t n);
uint8_t valid(Stack *sol);

int32_t main()
{
    uint8_t n;
    scanf("%d", &n);
    back(NULL, 1, n);
    exit(EXIT_SUCCESS);
}

void back(Stack *sol, uint8_t k, uint8_t n)
{
    for (int i = 1; i <= n; i++)
    {
        push(&sol, i);
        if (valid(sol))
        {
            if (is_sol(k, n))
            {
                print(sol);
            }
            else
            {
                back(sol, k + 1, n);
            }
        }
        pop(&sol);
    }
}

uint8_t is_sol(uint8_t k, uint8_t n)
{
    return k == n;
}

uint8_t valid(Stack *sol)
{
    uint8_t val = sol->nr;
    sol = sol->link;
    while (sol)
    {
        if (val == sol->nr)
            return 0;
        sol = sol->link;
    }
    return 1;
}

void print(Stack *s)
{
    if (!s)
    {
        printf("\n");
        return;
    }
    printf("%hhu ", s->nr);
    print(s->link);
}

void push(Stack **st, uint8_t val)
{
    Stack *new_node = (Stack *)malloc(sizeof(Stack));
    new_node->nr = val;
    new_node->link = *st;
    *st = new_node;
}

uint8_t pop(Stack **st)
{
    Stack *del = *st;
    uint8_t temp = del->nr;
    (*st) = (*st)->link;
    del->link = NULL;
    free(del);
    return temp;
}