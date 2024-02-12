# A,B,colors,stripes=map(int, input().split())

# for i in range(stripes):
#     typ, n ,color= map(int,input().split())
def draw_stripes(screen, stripes):
    for stripe in stripes:
        if stripe[0] == 1:  # Если тип полосы - строка
            for j in range(len(screen[0])):
                screen[stripe[1]-1][j] = stripe[2]
        elif stripe[0] == 2:  # Если тип полосы - столбец
            for i in range(len(screen)):
                screen[i][stripe[1]-1] = stripe[2]

def count_pixels(screen, colors):
    pixel_count = {}
    for i in range(len(screen)):
        for j in range(len(screen[0])):
            color = screen[i][j]
            if color != 0:
                if color not in pixel_count:
                    pixel_count[color] = 1
                else:
                    pixel_count[color] += 1
    return pixel_count

# Считываем размеры экрана и количество цветов
A, B, N, Q = map(int, input().split())

# Инициализируем экран и заполняем его нулями (черным цветом)
screen = [[0]*B for _ in range(A)]

# Считываем операции рисования полос
stripes = []
for _ in range(Q):
    stripes.append(list(map(int, input().split())))

# Рисуем полосы на экране
draw_stripes(screen, stripes)

# Подсчитываем количество пикселей для каждого цвета
pixel_count = count_pixels(screen, N)

# Формируем строку с результатом
result = ' '.join(str(pixel_count.get(i, 0)) for i in range(1, N+1))
print(result)
