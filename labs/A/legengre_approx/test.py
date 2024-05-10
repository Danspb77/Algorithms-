import matplotlib.pyplot as plt
from scipy.special import legendre
from scipy.optimize import curve_fit
import numpy as np

# Определение данных
def readArraysFromFile(filename):
    x = []
    y = []
    with open(filename) as file:
        for line in file:
            values = line.split()
            x.append(float(values[0]))
            y.append(float(values[1]))
    return np.array(x), np.array(y)

x,y = readArraysFromFile("data.txt")

# Определение функции для аппроксимации
def fit_func(x, *coeffs):
    return sum(c*legendre(i)(x) for i, c in enumerate(coeffs))

# Вычисление коэффициентов полинома Лежандра
degree = 2  # степень полинома Лежандра
popt, pcov = curve_fit(fit_func, x, y, p0=np.zeros(degree+1))

# Генерация точек для построения графика
x_values = np.linspace(x.min(), x.max(), 100)
y_values = fit_func(x_values, *popt)

# Построение графика
plt.figure(figsize=(8, 6))
plt.plot(x, y, 'ro', label='Исходные данные')  # исходные точки
plt.plot(x_values, y_values, 'b-', label='Аппроксимация полиномом Лежандра')  # аппроксимирующий полином
plt.legend()
plt.grid(True)
plt.show()

print(popt[::-1])