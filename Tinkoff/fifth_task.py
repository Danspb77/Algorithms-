from collections import defaultdict

def count_manuls(n, m, q, initial_manuls, friendships, events):
    manuls_count = initial_manuls.copy()
    friends = defaultdict(list)

    for u, v in friendships:
        friends[u].append(v)
        friends[v].append(u)

    for event in events:
        if event[0] == '+':
            u, x = int(event[1]), int(event[2])
            for friend in friends[u]:
                manuls_count[friend - 1] += x
        elif event[0] == '?':
            v = int(event[1])
            print(manuls_count[v - 1] if 1 <= v <= n else "Invalid child number")

# Чтение входных данных
n, m, q = map(int, input().split())
initial_manuls = list(map(int, input().split()))
friendships = [tuple(map(int, input().split())) for _ in range(m)]
events = [input().split() for _ in range(q)]

# Вызов функции и вывод результата
count_manuls(n, m, q, initial_manuls, friendships, events)
