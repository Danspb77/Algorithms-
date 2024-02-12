def can_establish_contact(n, social_thresholds):
    social_thresholds.sort(reverse=True)
    total_contacts = 0

    # Считаем общее количество контактов, которое можно установить
    for i in range(n):
        total_contacts += min(i, social_thresholds[i])
    
    flag=False
    for el in social_thresholds:
        if el > 1:
            flag=True
            break
    
    # Если общее количество контактов больше или равно n - 1, и хотя бы один разработчик имеет порог больше 1, то контакт установить можно
    return total_contacts >= n - 1 and (flag ==True or n==2)

# Чтение количества тестов
t = int(input())
arr=[]
for _ in range(t):
    # Чтение количества разработчиков и их порогов социальности
    n = int(input())
    social_thresholds = list(map(int, input().split()))
    arr.append(social_thresholds)


for i in range(t):
    
    # Проверка и вывод результата
    if can_establish_contact(len(arr[i]), arr[i]):
        print("Yes")
    else:
        print("No")
