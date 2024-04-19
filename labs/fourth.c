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

void least_squares_prediction(double *x, double *y, int n, int degree, double *coefficients) {
    // Оставляем без изменений
    // ...
}

void predict(double *x, double *coefficients, int degree, double *predicted_values, int m) {
    // Оставляем без изменений
    // ...
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <степень полинома>\n", argv[0]);
        return 1;
    }

    int degree = atoi(argv[1]);

    FILE *file = fopen("file4.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf", &x[i], &y[i]);
    }

    double coefficients[degree + 1];
    least_squares_prediction(x, y, n, degree, coefficients);

    printf("Коэффициенты полинома:\n");
    for (int i = 0; i <= degree; i++) {
        printf("%.6f ", coefficients[i]);
    }
    printf("\n");

    int m = 10;  // Количество новых входных данных
    double new_x[m];
    for (int i = 0; i < m; i++) {
        new_x[i] = i + 1;  // Пример значений для прогноза
    }

    double predicted_values[m];
    predict(new_x, coefficients, degree, predicted_values, m);

    printf("Прогнозируемые значения для новых входных данных:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %.6f -> y = %.6f\n", new_x[i], predicted_values[i]);
    }

    fclose(file);

    return 0;
}
