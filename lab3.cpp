#include <iostream>
#include <vector>
#include <locale>
#include <chrono>
#include "windows.h"


void exchangeSort(std::vector<std::vector<int>>& v) {
    int size = v.size();
    for (int m = 0; m <= size; m++) {
        int stopCounter = 1;
        for (int i = size - 1, j = 0; i >= (size / 2)-1, j <= (size / 2)-1; i--, j++) {
            for (int k = size - 1; k >= (size / 2)-1; k--) {
                if (k == size - stopCounter) {
                    stopCounter++;
                    break;
                }
                else {
                    if (v[k][i] > v[k - 1][i]) {
                        std::swap(v[k][i], v[k - 1][i]);
                    }
                    if (v[k][j] > v[k - 1][j]) {
                        std::swap(v[k][j], v[k - 1][j]);
                    }
                }
            }
        }
    }
}

int partition(std::vector<int> &v, int start, int end) {
    int pivot = end;
    int j = start;
    for (int i = start; i < end; i++) {
        if (v[i] < v[pivot]) {
            std::swap(v[i], v[j]);
            j++;
        }
    }
    std::swap(v[j], v[pivot]);
    return j;
}
void quickSort(std::vector<int> &v, int start, int end) {
    if (start >= end) return;

    int p = partition(v, start, end);
    quickSort(v, start, p - 1);
    quickSort(v, p + 1, end);
}
void quickSortTask(std::vector<std::vector<int>>& v) {
    std::vector<int> column;
    int taskSize = v.size()-1;
    bool notHalf = true;
    for (int i = v.size()-1; i >= 0; i--) {
        for (int j = v.size()-1; j >= taskSize; j--) {
            column.push_back(v[j][i]);
        }
        quickSort(column, 0, column.size() - 1);
        for (int k = v.size() - 1, n = 0; k >= taskSize, n <= column.size()-1; k--, n++) {
            v[k][i] = column[n];
        }
        column.clear();
        if (!notHalf) taskSize++;
        if (taskSize == v.size() / 2 && (v.size() / 2) % 2 == 0) {
            notHalf = false;
        }
        else if(taskSize == v.size() / 2) {
                notHalf = false;
                continue;
        }
        if (notHalf) taskSize--;
        if (taskSize == v.size() - 1) return;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Введіть розмірність масиву: ";
    int n;
    std::cin >> n;
    std::vector<std::vector<int>>arr;
    std::vector<int> helpV;
    std::cout << "Початковий масив:" << std::endl;
    for (int i = 0; i != n; i++) {
        std::vector <int> temp;
        for (int j = 0; j != n; j++) {
            temp.push_back((int)rand() % 201 - 100);
            std::cout << temp[j] << '\t';
        }
        arr.push_back(temp);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Виберіть метод сортування, де: \n 1 - exchangeSort \n 2 - quickSort" << std::endl;
    int choise;
    std::cin >> choise;
    switch (choise) {
    case 1: {
        std::cout << "Кінцевий масив:" << std::endl;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        exchangeSort(arr);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        for (int i = 0; i != n; i++) {
            for (int j = 0; j != n; j++) {
                std::cout << arr[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "Час роботи алгоритму: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " наносекунд" << std::endl;
        break;
    }
    case 2: {
        std::cout << "Кінцевий масив:" << std::endl;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        quickSortTask(arr);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        for (int i = 0; i != n; i++) {
            for (int j = 0; j != n; j++) {
                std::cout << arr[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "Час роботи алгоритму: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " наносекунд" << std::endl;
        break;
    }
    }
    
}
