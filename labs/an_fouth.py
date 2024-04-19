import numpy as np
from scipy.special import eval_legendre

def least_squares_prediction(x, y, degree):
    """
    Функция прогнозирования методом наименьших квадратов с использованием полиномов Лежандра.

    Параметры:
    - x: Входные данные (массив)
    - y: Выходные данные (массив)
    - degree: Степень полинома Лежандра

    Возвращает:
    - Массив коэффициентов полинома
    """

    # Подготовка матрицы дизайна, используя полиномы Лежандра
    design_matrix = np.array([eval_legendre(i, x) for i in range(degree + 1)]).T
    print(design_matrix)
    # Решение уравнения наименьших квадратов для получения коэффициентов
    coefficients = np.linalg.lstsq(design_matrix, y, rcond=None)[0]

    return coefficients

def predict(x, coefficients):
    """
    Функция прогнозирования значений на основе полученных коэффициентов полинома.

    Параметры:
    - x: Входные данные (массив)
    - coefficients: Коэффициенты полинома

    Возвращает:
    - Прогнозируемые значения
    """
    # Вычисление значений полинома для входных данных
    predicted_values = np.array([eval_legendre(i, x) for i in range(len(coefficients))]).T.dot(coefficients)
    
    return predicted_values

# Пример использования:

# Ввод данных пользователем
degree = int(input("Введите степень полинома Лежандра: "))
n = int(input("Введите количество точек данных: "))
print("Введите точки данных в формате 'x y':")
data = []
for i in range(n):
    point = tuple(map(float, input().split()))
    data.append(point)
data = np.array(data)

# Разделение входных и выходных данных
x = data[:, 0]
y = data[:, 1]

# Прогнозирование методом наименьших квадратов
coefficients = least_squares_prediction(x, y, degree)

# Вывод коэффициентов полинома
print("Коэффициенты полинома:", coefficients)

# Прогнозирование значений для новых входных данных
new_x = np.linspace(min(x), max(x), 10)  # Генерация новых входных данных
predicted_values = predict(new_x, coefficients)

# Вывод результатов
print("Прогнозируемые значения для новых входных данных:")
for i in range(len(new_x)):
    print("x =", new_x[i], " ->  y =", predicted_values[i])
