#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct object
{
    uint16_t g, v;
} Object;

Object *read_objects(size_t n);
int16_t partition(Object **a, int16_t left, int16_t right);
void quicksort(Object **a, int16_t left, int16_t right);
void swap(Object *x, Object *y);
uint32_t greedy_solve(Object *a, size_t n, int16_t gmax);

__int32_t main()
{
    size_t n;
    uint16_t gmax;
    scanf("%zu%hu", &n, &gmax);
    Object *a = read_objects(n);
    quicksort(&a, 0, (int16_t)(n - 1));
    uint32_t gain = greedy_solve(a, (int16_t)n, gmax);
    printf("%u\n", gain);
    free(a);
    exit(EXIT_SUCCESS);
}

uint32_t greedy_solve(Object *a, size_t n, int16_t gmax)
{
    uint32_t val = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (gmax - (*(a + i)).g < 0)
        {
            val += (*(a + i)).v / (*(a + i)).g * gmax;
            return val;
        }
        val += (*(a + i)).v;
        gmax -= (*(a + i)).g;
    }
    return val;
}

Object *read_objects(size_t n)
{
    Object *objects = (Object *)calloc(n, sizeof(Object));
    for (size_t i = 0; i < n; i++)
    {
        scanf("%hu%hu", &((objects + i)->g), &((objects + i)->v));
    }
    return objects;
}

int16_t partition(Object **a, int16_t left, int16_t right)
{
    Object pivot = *(*a + (left + right) / 2);
    while (left <= right)
    {
        while (pivot.v / pivot.g < (*(*a + left)).v / (*(*a + left)).g)
        {
            left++;
        }
        while (pivot.v / pivot.g > (*(*a + right)).v / (*(*a + right)).g)
        {
            right--;
        }
        if (left <= right)
        {
            swap(&*(*a + left), &*(*a + right));
            left++;
            right--;
        }
    }
    return left;
}

void quicksort(Object **a, int16_t left, int16_t right)
{
    int16_t index = partition(&*a, left, right);
    if (left < index - 1)
    {
        quicksort(&(*a), left, index - 1);
    }
    if (index < right)
    {
        quicksort(&*a, index, right);
    }
}

void swap(Object *x, Object *y)
{
    Object temp = *x;
    *x = *y;
    *y = temp;
}
