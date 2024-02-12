def can_form_tinkoff(s):
    flag=False
    if len(s)==7:
        flag=True
    # Создаем словарь, чтобы отслеживать количество каждой буквы в строке
    char_count = {}
    for char in s:
        char_count[char] = char_count.get(char, 0) + 1

    # Проверяем, что в строке есть не меньше букв для слова "TINKOFF"
    p = all(char_count.get(letter, 0) >= "TINKOFF".count(letter) for letter in "TINKOFF")

    if p and flag:
        return "Yes"
    else:
        return "No"

# Чтение количества тестов
t = int(input())
arr = []

for _ in range(t):
    # Чтение строки из больших латинских букв
    s = input().strip()
    arr.append(can_form_tinkoff(s))

for el in arr:
    print(el)
