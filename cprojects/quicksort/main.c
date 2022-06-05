#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
void clearConsole()
{
    system("cls");
}

void waitForAnyKey()
{
    system("pause");
}
#elif __linux__
void clearConsole()
{
    system("clear");
}

void waitForAnyKey()
{
    printf("Press any key to continue...\n");
    system("read -s -N 1");
}

#endif

struct student
{
    __int8_t key;
    __uint8_t *name;
    double average_grade;
};

size_t read_array(FILE *f, struct student **a);
void display_array(struct student *a, size_t n);
void read_info(FILE *f, struct student *_student);
void print_student(struct student _student);
void quicksort(struct student **a, __int8_t left, __int8_t right, __int8_t compare(struct student x, struct student y));
__int8_t compare(struct student x, struct student y);
__int8_t compare_by_key(struct student x, struct student y);
__int8_t compare_by_marks_average(struct student x, struct student y);
__int8_t compare_by_name(struct student x, struct student y);
__int8_t partition(struct student **a, __int8_t left, __int8_t right, __int8_t compare(struct student x, struct student y));
size_t _max(__uint8_t x, __uint8_t y);
__int8_t if_empty(FILE *f);
__uint8_t *read_string(FILE *f);
void _swap(struct student *x, struct student *y);
void f_display_array(FILE **f, struct student *a, size_t n);

__int32_t main()
{
    FILE *f = fopen("data.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopen() failed at line #%d in file %s\n", __LINE__, __FILE__);
        exit(1);
    }
    struct student *a = NULL;
    size_t n = read_array(f, &a);
    fclose(f);
    __uint8_t choice;
    clearConsole();
    do
    {
        printf("Alegeti una dintre urmatoarele optiuni:\n1. Sortarea elevilor dupa cheie;\n2. Sortarea elevilor dupa medie;\n3. Sortarea elevilot dupa nume;\n4. Afisarea listei curente a elevilor;\n0. Iesire din program.\nOptiunea aleasa: ");
        scanf(" %c", &choice);
        clearConsole();
        switch (choice)
        {
        case '1':
            if (n)
            {
                quicksort(&a, 0, n - 1, compare_by_key);
                printf("Lista e sortata dupa cheia elevilor.\n");
                waitForAnyKey();
                clearConsole();
            }
            break;
        case '2':
            if (n)
            {
                quicksort(&a, 0, n - 1, compare_by_marks_average);
                printf("Lista e sortata dupa media elevilor.\n");
                waitForAnyKey();
                clearConsole();
            }
            break;
        case '3':
            if (n)
            {
                quicksort(&a, 0, n - 1, compare_by_name);
                printf("Lista e sortata dupa numele elevilor in ordine alfabetica.\n");
                waitForAnyKey();
                clearConsole();
                break;
            }
        case '4':
            printf("Lista curenta a elevilor:\n");
            display_array(a, n);
            waitForAnyKey();
            clearConsole();
            break;
        case '0':
            printf("Se incheie executia programului!\n");
            waitForAnyKey();
            clearConsole();
            break;
        default:
            printf("Nu exista astfel de optiune:\n");
            waitForAnyKey();
            clearConsole();
            break;
        }
    } while (choice != '0');
    FILE *fo = fopen("data.out", "w");
    f_display_array(&fo, a, n); // after last operation, list of student will be inserted in file "data.out"
    fclose(f);
    free(a);
    exit(EXIT_SUCCESS);
}

__int8_t if_empty(FILE *f)
{
    if (getc(f) == EOF)
    {
        return 1;
    }
    return 0;
}

void f_display_array(FILE **f, struct student *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        fprintf(*f, "%d %s %.2lf\n", (a + i)->key, (a + i)->name, (a + i)->average_grade);
    }
}

size_t read_array(FILE *f, struct student **a)
{
    if (if_empty(f))
        return 0;
    fseek(f, 0, SEEK_SET); // mute pointer of f to start of file
    size_t i = 0;
    while (!feof(f))
    {
        i++;
        *a = (struct student *)realloc(*a, i * sizeof(struct student));
        read_info(f, *a + i - 1);
    }
    return i;
}

void read_info(FILE *f, struct student *_student)
{
    fscanf(f, "%d %lf ", &(_student->key), &(_student->average_grade));
    _student->name = read_string(f);
}

void print_student(struct student _student)
{
    printf("%d %s %.2lf\n", _student.key, _student.name, _student.average_grade);
}

void display_array(struct student *a, size_t n)
{
    if (!a)
    {
        printf("Lista e vida\n");
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        print_student(*(a + i));
    }
}

void quicksort(struct student **a, __int8_t left, __int8_t right, __int8_t compare(struct student x, struct student y))
{
    __int8_t index = partition(&(*a), left, right, compare);
    if (left < index - 1)
        quicksort(&(*a), left, index - 1, compare);
    if (index < right)
        quicksort(&(*a), index, right, compare);
}

__int8_t partition(struct student **a, __int8_t left, __int8_t right, __int8_t compare(struct student x, struct student y))
{
    __int8_t i = left, j = right;
    struct student pivot = *(*a + (left + right) / 2);
    while (i <= j)
    {
        while (compare(*(*a + i), pivot))
        {
            i++;
        }
        while (compare(pivot, *(*a + j)))
        {
            j--;
        }
        if (i <= j)
        {
            _swap(&*(*a + i), &*(*a + j));
            i++;
            j--;
        }
    }
    return i;
}

void _swap(struct student *x, struct student *y)
{
    struct student temp = *x;
    *x = *y;
    *y = temp;
}

__int8_t compare_by_key(struct student x, struct student y)
{
    return x.key < y.key;
}

__int8_t compare_by_marks_average(struct student x, struct student y)
{
    if (x.average_grade == y.average_grade)
        return x.key < y.key;
    return x.average_grade < y.average_grade;
}

__int8_t compare_by_name(struct student x, struct student y)
{
    size_t i, len_max = _max(strlen(x.name), strlen(y.name));
    for (i = 0; i < len_max; i++)
    {
        if (*(x.name + i) != *(y.name + i))
            break;
    }
    return *(x.name + i) < *(y.name + i);
}

__uint8_t *read_string(FILE *f)
{
    char *s = calloc(1, sizeof(char));
    char t;
    int len;
    while (fscanf(f, "%c", &t) == 1)
    {
        if (t == '\n')
            break;
        len = strlen(s);
        s = realloc(s, len + 1);
        *(s + len) = t;
        *(s + len + 1) = '\0';
    }
    return s;
}

size_t _max(__uint8_t x, __uint8_t y)
{
    if (x >= y)
        return x;
    return y;
}