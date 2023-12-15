def find_intersection(x1, y1, x2, y2, x3, y3, x4, y4):
    a1, b1, c1 = y2 - y1, x1 - x2, x2 * y1 - x1 * y2
    a2, b2, c2 = y4 - y3, x3 - x4, x4 * y3 - x3 * y4

    det = a1 * b2 - a2 * b1

    if det == 0:
        if a1 * x3 + b1 * y3 + c1 == 0 and a1 * x4 + b1 * y4 + c1 == 0:
            return 2
        else:
            return 0

    x = (c1 * b2 - c2 * b1) / det
    y = (a1 * c2 - a2 * c1) / det

    return 1, -x, -y

# Ввод данных с точностью до 6 знаков после запятой
x1, y1, x2, y2 = map(float, input().split())
x3, y3, x4, y4 = map(float, input().split())

# Нахождение и вывод результатов с округлением до 5 знаков после запятой
result = find_intersection(x1, y1, x2, y2, x3, y3, x4, y4)
if result == 0:
    print(0)
elif result == 2:
    print(2)
else:
    print(1, "{:.5f}".format(result[1]), "{:.5f}".format(result[2]))
