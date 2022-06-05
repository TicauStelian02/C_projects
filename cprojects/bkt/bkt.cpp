#include <iostream>
using namespace std;

char sp1[] = "               ";
int x1[10], n1, nrsol1 = 0;

void Afisare()
{
    int i;
    cout << sp1;
    for (i = 1; i <= n1; i++)
        cout << x1[i] << " ";
    cout << endl;
    nrsol1++;
}

int Valid(int k)
{
    int i;
    for (i = 1; i <= k - 1; i++)
        if (x1[k] == x1[i])
            return 0;
    return 1;
}

void BackRec1(int k)
{
    int i;
    for (i = 1; i <= n1; i++)
    {
        x1[k] = i;
        if (Valid(k))
            if (k == n1)
                Afisare();
            else
                BackRec1(k + 1);
    }
}

int main()
{
    cout << endl
         << endl
         << sp1 << "Permutarile primelor n numere naturale (n<10)" << endl;
    cout << endl
         << sp1 << " Dati valoarea lui n: ";
    cin >> n1;
    cout << endl;
    BackRec1(1);
    cout << endl
         << sp1 << "Numar solutii: " << nrsol1 << endl;
    return 0;
}