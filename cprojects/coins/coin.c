#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node
{
    uint8_t value;
    struct Node *link;
} Stack;

Stack *read_components(FILE *fin, uint16_t *amount);
void display_stack(Stack *stack);
void clear_stack(Stack **stack);
void push(Stack **stack, Stack *new_component);
void msort(Stack **stack);
void split(Stack *stack, Stack **x, Stack **y);
Stack *merge(Stack *x, Stack *y);
uint8_t pop_value(Stack **stack);
Stack *sol_stack(Stack *stack, uint8_t *valid_count, uint8_t amount);

int32_t main()
{
    FILE *fin = fopen("coin.in", "r");
    if (!fin)
    {
        fprintf(stderr, "fopen() failed in file %s at line #%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    uint16_t amount;
    Stack *values = read_components(fin, &amount);
    msort(&values);
    uint8_t size_sol = 0;
    Stack *sol = sol_stack(values, &size_sol, amount);
    if (!size_sol)
    {
        printf("Cant't obtain that amount\n");
    }
    else
    {
        printf("%hhu\n", size_sol);
        display_stack(sol);
        printf("\n");
    }
    clear_stack(&sol);
    exit(EXIT_SUCCESS);
}

Stack *sol_stack(Stack *stack, uint8_t *valid_count, uint8_t amount)
{
    Stack *sol_values = NULL;
    do
    {
        uint8_t bigger = pop_value(&stack);
        while (amount - bigger >= 0)
        {
            (*valid_count)++;
            Stack *new_in_sol = (Stack *)malloc(sizeof(stack));
            new_in_sol->value = bigger;
            push(&sol_values, new_in_sol);
            amount -= bigger;
            if (!amount)
            {
                return sol_values;
            }
        }
    } while (stack);
    stack = NULL;
    *valid_count = 0;
    return NULL;
}

uint8_t pop_value(Stack **stack)
{
    Stack *temp = *stack;
    *stack = (*stack)->link;
    temp->link = NULL;
    uint8_t val = temp->value;
    free(temp);
    return val;
}

void clear_stack(Stack **stack)
{
    if (!*stack)
    {
        return;
    }
    clear_stack(&((*stack)->link));
    free(*stack);
}

void display_stack(Stack *stack)
{
    if (!stack)
    {
        return;
    }
    printf("%hhu ", stack->value);
    display_stack(stack->link);
}

Stack *read_components(FILE *fin, uint16_t *amount)
{
    Stack *new_stack = NULL;
    fscanf(fin, "%hu ", amount);
    while (!feof(fin))
    {
        Stack *new_component = (Stack *)malloc(sizeof(Stack));
        fscanf(fin, "%hhu ", &(new_component->value));
        push(&new_stack, new_component);
    }
    return new_stack;
}

void push(Stack **stack, Stack *new_component)
{
    new_component->link = *stack;
    *stack = new_component;
}

void msort(Stack **stack)
{
    if (!*stack || !(*stack)->link)
    {
        return;
    }
    Stack *top = *stack, *x, *y;
    split(top, &x, &y);
    msort(&x);
    msort(&y);
    *stack = merge(x, y);
}

void split(Stack *stack, Stack **x, Stack **y)
{
    Stack *slowptr = stack, *fastptr = stack->link;
    while (fastptr)
    {
        fastptr = fastptr->link;
        if (fastptr)
        {
            slowptr = slowptr->link;
            fastptr = fastptr->link;
        }
    }
    *x = stack;
    *y = slowptr->link;
    slowptr->link = NULL;
}

Stack *merge(Stack *x, Stack *y)
{
    Stack *sorted_stack = NULL;
    if (!x)
    {
        return y;
    }
    if (!y)
    {
        return x;
    }
    if (x->value > y->value)
    {
        sorted_stack = x;
        sorted_stack->link = merge(x->link, y);
    }
    else
    {
        sorted_stack = y;
        sorted_stack->link = merge(x, y->link);
    }
    return sorted_stack;
}
