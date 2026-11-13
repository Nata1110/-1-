#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int N = 100;
std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<> d(-99, 99);
int arr[N];     
int sorted[N];  
int work[N];    
bool hasSorted = false;

steady_clock::time_point t1;
void startTimer() { t1 = steady_clock::now(); }
long long stopTimer() {
    auto t2 = steady_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}

void printArray(int b[]) {
    for (int i = 0; i < N; i++) cout << b[i] << " ";
    cout << endl;
}

void copyArray(int from[], int to[]) {
    for (int i = 0; i < N; i++) to[i] = from[i];
}

void swapElements(int b[], int i, int j) {
    int temp = b[i];
    b[i] = b[j];
    b[j] = temp;
}

int findMin(int b[]) {
    int min = b[0];
    for (int i = 1; i < N; i++)
        if (b[i] < min) min = b[i];
    return min;
}

int findMax(int b[]) {
    int max = b[0];
    for (int i = 1; i < N; i++)
        if (b[i] > max) max = b[i];
    return max;
}

void bubbleSort(int b[]) {
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - 1 - i; j++)
            if (b[j] > b[j + 1]) swapElements(b, j, j + 1);
}

void selectionSort(int b[]) {
    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < N; j++)
            if (b[j] < b[minIndex]) minIndex = j;
        swapElements(b, i, minIndex);
    }
}

void insertionSort(int b[]) {
    for (int i = 1; i < N; i++) {
        int key = b[i];
        int j = i - 1;
        while (j >= 0 && b[j] > key) {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = key;
    }
}

void shakerSort(int b[]) {
    int left = 0, right = N - 1;
    while (left < right) {
        for (int i = left; i < right; i++)
            if (b[i] > b[i + 1]) swapElements(b, i, i + 1);
        right--;
        for (int i = right; i > left; i--)
            if (b[i - 1] > b[i]) swapElements(b, i - 1, i);
        left++;
    }
}

void quickSort(int b[], int left, int right) {
    int i = left, j = right;
    int pivot = b[(left + right) / 2];
    while (i <= j) {
        while (b[i] < pivot) i++;
        while (b[j] > pivot) j--;
        if (i <= j) {
            swapElements(b, i, j);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(b, left, j);
    if (i < right) quickSort(b, i, right);
}

void prepareSorted() {
    if (hasSorted == false) {
        copyArray(arr, sorted);
        quickSort(sorted, 0, N - 1);
        hasSorted = true;
    }
}

// Задание 1
void task1() {
    for (int i = 0; i < N; i++) arr[i] = d(gen);
    hasSorted = false;
    cout << "Массив создан:" << endl;
    printArray(arr);
}

// Задание 2
void task2() {
    copyArray(arr, work); startTimer(); bubbleSort(work);
    cout << "Пузырьковая:         " << stopTimer() << " мкс" << endl;
    copyArray(arr, work); startTimer(); selectionSort(work);
    cout << "Выбор:           " << stopTimer() << " мкс" << endl;
    copyArray(arr, work); startTimer(); insertionSort(work);
    cout << "Вставки:         " << stopTimer() << " мкс" << endl;
    copyArray(arr, work); startTimer(); shakerSort(work);
    cout << "Шейкер:         " << stopTimer() << " мкс" << endl;
    copyArray(arr, work); startTimer(); quickSort(work, 0, N - 1);
    cout << "Эффективная (n log n): " << stopTimer() << " мкс" << endl;
    copyArray(work, sorted);  
    hasSorted = true;
    cout << "Отсортированный массив:" << endl;
    printArray(sorted);
}

// Задание 3
void task3() {
    prepareSorted();
    startTimer();
    int min1 = findMin(arr);
    int max1 = findMax(arr);
    long long time1 = stopTimer();
    startTimer();  
    int min2 = sorted[0];
    int max2 = sorted[N - 1];
    long long time2 = stopTimer();
    cout << "Неотсортированный: min = " << min1 << ", max = " << max1 << ", время = " << time1 << " мкс" << endl;
    cout << "Отсортированный:   min = " << min2 << ", max = " << max2 << ", время = " << time2 << " мкс" << endl;
}

// Задание 4
void task4() {
    int min = findMin(arr);
    int max = findMax(arr);
    int sum = min + max;
    int avg = sum / 2;
    if (sum % 2 != 0 && sum > 0) avg = avg + 1;  
    if (sum % 2 != 0 && sum < 0) avg = avg - 1;
    cout << "min = " << min << ", max = " << max << ", среднее округлённое = " << avg << endl;
    int count = 0;
    int indexes[N];
    startTimer();
    for (int i = 0; i < N; i++) {
        if (arr[i] == avg) {
            indexes[count] = i;
            count++;
        }
    }
    long long time = stopTimer();
    cout << "Индексы: ";
    for (int i = 0; i < count; i++) cout << indexes[i] << " ";
    cout << endl << "Количество: " << count << ", время поиска: " << time << " мкс" << endl;
}

// Задание 5
void task5() {
    prepareSorted();
    int a, count = 0;
    cout << "Введите a: ";
    cin >> a;
    for (int i = 0; i < N; i++)
        if (sorted[i] < a) count++;
    cout << "Элементов меньше " << a << ": " << count << endl;
}

// Задание 6
void task6() {
    prepareSorted();
    int b, count = 0;
    cout << "Введите b: ";
    cin >> b;
    for (int i = 0; i < N; i++)
        if (sorted[i] > b) count++;
    cout << "Элементов больше " << b << ": " << count << endl;
}

// Задание 7
int binarySearch(int x) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sorted[mid] == x) return mid;
        if (sorted[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int linearSearch(int x) {
    for (int i = 0; i < N; i++)
        if (arr[i] == x) return i;
    return -1;
}

void task7() {
    prepareSorted();
    int x;
    cout << "Введите число: ";
    cin >> x;
    startTimer();
    int r1 = binarySearch(x);
    long long time1 = stopTimer();
    startTimer();
    int r2 = linearSearch(x);
    long long time2 = stopTimer();
    if (r1 != -1 && r2 != -1) cout << "Число " << x << " найдено." << endl;
    else cout << "Числа " << x << " нет в массиве." << endl;
    cout << "Бинарный поиск: " << time1 << " мкс, перебор: " << time2 << " мкс" << endl;
}

// Задание 8
void task8() {
    int i, j;
    cout << "Введите два индекса (от 0 до " << N - 1 << "): ";
    cin >> i >> j;
    if (i < 0 || i >= N || j < 0 || j >= N) {
        cout << "Неверный индекс!" << endl;
        return;
    }
    startTimer();
    swapElements(arr, i, j);
    long long time = stopTimer();
    hasSorted = false;  
    cout << "Время: " << time << " мкс" << endl;
    printArray(arr);
}

// Индивидуальное задание
void task9() {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] != 0 && arr[i] % 3 == 0) {
            arr[i] = 0;
            count++;
        }
    }
    hasSorted = false;
    cout << "Новый массив:" << endl;
    printArray(arr);
    cout << "Количество замен: " << count << endl;
}

void printMenu() {
    cout << "\n Выберите пункт\n"
         << "1 - Создать массив\n2 - Сортировки и время\n3 - Min и Max\n4 - Среднее min и max, индексы\n5 - Элементы меньше a\n6 - Элементы больше b\n7 - Бинарный поиск и перебор\n8 - Обмен элементов\n9 - Кратные 3 заменить нулями\n0 - Выход\nВаш выбор: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    task1(); 
    int choice = -1;
    while (choice != 0) {
        printMenu();
        cin >> choice;
        if (choice == 1) task1();
        else if (choice == 2) task2();
        else if (choice == 3) task3();
        else if (choice == 4) task4();
        else if (choice == 5) task5();
        else if (choice == 6) task6();
        else if (choice == 7) task7();
        else if (choice == 8) task8();
        else if (choice == 9) task9();
        else if (choice == 0) cout << "Выход." << endl;
    }
    return 0;
}
