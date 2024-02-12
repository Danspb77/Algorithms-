N = int(input())
S = input()

s1 = S
s2 = S


def remove_char(s, index):
    return s[:index] + s[index+1:]


count = 0

# for c  in range(1,N+1):
for i in range(len(s1)):
    for j in range(i+1, len(s2)-1):
        print(s1[i],s2[j])
        if remove_char(S, i) == remove_char(S, j):
            count += 1
            print("-----",s1[i],s2[j])
            

print(count)


# def sadness_indicator(N, password):
#     # Создаем словарь для отслеживания индексов символов
#     indexes = {}
#     for i, char in enumerate(password):
#         if char in indexes:
#             indexes[char].append(i)
#         else:
#             indexes[char] = [i]

#     # Инициализируем показатель печали
#     sadness = 0

#     # Перебираем каждый символ пароля
#     for i, char in enumerate(password):
#         # Для каждого символа проверяем, сколько раз он встречается в словаре
#         count = len(indexes[char])
#         # Увеличиваем показатель печали на количество пар символов с одинаковыми значениями
#         sadness += count - 1

#     # Возвращаем общий показатель печали
#     return sadness


# # Считываем входные данные
# N = int(input())
# password = input()

# # Выводим показатель печали
# print(sadness_indicator(N, password))
