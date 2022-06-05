#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void read(FILE *fin, size_t *n, size_t *m);
uint16_t **read_matrix(FILE *fin, size_t n, size_t m);
uint16_t **create_null_matrix(size_t n, size_t m);
void display_mx(FILE *fout, uint16_t **mx, size_t n, size_t m);
void dye(uint16_t **mx, uint16_t color, size_t poz_i, size_t poz_j);
uint16_t color_all(uint16_t **mx, size_t n, size_t m);
void clear(uint16_t **mx, size_t n, size_t m);

int32_t main()
{
    FILE *fin = fopen("insule.in", "r");
    if (!fin)
    {
        fprintf(stderr, "fopen() failed in file %s at line %d!\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    size_t n, m;
    read(fin, &n, &m);
    uint16_t **a = read_matrix(fin, n, m);
    fclose(fin);
    uint16_t count = color_all(a, n, m); // final color -1 is the answer
    printf("%hu\n", count);
    FILE *fout = fopen("insule.out", "w"); // final matrix will be displayed in "insule.out"
    display_mx(fout, a, n, m);
    fclose(fout);
    clear(a, n, m);
    exit(EXIT_SUCCESS);
}

void clear(uint16_t **mx, size_t n, size_t m)
{
    for (size_t i = 0; i <= n + 1; i++)
        free(*(mx + i));
    free(mx);
}

uint16_t color_all(uint16_t **mx, size_t n, size_t m)
{
    uint16_t color = 1;
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            if (*(*(mx + i) + j) == 1)
            {
                color++; // choose color
                dye(mx, color, i, j);
            }
        }
    }
    return color - 1;
}

void dye(uint16_t **mx, uint16_t color, size_t poz_i, size_t poz_j)
{
    if (*(*(mx + poz_i) + poz_j) == 1)
    {
        /* color all neighbourgs if their elements are 1*/
        *(*(mx + poz_i) + poz_j) = color;
        dye(mx, color, poz_i - 1, poz_j);
        dye(mx, color, poz_i + 1, poz_j);
        dye(mx, color, poz_i, poz_j - 1);
        dye(mx, color, poz_i, poz_j + 1);
    }
}

uint16_t **create_null_matrix(size_t n, size_t m)
{
    uint16_t **mx = (uint16_t **)calloc(n + 2, sizeof(uint16_t *));
    for (size_t i = 0; i <= n + 1; i++)
        *(mx + i) = (uint16_t *)calloc(m + 2, sizeof(uint16_t));
    return mx;
}

void display_mx(FILE *fout, uint16_t **mx, size_t n, size_t m)
{
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            fprintf(fout, "%hu ", *(*(mx + i) + j));
        }
        fprintf(fout, "\n");
    }
}

void read(FILE *fin, size_t *n, size_t *m)
{
    fscanf(fin, "%zu %zu ", n, m);
}

uint16_t **read_matrix(FILE *fin, size_t n, size_t m)
{
    uint16_t **mx = create_null_matrix(n, m);
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            fscanf(fin, "%hu ", *(mx + i) + j);
        }
    }
    return mx;
}