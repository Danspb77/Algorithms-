import math

def intersect_circle_and_line(center_x, center_y, radius, A, B, C):
    # Находим проекцию центра окружности на прямую
    dot_product = A * (center_x - A * center_x - B * center_y) + B * (center_y - A * center_x - B * center_y)
    proj_x = center_x - A * dot_product / (A**2 + B**2)
    proj_y = center_y - B * dot_product / (A**2 + B**2)

    # Находим расстояние от проекции до точки пересечения
    distance = radius * math.sqrt(max(1 - dot_product**2 / ((A**2 + B**2) * radius**2), 0))

    # Находим координаты точек пересечения
    intersection1 = (proj_x + distance * A / math.sqrt(A**2 + B**2), proj_y + distance * B / math.sqrt(A**2 + B**2))
    intersection2 = (proj_x - distance * A / math.sqrt(A**2 + B**2), proj_y - distance * B / math.sqrt(A**2 + B**2))

    return [intersection1, intersection2] if A * B > 0 else [intersection2, intersection1]

# Чтение входных данных
center_x, center_y, radius, A, B, C = map(int, input().split())

# Находим точки пересечения
intersections = intersect_circle_and_line(center_x, center_y, radius, A, B, C)

# Вывод результата
print(len(intersections))
for point in intersections:
    print(f"{point[0]:.8f} {point[1]:.8f}")
