#include <stdio.h>
#include <stdlib.h>

size_t read_array(FILE *f, double **a);
__int8_t is_empty(FILE *f);
void display_array(double *a, size_t n);
void merge_sort(double **a, size_t left, size_t right);
__int8_t merge(double **a, size_t l, size_t m, size_t r);

__int32_t main()
{
    FILE *f = fopen("data.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopen() failed at line #%d in file %s\n", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
    }
    double *a = NULL;
    size_t n = read_array(f, &a);
    printf("Original array:\n");
    display_array(a, n);
    fclose(f);
    free(a);
    exit(EXIT_SUCCESS);
}

void merge_sort(double **a, size_t left, size_t right)
{
    
}

__int8_t is_empty(FILE *f)
{
    __int8_t emp = 0;
    if (getc(f) == EOF)
    {
        emp = 1;
    }
    fseek(f, 0, SEEK_SET);
    return emp;
}

size_t read_array(FILE *f, double **a)
{
    if (is_empty(f))
    {
        return 0;
    }
    size_t i = 0;
    while (!feof(f))
    {
        i++;
        *a = (double *)realloc(*a, i * sizeof(double));
        fscanf(f, "%lf ", *a + i - 1);
    }
    return i;
}

void display_array(double *a, size_t n)
{
    if (!a)
    {
        printf("Array is empty\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%.2lf ", *(a + i));
    }
    printf("\n");
}