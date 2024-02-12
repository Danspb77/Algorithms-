x = int(input())

def sieve_of_eratosthenes(n):
    prime = [True] * (n+1)
    prime[0] = prime[1] = False
    
    p = 2
    while p*p <= n:
        if prime[p]:
            for i in range(p*p, n+1, p):
                prime[i] = False
        p += 1
    
    primes = [i for i in range(n+1) if prime[i]]
    return primes

primes = sieve_of_eratosthenes(1000)
used = set()
c = 0

for el in primes:
    for i in range(1, 1000):
        if x % el**i == 0 and el**i not in used:
            c += 1
            used.add(el**i)
            x = x // el**i

print(c)

# def is_prime(n):
#     if n <= 1:
#         return False
#     if n <= 3:
#         return True
#     if n % 2 == 0 or n % 3 == 0:
#         return False
#     i = 5
#     while i * i <= n:
#         if n % i == 0 or n % (i + 2) == 0:
#             return False
#         i += 6
#     return True

# def f(X):
#     count = 0
#     while X != 1:
#         # Находим наименьший простой делитель числа X
#         for i in range(2, X+1):
#             if is_prime(i) and X % i == 0:
#                 prime = i
#                 break
        
#         # Подсчитываем, сколько раз число X делится на простой делитель
#         power = 0
#         while X % prime == 0:
#             X //= prime
#             power += 1
        
#         # Увеличиваем счетчик операций на количество делений на простой делитель
#         count += power
        
#     return count

# # Считываем число X
# X = int(input())

# # Выводим значение функции f(X)
# print(f(X))
