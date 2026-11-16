// Lab_7_1_rec.cpp
// < прізвище, ім’я автора >
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 13 (рекурсивний спосіб – у програмі немає жодного циклу)

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// Формує матрицю випадковими числами з діапазону [Low; High]; (i, j) – поточний елемент
void Create(int** Z, const int rowCount, const int colCount, const int Low, const int High,
    int i, int j);
// Виводить матрицю на екран у вигляді таблиці; (i, j) – поточний елемент
void Print(int** Z, const int rowCount, const int colCount, int i, int j);
// Впорядковує стовпчики матриці за ключами ← → ← (метод «бульбашки»); j0 – номер проходу
void Sort(int** Z, const int rowCount, const int colCount, int j0);
// Один прохід «бульбашки»: порівнює сусідні стовпчики j1 та j1+1 до межі end
void SortPass(int** Z, const int rowCount, const int end, int j1);
// Повертає true, якщо стовпчики j та j+1 стоять не в тому порядку (за ключами ← → ←)
bool NeedSwap(int** Z, const int j);
// Міняє місцями два стовпчики матриці; i – номер поточного рядка
void SwapColumns(int** Z, const int col1, const int col2, const int rowCount, int i);
// Обчислює суму S та кількість k заданих елементів і замінює їх нулями.
// Перед першим викликом S і k мають дорівнювати 0; (i, j) – поточний елемент
void Calculate(int** Z, const int rowCount, const int colCount, int& S, int& k, int i, int j);

// Під час unit-тестування функція main() виключається з компіляції
#ifndef UNIT_TEST
int main()
{
    srand((unsigned)time(NULL));

    const int Low = 4;          // нижня межа діапазону значень
    const int High = 45;        // верхня межа діапазону значень

    const int rowCount = 9;     // кількість рядків матриці Z
    const int colCount = 7;     // кількість стовпчиків матриці Z

    int** Z = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        Z[i] = new int[colCount];

    Create(Z, rowCount, colCount, Low, High, 0, 0);
    cout << "Initial matrix:" << endl;
    Print(Z, rowCount, colCount, 0, 0);

    Sort(Z, rowCount, colCount, 0);
    cout << "Sorted matrix:" << endl;
    Print(Z, rowCount, colCount, 0, 0);

    int S = 0;                  // сума заданих елементів
    int k = 0;                  // кількість заданих елементів
    Calculate(Z, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    Print(Z, rowCount, colCount, 0, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] Z[i];
    delete[] Z;

    return 0;
}
#endif

void Create(int** Z, const int rowCount, const int colCount, const int Low, const int High,
    int i, int j)
{
    Z[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(Z, rowCount, colCount, Low, High, i, j + 1);
    else
        if (i < rowCount - 1)
            Create(Z, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** Z, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << Z[i][j];
    if (j < colCount - 1)
        Print(Z, rowCount, colCount, i, j + 1);
    else
        if (i < rowCount - 1)
        {
            cout << endl;
            Print(Z, rowCount, colCount, i + 1, 0);
        }
        else
            cout << endl << endl;
}

void Sort(int** Z, const int rowCount, const int colCount, int j0)
{
    if (j0 < colCount - 1)
    {
        SortPass(Z, rowCount, colCount - j0 - 1, 0);
        Sort(Z, rowCount, colCount, j0 + 1);
    }
}

void SortPass(int** Z, const int rowCount, const int end, int j1)
{
    if (j1 < end)
    {
        if (NeedSwap(Z, j1))
            SwapColumns(Z, j1, j1 + 1, rowCount, 0);
        SortPass(Z, rowCount, end, j1 + 1);
    }
}

bool NeedSwap(int** Z, const int j)
{
    // Ключі: 1-й рядок – за спаданням (←),
    //        2-й рядок – за зростанням (→), якщо збігаються елементи 1-го рядка,
    //        3-й рядок – за спаданням (←), якщо збігаються елементи 1-го і 2-го рядків.
    return (Z[0][j] < Z[0][j + 1])
        ||
        (Z[0][j] == Z[0][j + 1] &&
            Z[1][j] > Z[1][j + 1])
        ||
        (Z[0][j] == Z[0][j + 1] &&
            Z[1][j] == Z[1][j + 1] &&
            Z[2][j] < Z[2][j + 1]);
}

void SwapColumns(int** Z, const int col1, const int col2, const int rowCount, int i)
{
    int tmp = Z[i][col1];
    Z[i][col1] = Z[i][col2];
    Z[i][col2] = tmp;
    if (i < rowCount - 1)
        SwapColumns(Z, col1, col2, rowCount, i + 1);
}

void Calculate(int** Z, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    // парні елементи, крім тих, у яких хоча б один індекс непарний
    if (Z[i][j] % 2 == 0 && !(i % 2 != 0 || j % 2 != 0))
    {
        S += Z[i][j];
        k++;
        Z[i][j] = 0;
    }
    if (j < colCount - 1)
        Calculate(Z, rowCount, colCount, S, k, i, j + 1);
    else
        if (i < rowCount - 1)
            Calculate(Z, rowCount, colCount, S, k, i + 1, 0);
}