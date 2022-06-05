#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node
{
    double key;
    struct Node *left, *right;
} Tree;

void read_tree(FILE *f, Tree **root); // create Binary Search Tree (BST)
void insert_Node(Tree **root, Tree *new_Node);
void output_tree(Tree *root, uint8_t level);
void inordine(Tree *root);
void postordine(Tree **root);
void preordine(Tree *root);
void sortare(double *a, Tree *root, size_t *i);
Tree *delete_Node(Tree *root, double searched_key);

int main()
{
    Tree *root = NULL;
    double *a = (double *)calloc(16, sizeof(double));
    FILE *f = fopen("file.in", "r");
    if (!f)
    {
        fprintf(stderr, "fopen() failed  in file %s at line # %d", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    read_tree(f, &root);
    fclose(f);
    if (!root)
    {
        printf("Tree doesn't have elements\n");
    }
    else
    {
        inordine(root);
        printf("\n");
        // printf("\n%.3lf", root->key);
        // output_tree(root, 0);
    }
    size_t i = 0;
    // sortare(a, root, &i);
    free(a);
    printf("Insert key of node to be deleted: ");
    double k;
    scanf("%lf", &k);
    root = delete_Node(root, k);
    inordine(root);
    postordine(&root); // sterge arbore
    return 0;
}

void read_tree(FILE *f, Tree **root)
{
    while (!feof(f))
    {
        Tree *new_Node = (Tree *)malloc(sizeof(Tree));
        fscanf(f, "%lf ", &new_Node->key);
        new_Node->left = new_Node->right = NULL;
        insert_Node(&*root, new_Node);
    }
}

Tree *delete_Node(Tree *root, double searched_key)
{
    Tree *max_in_left_subtree; // determinarea maximului din subarborele drept
    if (root == NULL)          // Cazul in care intreg arborele e parcurs si cheia nu e gasita
    {
        printf("searched key not found\n");
        return (root);
    }
    if (searched_key < root->key) // Parcurgem arborele spre stanga, cautand cheia
        root->left = delete_Node(root->left, searched_key);
    else if (searched_key > root->key) // Parcurgem arborele spre dreapta, cautand cheia
        root->right = delete_Node(root->right, searched_key);
    else
    {
        if (root->left && root->right) // exista subarbore stang si subarbore drept la cel cautat
        {
            max_in_left_subtree = root->left;  // pregatim cautare nodului cel mai din dreapta(cu cheie maxima) in subarborele stang
            while (max_in_left_subtree->right) // cautam nodul cel mai din dreapta
                max_in_left_subtree = max_in_left_subtree->right;
            root->key = max_in_left_subtree->key;                           // copiem informatia din nodul predecesor in nodul actual
            root->left = delete_Node(root->left, max_in_left_subtree->key); // stergem nodul predecesor
        }
        else
        {
            Tree *temp = root;
            if (root->left != NULL) // exista doar subarbore stang la cel cautat
                root = root->left;
            else if (root->right != NULL) // exista doar subarbore drept la cel cautat
                root = root->right;
            else // nu exista subarbore la cel cautat(nod frunza)
                root = NULL;
            free(temp);
        }
    }
    return root; // la finalizarea apelurilor recursive se intoarce adresa radacinii
}

void insert_Node(Tree **root, Tree *new_Node)
{
    if (!(*root)) // if(!(*root)) <=> if(*root == NULL)
    {
        *root = new_Node;
        return;
    }
    // if (new_Node->key < (*root)->key)
    // {
    //     insert_Node(&(*root)->left, new_Node);
    // }
    // else
    // {
    //     insert_Node(&(*root)->right, new_Node);
    // }
    (new_Node->key <= (*root)->key) ? insert_Node(&(*root)->left, new_Node) : insert_Node(&(*root)->right, new_Node);
    /*<=> if(new_Node->key<=(*root)->key)
    {
        insert_Node(&(*root)->left,new_Node);
    }
    else{
        insert_Node(&(*root)->right,new_Node);
    }
    */
}

void output_tree(Tree *root, uint8_t level)
{
    if (root)
    {
        output_tree(root->left, level + 1);
        for (size_t i = 0; i < level; i++)
        {
            printf("            ");
        }
        printf("%.3lf\n", root->key); //%.3lf - afiseaza 3 cifre dupa virgula
        output_tree(root->right, level + 1);
    }
}

void inordine(Tree *root)
{
    if (root)
    {
        inordine(root->left);
        printf("%.3lf   ", root->key);
        inordine(root->right);
    }
}

void postordine(Tree **root)
{
    if (*root)
    {
        postordine(&(*root)->left);
        postordine(&(*root)->right);
        free(*root);
    }
}

void preordine(Tree *root)
{
    if (root)
    {
        // conditie
        preordine(root->left);
        preordine(root->right);
    }
}

void sortare(double *a, Tree *root, size_t *i) // convert BST to array a
{
    if (root) // if(root) <=> if(root != NULL)
    {
        sortare(a, root->left, i);
        *(a + *i) = root->key; // a-array that will be sorted
        (*i)++;                // i-index of element in array a
        sortare(a, root->right, i);
    }
}