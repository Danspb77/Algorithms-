#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для рекурсивного вычисления полиномов Лежандра
double legendre(int degree, double x) {
    if (degree == 0)
        return 1.0; // Базовый случай: P_0(x) = 1
    else if (degree == 1)
        return x; // Базовый случай: P_1(x) = x
    else
        // Рекурсивное выражение для P_n(x)
        return ((2 * degree - 1) * x * legendre(degree - 1, x) - (degree - 1) * legendre(degree - 2, x)) / degree;
}

// Функция для вычисления коэффициентов полинома методом наименьших квадратов
void least_squares_prediction(double *x, double *y, int n, int degree, double *coefficients) {
    double design_matrix[n][degree + 1];

    // Заполнение матрицы дизайна полиномами Лежандра
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= degree; j++) {
            design_matrix[i][j] = legendre(j, x[i]);
        }
    }

    // Вычисление транспонированной матрицы дизайна
    double transpose_design[degree + 1][n];
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j < n; j++) {
            transpose_design[i][j] = design_matrix[j][i];
        }
    }

    // Вычисление произведения транспонированной матрицы на исходную матрицу
    double temp[degree + 1][degree + 1];
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < n; k++) {
                temp[i][j] += transpose_design[i][k] * design_matrix[k][j];
            }
        }
    }

    // Вычисление правой части системы линейных уравнений
    double rhs[degree + 1];
    for (int i = 0; i <= degree; i++) {
        rhs[i] = 0;
        for (int j = 0; j < n; j++) {
            rhs[i] += transpose_design[i][j] * y[j];
        }
    }

    // Решение системы линейных уравнений для получения коэффициентов полинома
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            coefficients[i] = 0;
            for (int k = 0; k <= degree; k++) {
                coefficients[i] += temp[i][k] * rhs[k];
            }
        }
    }
}

// Функция для прогнозирования значений для новых входных данных
void predict(double *x, double *coefficients, int degree, double *predicted_values, int m) {
    for (int i = 0; i < m; i++) {
        // Инициализация прогнозируемого значения
        predicted_values[i] = 0;
        // Вычисление значения полинома для каждой новой точки данных
        for (int j = 0; j <= degree; j++) {
            predicted_values[i] += coefficients[j] * legendre(j, x[i]);
        }
    }
}

int main() {
    int degree, n, m;
    // Ввод степени полинома Лежандра и количества точек данных
    printf("Введите степень полинома Лежандра: ");
    scanf("%d", &degree);
    printf("Введите количество точек данных: ");
    scanf("%d", &n);

    // Ввод исходных точек данных
    printf("Введите точки данных в формате 'x y':\n");
    double data[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &data[i][0], &data[i][1]);
    }

    // Разделение входных и выходных данных
    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        x[i] = data[i][0];
        y[i] = data[i][1];
    }

    // Прогнозирование методом наименьших квадратов
    double coefficients[degree + 1];
    least_squares_prediction(x, y, n, degree, coefficients);

    // Вывод коэффициентов полинома
    printf("Коэффициенты полинома:\n");
    for (int i = 0; i <= degree; i++) {
        printf("%.6f ", coefficients[i]);
    }
    printf("\n");

    // Ввод количества новых входных данных и новых данных
    printf("Введите количество новых входных данных: ");
    scanf("%d", &m);
    printf("Введите новые входные данные:\n");
    double new_x[m];
    for (int i = 0; i < m; i++) {
        scanf("%lf", &new_x[i]);
    }

    // Прогнозирование значений для новых входных данных
    double predicted_values[m];
    predict(new_x, coefficients, degree, predicted_values, m);

    // Вывод результатов прогнозирования
    printf("Прогнозируемые значения для новых входных данных:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %.6f -> y = %.6f\n", new_x[i], predicted_values[i]);
    }

    return 0;
}
