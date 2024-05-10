from matplotlib import pyplot as plt
import numpy as np

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
plt.plot(x, y,'ro', label='Data points')
with open("coeffs.txt") as file:
    legendre_coeffcs=[float(a) for a in file.readline().split()][::-1]
x_vals = np.linspace(min(x), max(x), 100)
y_vals = np.polynomial.legendre.legval(x_vals, legendre_coeffcs)
plt.plot(x_vals, y_vals,'b-', label='Legendre Approximation')
plt.legend()
plt.grid()
plt.show()
