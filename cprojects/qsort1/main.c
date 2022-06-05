#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void read_array(FILE *f, double **a, size_t *n);
void swap(double *x, double *y);
uint8_t partition(double *a, uint8_t first, uint8_t last);
void quickSort(double *a, uint8_t first, uint8_t last);
void print_array(double *a, size_t n);

int32_t main()
{
    size_t n = -1;
    FILE *f = fopen("vector.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopen() failed at line #%d in file %s\n", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
    }
    double *a = NULL;
    read_array(f, &a, &n);
    fclose(f);
    print_array(a, n);
    free(a);
    return 0;
}

void read_array(FILE *f, double **a, size_t *n)
{
    fscanf(f, "%d ", &(*n));
    *a = (double *)calloc(*n, sizeof(double));
    for (size_t i = 0; i < (*n); i++)
    {
        fscanf(f, "%lf ", &(*(a + i)));
    }
}

void swap(double *x, double *y)
{
}

uint8_t partition(double *a, uint8_t first, uint8_t last)
{
    return 0;
}

void quickSort(double *a, uint8_t first, uint8_t last)
{
}

void print_array(double *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%.3lf ", *(a + i));
    }
    printf("\n");
}