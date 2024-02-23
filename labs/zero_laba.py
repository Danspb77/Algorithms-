# # a - коэффициент перед х**2 (a ∈ R)
# # b - коэффициент перед х, (b ∈ R)
# # c -  свободный коэффициент (c ∈ R)
# # ans - корень уравнения (ans ∈ R)
# # ans1 - корень уравнения (ans1 ∈ R)
# # ans2 - корень уравнения (ans2 ∈ R)
# # D - дискриминант(D ∈ R)


# from string import digits


# def good_parameter(n):  # Функция для проверки входных данных
#     if n[0] in '-+' + digits:
#         if len(n) == 1:
#             return True
#         if all(n[i] in digits + '.' for i in range(1, len(n))) and (n.count('.') == 1 or n.count('.') == 0):
#             return True
#     return False




# def solve_equal(a, b, c):

#     # проверка, что уравнение квадратное
#     if a == 0:
#         # проверка, что это линейное уравнение
#         if b == 0:
#             # проверка, что свободный член = 0
#             if c == 0:
#                 print("X- любое число")
#             else:
#                 print("Решений нет")
#         else:
#             ans = -c/b
#             print("Это линейное уравнение", ans)

#     else:
#         D = b**2-4*a*c
#         # проверка положительный ли дискриминант
#         if D > 0:
#             ans1 = (-b+D**0.5)/(2*a)
#             ans2 = (-b-D**0.5)/(2*a)
#             print("Корни уравнения:", ans1, " , ", ans2)
#         else:
#             # проверка равен ли дискриминант 0
#             if D == 0:
#                 ans = -b/(2*a)
#                 print("Дискриминант = 0, ответ:", ans)
#             else:
#                 print("Решений нет")


# s = input(
#     'Введите через пробел коэффициенты а, b, c:\n').split()
# while len(s) != 3 or (not all(good_parameter(i) for i in s)):
#     print('Введенные числа некорректны\n')
#     # Проверка входных данных
#     s = input(
#         'Введите через пробел коэффициенты а, b, c:\n').split()
# try:
#     a, b, c = (float(i) for i in s)  # Попытка преобразовать числа
# except OverflowError:  # Обработка исключения
#     print('Ошибка переполнения')
# (solve_equal(a, b, c))  # Вызов функции решения уравнения




# Если стрелка на источнике вправо или вверх то E = 1
# Если стрелка на источнике влево или вниз то E = -1
# Если источника нет, то E = 0

E = [-1,  # E1
     1,  # E2
     0,  # E3
     -1,  # E4
     0,  # E5
     0  # E6
     ]

# Если резистор есть, то R=1, иначе R=0
R = [1,  # R1
     1,  # R2
     0,  # R3
     1,  # R4
     0,  # R5
     0  # R6
     ]

# Если катушка есть, то L=1, иначе L=0
L = [0,  # L1
     0,  # L2
     1,  # L3
     0,  # L4
     1,  # L5
     1  # L6
     ]

# Если конденсатор есть, то C=1, иначе C=0
C = [0,  # C1
     0,  # C2
     0,  # C3
     0,  # C4
     1,  # C5
     1  # C6
     ]

I = [(-1 if E[i] == -1 else 1) for i in range(len(E))]
I.insert(0, 0)
E.insert(0, 0)
R.insert(0, 0)
L.insert(0, 0)
C.insert(0, 0)
print("Уравнения узлов:")
print(("I1" if I[1] == -1 else "-I1") + ("+I3" if I[3] == 1 else "-I3") + ("+I4" if I[4] == -1 else "-I4") + "=0")
print(("I4" if I[4] == 1 else "-I4") + ("+I5" if I[5] == -1 else "-I5") + ("+I6" if I[6] == 1 else "-I6") + "=0")
print(("I1" if I[1] == 1 else "-I1") + ("+I2" if I[2] == 1 else "-I2") + ("+I5" if I[5] == 1 else "-I5") + "=0")
print("Уравнения контуров:")
print(("#" + (
           "" if R[1] == 0 else "+I1*R1" if I[1] == -1 else "-I1*R1") + (
           "" if R[4] == 0 else "+I4*R4" if I[4] == 1 else "-I4*R4") + (
           "" if R[5] == 0 else "+I5*R5" if I[5] == 1 else "-I5*R5") + (
           "" if L[1] == 0 else "+I1*j*xL1" if I[1] == -1 else "-I1*j*xL1") + (
           "" if L[4] == 0 else "+I4*j*xL4" if I[4] == 1 else "-I4*j*xL4") + (
           "" if L[5] == 0 else "+I5*j*xL5" if I[5] == 1 else "-I5*j*xL5") + (
           "" if C[1] == 0 else "-I1*j*xC1" if I[1] == -1 else "+I1*j*xC1") + (
           "" if C[4] == 0 else "-I4*j*xC4" if I[4] == 1 else "+I4*j*xC4") + (
           "" if C[5] == 0 else "-I5*j*xC5" if I[5] == 1 else "+I5*j*xC5")
       + "=0" + (
           "" if E[1] == 0 else "+E1" if E[1] == -1 else "-E1") + (
           "" if E[4] == 0 else "+E4" if E[4] == 1 else "-E4") + (
           "" if E[5] == 0 else "+E5" if E[5] == 1 else "-E5")).replace("=0-", "=-").replace("=0+", "=").replace("#+", "").replace("#-", "-"))
print(("#" + (
           "" if R[3] == 0 else "+I3*R3" if I[3] == -1 else "-I3*R3") + (
           "" if R[4] == 0 else "+I4*R4" if I[4] == -1 else "-I4*R4") + (
           "" if R[6] == 0 else "+I6*R6" if I[6] == 1 else "-I6*R6") + (
           "" if L[3] == 0 else "+I3*j*xL3" if I[3] == -1 else "-I3*j*xL3") + (
           "" if L[4] == 0 else "+I4*j*xL4" if I[4] == -1 else "-I4*j*xL4") + (
           "" if L[6] == 0 else "+I6*j*xL6" if I[6] == 1 else "-I6*j*xL6") + (
           "" if C[3] == 0 else "-I3*j*xC3" if I[3] == -1 else "+I3*j*xC3") + (
           "" if C[4] == 0 else "-I4*j*xC4" if I[4] == -1 else "+I4*j*xC4") + (
           "" if C[6] == 0 else "-I6*j*xC6" if I[6] == 1 else "+I6*j*xC6")
       + "=0" + (
           "" if E[3] == 0 else "+E3" if E[3] == -1 else "-E3") + (
           "" if E[4] == 0 else "+E4" if E[4] == -1 else "-E4") + (
           "" if E[6] == 0 else "+E6" if E[6] == 1 else "-E6")).replace("=0-", "=-").replace("=0+", "=").replace("#+", "").replace("#-", "-"))
print(("#" + (
           "" if R[2] == 0 else "+I2*R2" if I[2] == 1 else "-I2*R2") + (
           "" if R[5] == 0 else "+I5*R5" if I[5] == -1 else "-I5*R5") + (
           "" if R[6] == 0 else "+I6*R6" if I[6] == -1 else "-I6*R6") + (
           "" if L[2] == 0 else "+I2*j*xL2" if I[2] == 1 else "-I2*j*xL2") + (
           "" if L[5] == 0 else "+I5*j*xL5" if I[5] == -1 else "-I5*j*xL5") + (
           "" if L[6] == 0 else "+I6*j*xL6" if I[6] == -1 else "-I6*j*xL6") + (
           "" if C[2] == 0 else "-I2*j*xC2" if I[2] == 1 else "+I2*j*xC2") + (
           "" if C[5] == 0 else "-I5*j*xC5" if I[5] == -1 else "+I5*j*xC5") + (
           "" if C[6] == 0 else "-I6*j*xC6" if I[6] == -1 else "+I6*j*xC6")
       + "=0" + (
           "" if E[2] == 0 else "+E2" if E[2] == 1 else "-E2") + (
           "" if E[5] == 0 else "+E5" if E[5] == -1 else "-E5") + (
           "" if E[6] == 0 else "+E6" if E[6] == -1 else "-E6")).replace("=0-", "=-").replace("=0+", "=").replace("#+", "").replace("#-", "-"))
