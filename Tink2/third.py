# Считываем входные данные
stripes, wall_width, stripe_width = map(int, input().split())
stripe_coordinates = list(map(int, input().split()))

# Проверяем, что координаты левых концов полос заданы в возрастающем порядке
if stripe_coordinates != sorted(stripe_coordinates):
    print("Ошибка: координаты левых концов полос должны быть заданы в возрастающем порядке.")
    exit()

# Объявляем переменную для хранения координат правого конца текущей объединенной полосы
current_right_end = stripe_coordinates[0] + stripe_width

# Вычисляем длину оставшегося пространства на стене, объединяя перекрывающиеся полосы
remaining_space = wall_width - stripe_width  # Изначально считаем, что стена пуста
# Вычисляем длину оставшегося пространства на стене, объединяя перекрывающиеся полосы
for i in range(1, stripes):
    # Проверяем, что индекс i не выходит за пределы списка stripe_coordinates
    if i < len(stripe_coordinates):
        # Если текущая полоса перекрывается с предыдущей, обновляем правый конец текущей объединенной полосы
        if stripe_coordinates[i] <= current_right_end:
            current_right_end = max(current_right_end, stripe_coordinates[i] + stripe_width)
        # Иначе добавляем длину текущей полосы к оставшемуся пространству на стене
        else:
            remaining_space += stripe_coordinates[i] - current_right_end
            current_right_end = stripe_coordinates[i] + stripe_width
    else:
        break  # Если индекс i выходит за пределы списка, прерываем цикл
# Вычисляем количество полных полос обоев, которое нам нужно
full_stripes_needed = remaining_space // stripe_width

# Если остаток от деления больше нуля, добавляем одну дополнительную полосу
if remaining_space % stripe_width > 0:
    full_stripes_needed += 1

# Выводим результат
print(full_stripes_needed)
