def is_point_inside_region(a, o, b, p):
    def slope(x1, y1, x2, y2):
        return (y2 - y1) / (x2 - x1) if x2 - x1 != 0 else float('inf')

    slope_AOP = slope(a[0], a[1], o[0], o[1])
    slope_BOP = slope(b[0], b[1], o[0], o[1])
    slope_ABP = slope(a[0], a[1], p[0], p[1])
    slope_BBP = slope(b[0], b[1], p[0], p[1])

    return (slope_ABP >= slope_AOP and slope_ABP <= slope_BOP) or (slope_ABP <= slope_AOP and slope_ABP >= slope_BOP)

# Чтение входных данных
a = list(map(int, input().split()))
o = list(map(int, input().split()))
b = list(map(int, input().split()))
p = list(map(int, input().split()))

# Проверка и вывод результата
if is_point_inside_region(a, o, b, p):
    print("YES")
else:
    print("NO")
