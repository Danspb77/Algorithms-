import math

def find_intersection_points(x1, y1, r1, x2, y2, r2):
    distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

    if distance > r1 + r2:
        return 0  # Окружности не пересекаются

    if distance < abs(r1 - r2):
        return 0  # Одна окружность вложена в другую

    if distance == 0 and r1 == r2:
        return 3  # Окружности совпадают

    # Находим точку пересечения прямой, соединяющей центры окружностей, с их внешней общей касательной
    a = (r1**2 - r2**2 + distance**2) / (2 * distance)
    h = math.sqrt(r1**2 - a**2)

    # Находим координаты точек пересечения
    x3 = x1 + a * (x2 - x1) / distance
    y3 = y1 + a * (y2 - y1) / distance

    intersection_points = [(x3 + h * (y2 - y1) / distance, y3 - h * (x2 - x1) / distance),
                           (x3 - h * (y2 - y1) / distance, y3 + h * (x2 - x1) / distance)]

    if distance == r1 + r2:
        return 1, (result[1][0], result[1][1])  # Окружности касаются внешне

    return 2, (x3, y3, h, distance - a) + intersection_points

# Чтение числа тестов
num_tests = int(input())

# Обработка каждого теста
for _ in range(num_tests):
    x1, y1, r1 = map(int, input().split())
    x2, y2, r2 = map(int, input().split())

    result = find_intersection_points(x1, y1, r1, x2, y2, r2)

    # Вывод результатов
    print(result[0])
    if result[0] > 0:
        print(f"{result[1][0]:.10f} {result[1][1]:.10f}")
        if result[0] == 2:
            print(f"{result[1][2]:.10f} {result[1][3]:.10f}")
            print(f"{result[1][4]:.10f} {result[1][5]:.10f}")
