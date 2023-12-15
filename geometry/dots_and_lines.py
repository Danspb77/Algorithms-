import math

def distance_point_to_point(x1, y1, x2, y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

def distance_point_to_line(x, y, x1, y1, x2, y2):
    return abs((y2 - y1)*x - (x2 - x1)*y + x2*y1 - y2*x1) / math.sqrt((y2 - y1)**2 + (x2 - x1)**2)

def distance_point_to_segment(x, y, x1, y1, x2, y2):
    px, py = x2 - x1, y2 - y1
    dot_product = (x - x1) * px + (y - y1) * py
    if dot_product < 0:
        return distance_point_to_point(x, y, x1, y1)
    length_squared = px**2 + py**2
    if dot_product > length_squared:
        return distance_point_to_point(x, y, x2, y2)
    t = dot_product / length_squared
    projection_x, projection_y = x1 + t * px, y1 + t * py
    return distance_point_to_point(x, y, projection_x, projection_y)

def distance_point_to_ray(x, y, x1, y1, x2, y2):
    px, py = x2 - x1, y2 - y1
    dot_product = (x - x1) * px + (y - y1) * py
    if dot_product < 0:
        return distance_point_to_point(x, y, x1, y1)
    length_squared = px**2 + py**2
    t = dot_product / length_squared
    projection_x, projection_y = x1 + t * px, y1 + t * py
    if t >= 0:
        return distance_point_to_point(x, y, projection_x, projection_y)
    else:
        return distance_point_to_point(x, y, x1, y1)

# Ввод данных
xa, ya = map(int, input().split())
xb, yb = map(int, input().split())
xc, yc = map(int, input().split())
xd, yd = map(int, input().split())

# Вычисление расстояний
dist_ac = distance_point_to_point(xa, ya, xc, yc)
dist_ac_to_cd = distance_point_to_segment(xa, ya, xc, yc, xd, yd)
dist_ac_to_ray_cd = distance_point_to_ray(xa, ya, xc, yc, xd, yd)
dist_ac_to_line_cd = distance_point_to_line(xa, ya, xc, yc, xd, yd)

dist_ab_to_c = distance_point_to_line(xc, yc, xa, ya, xb, yb)
dist_ab_to_cd = distance_point_to_segment(xa, ya, xc, yc, xd, yd)
dist_ab_to_ray_cd = distance_point_to_ray(xa, ya, xc, yc, xd, yd)
dist_ab_to_line_cd = distance_point_to_line(xa, ya, xc, yc, xd, yd)

dist_ray_ab_to_c = distance_point_to_ray(xc, yc, xa, ya, xb, yb)
dist_ray_ab_to_cd = distance_point_to_segment(xa, ya, xc, yc, xd, yd)
dist_ray_ab_to_ray_cd = distance_point_to_ray(xa, ya, xc, yc, xd, yd)
dist_ray_ab_to_line_cd = distance_point_to_line(xa, ya, xc, yc, xd, yd)

dist_line_ab_to_c = distance_point_to_line(xc, yc, xa, ya, xb, yb)
dist_line_ab_to_cd = distance_point_to_segment(xa, ya, xc, yc, xd, yd)
dist_line_ab_to_ray_cd = distance_point_to_ray(xa, ya, xc, yc, xd, yd)
dist_line_ab_to_line_cd = distance_point_to_line(xa, ya, xc, yc, xd, yd)

# Вывод результатов
print(f"{dist_ac:.10f}")
print(f"{dist_ac_to_cd:.10f}")
print(f"{dist_ac_to_ray_cd:.10f}")
print(f"{dist_ac_to_line_cd:.10f}")
print(f"{dist_ab_to_c:.10f}")
print(f"{dist_ab_to_cd:.10f}")
print(f"{dist_ab_to_ray_cd:.10f}")
print(f"{dist_ab_to_line_cd:.10f}")
print(f"{dist_ray_ab_to_c:.10f}")
print(f"{dist_ray_ab_to_cd:.10f}")
print(f"{dist_ray_ab_to_ray_cd:.10f}")
print(f"{dist_ray_ab_to_line_cd:.10f}")
print(f"{dist_line_ab_to_c:.10f}")
print(f"{dist_line_ab_to_cd:.10f}")
print(f"{dist_line_ab_to_ray_cd:.10f}")
print(f"{dist_line_ab_to_line_cd:.10f}")
