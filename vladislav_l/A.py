N = int(input())
mas = [int(i) for i in input().split()]
x = int(input())

l = 0
r = N-1

while l < r:
    if mas[l] >= x:
        if mas[r] < x:
            mas[l], mas[r] = mas[r], mas[l]
            l += 1
            r -= 1
        else: 
            r -= 1
    else: 
        l += 1


# Проверка, все ли элементы равны и больше или равны x
if all(m < x for m in mas):
    print(f"{N}\n{0}")
# Проверка, все ли элементы равны и меньше x
elif all(m >= x for m in mas):
    print(f"{0}\n{N}")
else:
    print(f"{l}\n{len(mas)-l}")