#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str) && *str != '.' && *str != '-') {
            return false;
        }
        str++;
    }
    return true;
}

double legendre(int degree, double x) {
    if (degree == 0)
        return 1.0;
    else if (degree == 1)
        return x;
    else
        return ((2 * degree - 1) * x * legendre(degree - 1, x) - (degree - 1) * legendre(degree - 2, x)) / degree;
}

void least_squares_prediction(double *x, double *y, int n, int degree, double *coefficients) {
    double design_matrix[n][degree + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= degree; j++) {
            design_matrix[i][j] = legendre(j, x[i]);
        }
    }

    double transpose_design[degree + 1][n];
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j < n; j++) {
            transpose_design[i][j] = design_matrix[j][i];
        }
    }

    double temp[degree + 1][degree + 1];
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < n; k++) {
                temp[i][j] += transpose_design[i][k] * design_matrix[k][j];
            }
        }
    }

    double rhs[degree + 1];
    for (int i = 0; i <= degree; i++) {
        rhs[i] = 0;
        for (int j = 0; j < n; j++) {
            rhs[i] += transpose_design[i][j] * y[j];
        }
    }

    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            coefficients[i] = 0;
            for (int k = 0; k <= degree; k++) {
                coefficients[i] += temp[i][k] * rhs[k];
            }
        }
    }
}

void predict(double *x, double *coefficients, int degree, double *predicted_values, int m) {
    for (int i = 0; i < m; i++) {
        predicted_values[i] = 0;
        for (int j = 0; j <= degree; j++) {
            predicted_values[i] += coefficients[j] * legendre(j, x[i]);
        }
    }
}

int main() {
    int degree, n, m;
    char input[100];

    printf("Введите степень полинома Лежандра: ");
    while (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &degree) == 1) {
            break;
        }
        printf("Ошибка: Пожалуйста, введите целое число для степени полинома Лежандра: ");
    }

    printf("Введите количество точек данных: ");
    while (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &n) == 1) {
            break;
        }
        printf("Ошибка: Пожалуйста, введите целое число для количества точек данных: ");
    }

    printf("Введите точки данных в формате 'x y':\n");
    double data[n][2];
    for (int i = 0; i < n; i++) {
        double x, y;
        printf("Точка %d: ", i + 1);
        while (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%lf %lf", &x, &y) == 2) {
                data[i][0] = x;
                data[i][1] = y;
                break;
            }
            printf("Ошибка: Пожалуйста, введите два числа в формате 'x y' для точки %d: ", i + 1);
        }
    }

    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        x[i] = data[i][0];
        y[i] = data[i][1];
    }

    double coefficients[degree + 1];
    least_squares_prediction(x, y, n, degree, coefficients);

    printf("Коэффициенты полинома:\n");
    for (int i = 0; i <= degree; i++) {
        printf("%.6f ", coefficients[i]);
    }
    printf("\n");

    printf("Введите количество новых входных данных: ");
    while (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &m) == 1) {
            break;
        }
        printf("Ошибка: Пожалуйста, введите целое число для количества новых входных данных: ");
    }

    printf("Введите новые входные данные:\n");
    double new_x[m];
    for (int i = 0; i < m; i++) {
        printf("Новая точка %d: ", i + 1);
        while (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%lf", &new_x[i]) == 1) {
                break;
            }
            printf("Ошибка: Пожалуйста, введите число для новой точки %d: ", i + 1);
        }
    }

    double predicted_values[m];
    predict(new_x, coefficients, degree, predicted_values, m);

    printf("Прогнозируемые значения для новых входных данных:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %.6f -> y = %.6f\n", new_x[i], predicted_values[i]);
    }

    return 0;
}
