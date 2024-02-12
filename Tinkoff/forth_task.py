from collections import defaultdict

def build_tree(n, edges):
    # Функция для построения корневого дерева из входных данных
    tree = defaultdict(list)
    for i in range(n):
        if edges[i]:  # Если у вершины есть пакет акций
            p, a, c = edges[i]
            tree[p].append((i + 1, a, c))
    return tree

def min_money_spent(n, k, companies, edges):
    # Функция для определения минимального количества денег, которое Боб должен потратить
    tree = build_tree(n, edges)
    unique_companies = set(companies)
    min_money = float('inf')

    def dfs(node):
        # Рекурсивная функция для обхода дерева в глубину (DFS)
        nonlocal min_money
        if not edges[node - 1]:  # Если у вершины нет пакета акций
            return set()

        package_cost = edges[node - 1][1]  # Стоимость пакета акций (может быть числом или строкой)
        company = edges[node - 1][2]
        companies_set = {company}

        for child, child_cost, child_company in tree[node]:
            child_set = dfs(child)
            companies_set |= child_set
            package_cost += child_cost

        if len(companies_set) == k:
            # Если уникальных компаний в текущем поддереве стало k, обновляем минимальное количество денег
            min_money = min(min_money, int(package_cost))  # Преобразуем стоимость пакета акций в целое число

        return companies_set

    dfs(1)  # Начинаем обход с корня дерева

    return min_money if min_money != float('inf') else -1

# Чтение входных данных
n, k = map(int, input().split())
companies = [input().strip() for _ in range(k)]

# Вместо ввода данных о вершинах, мы просто считываем строки и разбиваем их на части
edges = []
for _ in range(n):
    line = input().strip().split()
    if line:
        edges.append((int(line[0]), int(line[1]), line[2]))
    else:
        edges.append([])

# Вызов функции и вывод результата
result = min_money_spent(n, k, companies, edges)
print(result)
