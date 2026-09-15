#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Компаратор для стандартной функции qsort
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left; j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

void test_matrix(int n)
{
    int* a = (int*)malloc(n * n * sizeof(int));
    int* b = (int*)malloc(n * n * sizeof(int));
    int* c = (int*)malloc(n * n * sizeof(int));

    if (a == NULL || b == NULL || c == NULL) return;

    for (int i = 0; i < n * n; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    clock_t start = clock();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int elem_c = 0;
            for (int r = 0; r < n; r++) {
                elem_c += a[i * n + r] * b[r * n + j];
            }
            c[i * n + j] = elem_c;
        }
    }

    clock_t end = clock();

    double t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Матрица %4d x %4d | Время: %.4f сек.\n", n, n, t);

    free(a);
    free(b);
    free(c);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));

    printf(" ЗАДАНИЕ 1: УМНОЖЕНИЕ МАТРИЦ \n");
    printf("Сложность алгоритма: O(N^3)\n");
    test_matrix(100);
    test_matrix(200);
    test_matrix(400);
    test_matrix(600);
    test_matrix(800);
    test_matrix(1000);

    printf("\n ЗАДАНИЕ 2: СОРТИРОВКИ \n");
    int count = 20000;
    printf("Размер массивов для сортировки: %d\n\n", count);

    int* arr1 = (int*)malloc(count * sizeof(int));
    int* arr2 = (int*)malloc(count * sizeof(int));
    int* arr3 = (int*)malloc(count * sizeof(int));
    clock_t start, end;

    // 1) Случайный набор
    for (int i = 0; i < count; i++) {
        arr1[i] = rand() % 10000;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    printf("1) Случайный набор:\n");
    start = clock();
    shell(arr1, count);
    end = clock();
    printf("   Сортировка Шелла:    %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(arr2, 0, count - 1);
    end = clock();
    printf("   Быстрая (QuickSort):   %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(arr3, count, sizeof(int), cmp);
    end = clock();
    printf("   Стандартная (qsort): %.4f сек.\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 2) Возрастающий набор
    for (int i = 0; i < count; i++) {
        arr1[i] = i;
        arr2[i] = i;
        arr3[i] = i;
    }
    printf("2) Уже отсортированный (возрастающий):\n");
    start = clock();
    shell(arr1, count);
    end = clock();
    printf("   Сортировка Шелла:    %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(arr2, 0, count - 1);
    end = clock();
    printf("   Быстрая (QuickSort):   %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(arr3, count, sizeof(int), cmp);
    end = clock();
    printf("   Стандартная (qsort): %.4f сек.\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 3) Убывающий набор
    for (int i = 0; i < count; i++) {
        arr1[i] = count - i;
        arr2[i] = count - i;
        arr3[i] = count - i;
    }
    printf("3) Обратный (убывающий):\n");
    start = clock();
    shell(arr1, count);
    end = clock();
    printf("   Сортировка Шелла:    %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(arr2, 0, count - 1);
    end = clock();
    printf("   Быстрая (QuickSort):   %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(arr3, count, sizeof(int), cmp);
    end = clock();
    printf("   Стандартная (qsort): %.4f сек.\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 4) Половина возрастает, половина убывает
    for (int i = 0; i < count / 2; i++) {
        arr1[i] = i;
        arr2[i] = i;
        arr3[i] = i;
    }
    for (int i = count / 2; i < count; i++) {
        arr1[i] = count - i;
        arr2[i] = count - i;
        arr3[i] = count - i;
    }
    printf("4) Половина возрастает, половина убывает:\n");
    start = clock();
    shell(arr1, count);
    end = clock();
    printf("   Сортировка Шелла:    %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qs(arr2, 0, count - 1);
    end = clock();
    printf("   Быстрая (QuickSort):   %.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    qsort(arr3, count, sizeof(int), cmp);
    end = clock();
    printf("   Стандартная (qsort): %.4f сек.\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(arr1);
    free(arr2);
    free(arr3);

    printf("Работа завершена!\n");
    return 0;
}