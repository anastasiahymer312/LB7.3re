#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** a, const int rowCount, const int colCount) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
}

int ProductOfRowsWithoutNegatives(int** a, const int rowCount, const int colCount, int rowIndex = 0) {
    if (rowIndex >= rowCount) {
        return 1;
    }

    bool hasNegative = false;
    for (int j = 0; j < colCount; j++) {
        if (a[rowIndex][j] < 0) {
            hasNegative = true;
            break;
        }
    }

    int rowProduct = hasNegative ? 1 : 1;
    if (!hasNegative) {
        for (int j = 0; j < colCount; j++) {
            rowProduct *= a[rowIndex][j];
        }
    }

    return rowProduct * ProductOfRowsWithoutNegatives(a, rowCount, colCount, rowIndex + 1);
}

void MaxSumOfDiagonals(int** a, const int rowCount, const int colCount) {
    int maxSum = INT_MIN;

    for (int k = 0; k < rowCount; k++) {
        int sum = 0;
        for (int i = 0, j = k; i < rowCount && j >= 0; i++, j--) {
            if (j < colCount) {
                sum += a[i][j];
            }
        }
        maxSum = max(maxSum, sum);
    }

    for (int k = 1; k < colCount; k++) {
        int sum = 0;
        for (int i = 0, j = k; i < rowCount && j < colCount; i++, j++) {
            sum += a[i][j];
        }
        maxSum = max(maxSum, sum);
    }

    cout << "Максимум серед сум елементів діагоналей: " << maxSum << endl;
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Low = -10, High = 10;
    int rowCount, colCount;

    cout << "k = "; cin >> rowCount;
    cout << "n = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    Print(a, rowCount, colCount);

    int product = ProductOfRowsWithoutNegatives(a, rowCount, colCount);
    cout << "Добуток елементів у рядках без від’ємних: " << product << endl;

    MaxSumOfDiagonals(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
