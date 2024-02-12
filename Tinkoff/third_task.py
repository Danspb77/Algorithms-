def max_money_left(n, m, prices):
    # Инициализируем переменную для хранения максимального остатка денег
    max_money = 0

    # Проходим по размеру кредита от 1 до m
    for borrowed_money in range(1, m + 1):
        remaining_money = borrowed_money  # Оставшиеся деньги после покупок

        # Проходим по списку подарков
        for i in range(n):
            # Если Максим не может позволить себе текущий подарок, переходим к следующему
            if prices[i] <= remaining_money:
                remaining_money -= prices[i]

        # Обновляем максимальный остаток
        max_money = max(max_money, remaining_money)

    return max_money

# Чтение входных данных
n, m = map(int, input().split())
prices = list(map(int, input().split()))
arr=[]

# Вызов функции и вывод результата
result = max_money_left(n, m, prices)
print(result)
