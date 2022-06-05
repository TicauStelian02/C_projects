#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void read(FILE *f, size_t *n, size_t *m, uint8_t *start_i, uint8_t *start_j, uint8_t *final_i, uint8_t *final_j, uint8_t ***labirint);
uint8_t **generate_null_matrix(size_t n, size_t m);
void clear(uint8_t ***mx, size_t n);
void back(uint8_t **labirint, size_t n, size_t m, uint8_t i_actual, uint8_t j_actual, uint8_t final_i, uint8_t final_j, uint8_t *dir_i, uint8_t *dir_j, uint8_t k);
void print_mx(uint8_t **mx, size_t n, size_t m);
uint8_t valid(uint8_t i, uint8_t j, size_t n, size_t m);
uint8_t potentional_sol(uint8_t **labirint, uint8_t i, uint8_t j, uint8_t final_i, uint8_t final_j);
uint8_t is_sol(uint8_t i_actual, uint8_t j_actual, uint8_t final_i, uint8_t final_j);

int32_t main()
{
    FILE *f = fopen("data.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopne() filed at line %d in file %s", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
    }
    size_t n, m;
    uint8_t start_i, start_j, final_i, final_j, **labirint;
    read(f, &n, &m, &start_i, &start_j, &final_i, &final_j, &labirint);
    fclose(f);
    uint8_t *dir_i = (uint8_t *)calloc(4, sizeof(uint8_t));
    *dir_i = -1;
    *(dir_i + 2) = 1;
    uint8_t *dir_j = (uint8_t *)calloc(4, sizeof(uint8_t));
    *(dir_j + 1) = 1;
    *(dir_j + 3) = -1;
    back(labirint, n, m, start_i, start_j, final_i, final_j, dir_i, dir_j, 2);
    clear(&labirint, n);
    free(dir_i);
    free(dir_j);
    exit(EXIT_SUCCESS);
}

uint8_t valid(uint8_t i, uint8_t j, size_t n, size_t m)
{
    return i < n && i >= 0 && j < m && j >= 0;
}

uint8_t potentional_sol(uint8_t **labirint, uint8_t i, uint8_t j, uint8_t final_i, uint8_t final_j)
{
    return *(*(labirint + i) + j) != 0 && *(*(labirint + i) + j) != 1;
}

uint8_t is_sol(uint8_t i_actual, uint8_t j_actual, uint8_t final_i, uint8_t final_j)
{
    return i_actual == final_i && j_actual == final_j;
}

void back(uint8_t **labirint, size_t n, size_t m, uint8_t i_actual, uint8_t j_actual, uint8_t final_i, uint8_t final_j, uint8_t *dir_i, uint8_t *dir_j, uint8_t k)
{
    if (is_sol(i_actual, j_actual, final_i, final_j))
    {
        *(*(labirint + i_actual) + j_actual) = 1;
        print_mx(labirint, n, m);
    }
    else
    {
        for (size_t i = 0; i < 4; i++)
        {
            i_actual += *(dir_i + i);
            j_actual += *(dir_j + i);
            if (valid(i_actual, j_actual, n, m))
            {
                if (potentional_sol(labirint, i_actual, j_actual, final_i, final_j))
                {
                    *(*(labirint + i_actual) + j_actual) = 1;
                    back(labirint, n, m, i_actual, j_actual, final_i, final_j, dir_i, dir_j, k + 1);
                    *(*(labirint + i_actual) + j_actual) = 0;
                }
            }
        }
    }
}

void print_mx(uint8_t **mx, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%2hhu ", *(*(mx + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void clear(uint8_t ***mx, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(*(*mx + i));
    free(*mx);
}

uint8_t **generate_null_matrix(size_t n, size_t m)
{
    uint8_t **mx = (uint8_t **)calloc(n, sizeof(uint8_t *));
    for (size_t i = 0; i < n; i++)
        *(mx + i) = (uint8_t *)calloc(m, sizeof(uint8_t));
    return mx;
}

void read(FILE *f, size_t *n, size_t *m, uint8_t *start_i, uint8_t *start_j, uint8_t *final_i, uint8_t *final_j, uint8_t ***labirint)
{
    fscanf(f, "%zu %zu %hhu %hhu %hhu %hhu ", n, m, start_i, start_j, final_i, final_j);
    *labirint = generate_null_matrix(*n, *m);
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            fscanf(f, "%hhu ", *(*labirint + i) + j);
}