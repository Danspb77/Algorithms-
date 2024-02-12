# a - коэффициент перед х**2 (a ∈ R)
# b - коэффициент перед х, (b ∈ R)
# c -  свободный коэффициент (c ∈ R)
# ans - корень уравнения (ans ∈ R)
# ans1 - корень уравнения (ans1 ∈ R)
# ans2 - корень уравнения (ans2 ∈ R)
# D - дискриминант(D ∈ R)





print("Введите через пробел коэффициенты а, b, c")


a, b, c = map(float, input().split())


# проверка, что уравнение квадратное
if a == 0:
    # проверка, что это линейное уравнение
    if b == 0:
        # проверка, что свободный член = 0
        if c == 0:
            print("X- любое число")
        else:
            print("Решений нет")
    else:
        ans = -c/b
        print("Это линейное уравнение", ans)


else:
    D = b**2-4*a*c
    # проверка положительный ли дискриминант
    if D > 0:
        ans1 = (-b+D**0.5)/(2*a)
        ans2 = (-b-D**0.5)/(2*a)
        print("Корни уравнения:",ans1," , ", ans2)
    else:
        # проверка равен ли дискриминант 0
        if D == 0:
            ans = -b/(2*a)
            print("Дискриминант = 0",ans)
        else:
            print("Решений нет")
