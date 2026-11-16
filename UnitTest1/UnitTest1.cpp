// UnitTest_rec.cpp – Microsoft Native Unit Test Project (CppUnitTest)
// Лабораторна робота № 7.1, варіант 13 (рекурсивний спосіб)
#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TEST   
#include "../lb 7.1 rec/lb 7.1 rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest7_1_rec
{
    // допоміжна функція: створює матрицю з масиву значень
    static int** MakeMatrix(const int rows, const int cols, const int* values)
    {
        int** m = new int* [rows];
        for (int i = 0; i < rows; i++)
        {
            m[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                m[i][j] = values[i * cols + j];
        }
        return m;
    }

    static void FreeMatrix(int** m, const int rows)
    {
        for (int i = 0; i < rows; i++)
            delete[] m[i];
        delete[] m;
    }

    // допоміжна функція: порівнює матрицю з очікуваним масивом
    static void AssertMatrix(int** m, const int rows, const int cols, const int* expected)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                Assert::AreEqual(expected[i * cols + j], m[i][j]);
    }

    TEST_CLASS(UnitTest7_1_rec)
    {
    public:

        TEST_METHOD(TestCreateInRange)
        {
            const int rows = 9, cols = 7;
            int** Z = new int* [rows];
            for (int i = 0; i < rows; i++)
                Z[i] = new int[cols];

            Create(Z, rows, cols, 4, 45, 0, 0);

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                {
                    Assert::IsTrue(Z[i][j] >= 4);
                    Assert::IsTrue(Z[i][j] <= 45);
                }
            FreeMatrix(Z, rows);
        }

        TEST_METHOD(TestCalculate)
        {
            const int rows = 3, cols = 4;
            const int v[] = { 4,  5,  6,  7,
                              8, 10, 12, 14,
                             20, 21, 22, 23 };
            int** Z = MakeMatrix(rows, cols, v);

            int S = 0, k = 0;
            Calculate(Z, rows, cols, S, k, 0, 0);

            Assert::AreEqual(52, S);   // 4 + 6 + 20 + 22
            Assert::AreEqual(4, k);
            Assert::AreEqual(0, Z[0][0]);
            Assert::AreEqual(0, Z[0][2]);
            Assert::AreEqual(0, Z[2][0]);
            Assert::AreEqual(0, Z[2][2]);
            Assert::AreEqual(10, Z[1][1]);   // індекс (1,1) непарний – не змінюється

            FreeMatrix(Z, rows);
        }

        TEST_METHOD(TestSwapColumns)
        {
            const int rows = 2, cols = 3;
            const int v[] = { 1, 2, 3,
                              4, 5, 6 };
            int** Z = MakeMatrix(rows, cols, v);

            SwapColumns(Z, 0, 2, rows, 0);

            const int expected[] = { 3, 2, 1,
                                     6, 5, 4 };
            AssertMatrix(Z, rows, cols, expected);

            FreeMatrix(Z, rows);
        }

        TEST_METHOD(TestSortByFirstAndSecondRow)
        {
            const int rows = 3, cols = 4;
            const int v[] = { 5, 9, 5, 9,
                              1, 2, 3, 4,
                              7, 8, 9, 6 };
            int** Z = MakeMatrix(rows, cols, v);

            Sort(Z, rows, cols, 0);

            const int expected[] = { 9, 9, 5, 5,
                                     2, 4, 1, 3,
                                     8, 6, 7, 9 };
            AssertMatrix(Z, rows, cols, expected);

            FreeMatrix(Z, rows);
        }

        TEST_METHOD(TestSortByThirdRow)
        {
            const int rows = 3, cols = 3;
            const int v[] = { 5, 5, 7,
                              1, 1, 2,
                              3, 8, 1 };
            int** Z = MakeMatrix(rows, cols, v);

            Sort(Z, rows, cols, 0);

            const int expected[] = { 7, 5, 5,
                                     2, 1, 1,
                                     1, 8, 3 };
            AssertMatrix(Z, rows, cols, expected);

            FreeMatrix(Z, rows);
        }

        TEST_METHOD(TestNeedSwap)
        {
            const int rows = 3, cols = 2;
            const int v[] = { 5, 7,
                              1, 1,
                              3, 3 };
            int** Z = MakeMatrix(rows, cols, v);

            Assert::IsTrue(NeedSwap(Z, 0));    // 5 < 7 – порядок за спаданням порушено
            Z[0][1] = 5;                       // перший рядок однаковий, 1 == 1, 3 == 3
            Assert::IsFalse(NeedSwap(Z, 0));
            Z[1][1] = 0;                       // 2-й рядок: 1 > 0 – порядок за зростанням порушено
            Assert::IsTrue(NeedSwap(Z, 0));
            Z[1][1] = 1; Z[2][1] = 9;          // 3-й рядок: 3 < 9 – порядок за спаданням порушено
            Assert::IsTrue(NeedSwap(Z, 0));

            FreeMatrix(Z, rows);
        }
    };
}