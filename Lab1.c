#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

struct student {
    char famil[20];
    char name[20];
    char facult[20];
    int Nomzach;
};

int main(void) {
    // Настройка корректного отображения кириллицы в консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned int)time(NULL));

    // ================= ЗАДАНИЯ 1, 2 и 3 =================
    printf("========== ЗАДАНИЯ 1, 2 и 3 ==========\n");
    int n;
    printf("Введите размер одномерного массива: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка ввода размера!\n");
        return 1;
    }

    // Динамическое выделение памяти
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Сгенерированный массив: ");
    for (int i = 0; i < n; i++) {
        arr[i] = 10 + rand() % 90; // случайные числа от 10 до 99
        printf("%d ", arr[i]);
    }
    printf("\n");

    int min_val = arr[0];
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    printf("Максимальный элемент: %d\n", max_val);
    printf("Минимальный элемент: %d\n", min_val);
    printf("Разница (max - min): %d\n\n", max_val - min_val);

    free(arr); // освобождение динамической памяти

    // ================= ЗАДАНИЕ 4 =================
    printf("========== ЗАДАНИЕ 4 ==========\n");
    int rows = 3, cols = 4;
    int matrix[3][4];

    printf("Сгенерированный двумерный массив (3x4):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 1 + rand() % 9;
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nСуммы по строкам:\n");
    for (int i = 0; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        printf("Строка %d: %d\n", i + 1, row_sum);
    }

    printf("\nСуммы по столбцам:\n");
    for (int j = 0; j < cols; j++) {
        int col_sum = 0;
        for (int i = 0; i < rows; i++) {
            col_sum += matrix[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }
    printf("\n");

    // ================= ЗАДАНИЕ 5 =================
    printf("========== ЗАДАНИЕ 5 ==========\n");
    struct student students[3] = {
        {"Иванов", "Иван", "ВТ", 1001},
        {"Петров", "Алексей", "ИВТ", 1002},
        {"Сидоров", "Михаил", "ПИ", 1003}
    };

    printf("База студентов загружена.\n");
    char search_famil[20];
    printf("Введите фамилию для поиска (например, Иванов): ");
    scanf("%19s", search_famil);

    int found = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(students[i].famil, search_famil) == 0) {
            printf("\n--- Студент найден ---\n");
            printf("Фамилия: %s\n", students[i].famil);
            printf("Имя: %s\n", students[i].name);
            printf("Факультет: %s\n", students[i].facult);
            printf("Номер зачетки: %d\n", students[i].Nomzach);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nСтудент с такой фамилией не найден.\n");
    }

    printf("\nЛабораторная работа завершена!\n");
    return 0;
}