#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct hours
{
    uint32_t start, final;
} Interval;

void swap(Interval *x, Interval *y);
void quicksort(Interval **a, int8_t left, int8_t right);
int8_t partition(Interval **a, int8_t left, int8_t right);
Interval *read_intervals(FILE *fin, size_t n);
void display_intervals(Interval *a, size_t n);
Interval *create_sol_vector(Interval *a, size_t n, uint8_t *valid_count);

int32_t main()
{
    FILE *fin = fopen("spect.in", "r");
    if (!fin)
    {
        fprintf(stderr, "fopen() failed in file %s at line #%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    size_t n;
    fscanf(fin, "%zu ", &n);
    Interval *a = read_intervals(fin, n);
    fclose(fin);
    quicksort(&a, 0, (int16_t)(n - 1));
    uint8_t size_sol = 0;
    Interval *sol_intervals = create_sol_vector(a, n, &size_sol);
    printf("%hhu\n", size_sol);
    display_intervals(sol_intervals, size_sol);
    free(a);
    free(sol_intervals);
    exit(EXIT_SUCCESS);
}

Interval *read_intervals(FILE *fin, size_t n)
{
    Interval *intervals = (Interval *)calloc(n, sizeof(Interval));
    for (size_t i = 0; i < n; i++)
    {
        fscanf(fin, "%hhi %hhi ", &((intervals + i)->start), &((intervals + i)->final));
    }
    return intervals;
}

void display_intervals(Interval *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%hhi %hhi\n", (*(a + i)).start, (*(a + i)).final);
    }
}

void quicksort(Interval **a, int8_t left, int8_t right)
{
    int8_t index = partition(&*a, left, right);
    if (left < index - 1)
    {
        quicksort(&*a, left, index - 1);
    }
    if (index < right)
    {
        quicksort(&*a, index, right);
    }
}

int8_t partition(Interval **a, int8_t left, int8_t right)
{

    Interval pivot = *(*a + (left + right) / 2);
    while (left <= right)
    {
        while ((*(*a + left)).final < pivot.final)
        {
            left++;
        }
        while ((*(*a + right)).final > pivot.final)
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
}

void swap(Interval *x, Interval *y)
{
    Interval temp = *x;
    *x = *y;
    *y = temp;
}

Interval *create_sol_vector(Interval *a, size_t n, uint8_t *valid_count)
{
    (*valid_count)++;
    Interval *sol = (Interval *)calloc(*valid_count, sizeof(Interval));
    *sol = *a;
    for (size_t i = 1; i < n; i++)
    {
        if ((*(a + i)).start >= (*(sol + *valid_count - 1)).final)
        {
            (*valid_count)++;
            sol = (Interval *)realloc(sol, (*valid_count + 1) * sizeof(Interval));
            *(sol + *valid_count - 1) = *(a + i);
        }
    }
    return sol;
}
