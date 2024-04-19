#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вычисления полиномов Лежандра
double legendre(int degree, double x) {
    if (degree == 0)
        return 1.0;  // P_0(x) = 1
    else if (degree == 1)
        return x;    // P_1(x) = x
    else
        // Рекурсивное выражение для P_n(x)
        return ((2 * degree - 1) * x * legendre(degree - 1, x) - (degree - 1) * legendre(degree - 2, x)) / degree;
}

// Функция для вычисления коэффициентов полинома методом наименьших квадратов
void least_squares_prediction(double *x, double *y, int n, int degree, double *coefficients) {
    // Оставляем без изменений, реализация остается та же
    // ...
}

// Функция для прогнозирования значений для новых входных данных
void predict(double *x, double *coefficients, int degree, double *predicted_values, int m) {
    // Оставляем без изменений, реализация остается та же
    // ...
}

int main() {
    int degree;
    printf("Введите степень полинома: ");
    scanf("%d", &degree);

    FILE *file = fopen("file4.txt", "r");  // Открываем файл для чтения
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);  // Читаем количество точек данных из файла

    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf", &x[i], &y[i]);  // Читаем точки данных из файла
    }

    double coefficients[degree + 1];
    least_squares_prediction(x, y, n, degree, coefficients);  // Вычисляем коэффициенты полинома

    printf("Коэффициенты полинома:\n");
    for (int i = 0; i <= degree; i++) {
        printf("%.6f ", coefficients[i]);  // Выводим коэффициенты полинома
    }
    printf("\n");

    int m = 10;  // Количество новых входных данных
    double new_x[m];
    for (int i = 0; i < m; i++) {
        new_x[i] = i + 1;  // Пример значений для прогноза
    }

    double predicted_values[m];
    predict(new_x, coefficients, degree, predicted_values, m);  // Прогнозируем значения для новых входных данных

    printf("Прогнозируемые значения:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %.6f -> y = %.6f\n", new_x[i], predicted_values[i]);  // Выводим прогнозируемые значения
    }

    fclose(file);  // Закрываем файл

    return 0;
}
