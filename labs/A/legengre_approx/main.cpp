#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

double legendre(int n, double x) {
    if (n == 0)
        return 1.0;
    else if (n == 1)
        return x;
    else
        return ((2.0 * n - 1.0) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
}

std::vector<double> fitLegendre(int degree, const std::vector<double>& x, const std::vector<double>& y) {
    int n = x.size();
    std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1, 0.0));
    std::vector<double> b(degree + 1, 0.0);
    std::vector<double> coeffs(degree + 1, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= degree; ++j) {
            for (int k = 0; k <= degree; ++k) {
                A[j][k] += legendre(j, x[i]) * legendre(degree-k, x[i]);
            }
            b[j] += y[i] * legendre(j, x[i]);
        }
    }

    // Решение системы линейных уравнений методом Гаусса
    for (int i = 0; i <= degree; ++i) {
        for (int j = i + 1; j <= degree; ++j) {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k <= degree; ++k) {
                A[j][k] -= ratio * A[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }

    for (int i = degree; i >= 0; --i) {
        for (int j = i + 1; j <= degree; ++j) {
            b[i] -= A[i][j] * coeffs[j];
        }
        coeffs[i] = b[i] / A[i][i];
    }

    return coeffs;
}

std::pair<std::vector<double>, std::vector<double>> readVectorsFromFile(const std::string& filename) {
    std::vector<double> x;
    std::vector<double> y;
    std::ifstream file(filename);
    double x_value, y_value;
    if (file.is_open()) {
        while (file >> x_value >> y_value) {
            x.push_back(x_value);
            y.push_back(y_value);
        }
        file.close();
    }
    return std::make_pair(x, y);
}

int main() {
    std::pair<std::vector<double>, std::vector<double>> data = readVectorsFromFile("data.txt");
    std::vector<double> x = data.first;
    std::vector<double> y = data.second;
    std::cout<<"Введи степень для аппроксимации: ";
    int degree; // степень полинома Лежандра
    std::cin>>degree;
    std::vector<double> coeffs = fitLegendre(degree, x, y);

    std::cout << "Коэффициенты полинома Лежандра: ";
    for (double coeff : coeffs) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;
    std::ofstream file("coeffs.txt");
    if (file.is_open()) {
        for (int i = 0; i <= degree; ++i) {
            file << coeffs[i] << " ";
        }
        file.close();
    }
    return 0;
}
