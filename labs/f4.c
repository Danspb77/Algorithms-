#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double legendre(int degree, double x) {
    if (degree == 0)
        return 1.0;
    else if (degree == 1)
        return x;
    else
        return ((2 * degree - 1) * x * legendre(degree - 1, x) - (degree - 1) * legendre(degree - 2, x)) / degree;
}
void predict(double *x, double *coefficients, int degree, double *predicted_values, int m) {
    for (int i = 0; i < m; i++) {
        predicted_values[i] = 0;  // Инициализируем прогнозируемое значение для текущей точки
        for (int j = 0; j <= degree; j++) {
            predicted_values[i] += coefficients[j] * legendre(j, x[i]);  // Вычисляем прогнозируемое значение
        }
    }
}


void gauss_elimination(double *A, double *b, double *x, int n) {
    // Прямой ход, преобразование матрицы A к верхнетреугольному виду
    for (int i = 0; i < n; i++) {
        // Находим максимальный элемент в текущем столбце для частичного выбора ведущего элемента
        double maxEl = fabs(A[i * n + i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k * n + i]) > maxEl) {
                maxEl = fabs(A[k * n + i]);
                maxRow = k;
            }
        }

        // Переставляем строки для частичного выбора ведущего элемента
        if (i != maxRow) {
            for (int k = i; k < n; k++) {
                double tmp = A[maxRow * n + k];
                A[maxRow * n + k] = A[i * n + k];
                A[i * n + k] = tmp;
            }
            double tmp = b[maxRow];
            b[maxRow] = b[i];
            b[i] = tmp;
        }

        // Обнуляем элементы ниже диагонали
        for (int k = i + 1; k < n; k++) {
            double c = -A[k * n + i] / A[i * n + i];
            for (int j = i; j < n; j++) {
                if (i == j) {
                    A[k * n + j] = 0;
                } else {
                    A[k * n + j] += c * A[i * n + j];
                }
            }
            b[k] += c * b[i];
        }
    }

    // Обратный ход, вычисление решения системы
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i] / A[i * n + i];
        for (int k = i - 1; k >= 0; k--) {
            b[k] -= A[k * n + i] * x[i];
        }
    }
}

void least_squares_prediction(double *x, double *y, int n, int degree, double *coefficients) {
    double *A = (double *)malloc((degree + 1) * (degree + 1) * sizeof(double));
    double *b = (double *)malloc((degree + 1) * sizeof(double));

    // Строим матрицу A = X^T * X и вектор b = X^T * y
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            A[i * (degree + 1) + j] = 0;
            for (int k = 0; k < n; k++) {
                A[i * (degree + 1) + j] += legendre(i, x[k]) * legendre(j, x[k]);
            }
        }
        b[i] = 0;
        for (int k = 0; k < n; k++) {
            b[i] += legendre(i, x[k]) * y[k];
        }
    }

    // Используем метод Гаусса для решения системы A * coefficients = b
    gauss_elimination(A, b, coefficients, degree + 1);

    free(A);
    free(b);
}

int main() {
    int degree;
    printf("Введите степень полинома Лежандра: ");
    scanf("%d", &degree);

    FILE *file = fopen("file4.txt", "r");  // Открываем файл для чтения
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);  // Читаем количество точек данных из файла

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));
    if (x == NULL || y == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf", &x[i], &y[i]);  // Читаем точки данных из файла
    }
    fclose(file);  // Закрываем файл

    double *coefficients = malloc((degree + 1) * sizeof(double));
    if (coefficients == NULL) {
        printf("Ошибка выделения памяти для коэффициентов\n");
        free(x);
        free(y);
        return 1;
    }

    least_squares_prediction(x, y, n, degree, coefficients);  // Вычисляем коэффициенты полинома

    printf("Коэффициенты полинома:[");
    for (int i = 0; i <= degree; i++) {
        printf("%.6f ", coefficients[i]);  // Выводим коэффициенты полинома
    }
    printf("]\n");

    int m = 10;  // Количество новых входных данных
    double *new_x = malloc(m * sizeof(double));
    double *predicted_values = malloc(m * sizeof(double));
    if (new_x == NULL || predicted_values == NULL) {
        printf("Ошибка выделения памяти для прогнозирования\n");
        free(x);
        free(y);
        free(coefficients);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        new_x[i] = 1 + i * 0.5;  // Пример значений для прогноза
    }

    predict(new_x, coefficients, degree, predicted_values, m);  // Прогнозируем значения для новых входных данных

    printf("Прогнозируемые значения:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %.6f -> y = %.6f\n", new_x[i], predicted_values[i]);  // Выводим прогнозируемые значения
    }

    free(x);
    free(y);
    free(coefficients);
    free(new_x);
    free(predicted_values);

    return 0;
}

