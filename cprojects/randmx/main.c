#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

uint8_t **create_null_matrix(size_t n, size_t m);
void display_mx(FILE *fout, uint8_t **mx, size_t n, size_t m);
uint8_t **generate_random_matrix(size_t n, size_t m, uint8_t range);

int32_t main()
{
    uint8_t **a = generate_random_matrix(255, 255, 2);
    FILE *fout = fopen("matrix.out", "w");
    display_mx(fout, a, 255, 255);
    exit(EXIT_SUCCESS);
}

uint8_t **create_null_matrix(size_t n, size_t m)
{
    uint8_t **mx = (uint8_t **)calloc(n + 2, sizeof(uint8_t *));
    for (size_t i = 0; i <= n + 1; i++)
        *(mx + i) = (uint8_t *)calloc(m + 2, sizeof(uint8_t));
    return mx;
}

void display_mx(FILE *fout, uint8_t **mx, size_t n, size_t m)
{
    srand(time(NULL));
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            fprintf(fout, "%hhu ", *(*(mx + i) + j));
        }
        fprintf(fout, "\n");
    }
}

uint8_t **generate_random_matrix(size_t n, size_t m, uint8_t range)
{
    uint8_t **mx = create_null_matrix(n, m);
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            *(*(mx + i) + j) = rand() % range;
        }
    }
    return mx;
}
