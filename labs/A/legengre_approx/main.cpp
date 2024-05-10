#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// Функция для вычисления полинома Лежандра степени n в точке x
// Полиномы Лежандра P_n(x) вычисляются рекурсивно по следующим формулам:
// P_0(x) = 1
// P_1(x) = x
// (n + 1)P_{n+1}(x) = (2n + 1)xP_n(x) - nP_{n-1}(x)
// Где:
//   - n - степень полинома Лежандра
//   - x - значение аргумента
double legendre(int n, double x) {
    if (n == 0)
        return 1.0;
    else if (n == 1)
        return x;
    else
        return ((2.0 * n - 1.0) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
}

// Функция для аппроксимации данных полиномом Лежандра заданной степени
std::vector<double> fitLegendre(int degree, const std::vector<double>& x, const std::vector<double>& y) {
    int n = x.size();
    std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1, 0.0));
    std::vector<double> b(degree + 1, 0.0);
    std::vector<double> coeffs(degree + 1, 0.0);

    // Построение матрицы A и вектора b для системы уравнений
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= degree; ++j) {
            for (int k = 0; k <= degree; ++k) {
                A[j][k] += legendre(j, x[i]) * legendre(degree-k, x[i]); // Заполнение матрицы A
            }
            b[j] += y[i] * legendre(j, x[i]); // Заполнение вектора b
        }
    }

    // Решение системы линейных уравнений методом Гаусса
    for (int i = 0; i <= degree; ++i) {
        // Прямой ход метода Гаусса: приведение матрицы к верхнетреугольному виду
        for (int j = i + 1; j <= degree; ++j) {
            // Вычисляем множитель, на который будем умножать строку i для вычитания из строки j
            double ratio = A[j][i] / A[i][i];
            // Вычитаем из строки j строку i, умноженную на вычисленный множитель
            for (int k = i; k <= degree; ++k) {
                A[j][k] -= ratio * A[i][k];
            }
            // Также корректируем соответствующий элемент в векторе b
            b[j] -= ratio * b[i];
        }
    }

    // Обратный ход метода Гаусса для нахождения коэффициентов
    for (int i = degree; i >= 0; --i) {
        // Вычисляем значение i-го коэффициента, начиная с последнего
        // Перебираем все коэффициенты после i-го и вычитаем их вклад в i-й коэффициент
        for (int j = i + 1; j <= degree; ++j) {
            b[i] -= A[i][j] * coeffs[j];
        }
        // Вычисляем значение i-го коэффициента, деля b[i] на соответствующий элемент матрицы A
        coeffs[i] = b[i] / A[i][i];
    }

    return coeffs;
}

std::pair<std::vector<double>, std::vector<double>> readVectorsFromFile(const std::string& filename) {
    std::vector<double> x;
    std::vector<double> y;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Невозможно открыть файл: проверьте путь к файлу");
    }
    double x_value, y_value;
    while (file >> x_value >> y_value) {
        x.push_back(x_value);
        y.push_back(y_value);
    }
    file.close();
    return std::make_pair(x, y);
}

int main() {
    std::vector<double> x, y;

    try {
        std::pair<std::vector<double>, std::vector<double>> data = readVectorsFromFile("data.txt");
        x = data.first;
        y = data.second;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; // Вывод только текста ошибки без технической информации
        return 1;
    }

    // Запрос степени для аппроксимации
    std::cout << "Введи степень для аппроксимации: ";
    int degree; // степень полинома Лежандра
    std::cin >> degree;

    // Аппроксимация и вывод коэффициентов
    std::vector<double> coeffs = fitLegendre(degree, x, y);
    std::cout << "Коэффициенты полинома Лежандра: ";
    for (double coeff : coeffs) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;

    // Запись коэффициентов в файл
    std::ofstream file("coeffs.txt");
    if (file.is_open()) {
        for (int i = 0; i <= degree; ++i) {
            file << coeffs[i] << " ";
        }
        file.close();
    }

    return 0;
}
