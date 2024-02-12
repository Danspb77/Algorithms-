class SegmentTree:
    def __init__(self, arr):
        self.n = len(arr)
        self.tree = [float('-inf')] * (4 * self.n)
        self.lazy = [0] * (4 * self.n)
        self.build(arr, 1, 1, self.n)

    def build(self, arr, v, tl, tr):
        if tl == tr:
            self.tree[v] = arr[tl - 1]
        else:
            tm = (tl + tr) // 2
            self.build(arr, 2 * v, tl, tm)
            self.build(arr, 2 * v + 1, tm + 1, tr)
            self.tree[v] = max(self.tree[2 * v], self.tree[2 * v + 1])

    def push(self, v):
        self.tree[2 * v] += self.lazy[v]
        self.lazy[2 * v] += self.lazy[v]
        self.tree[2 * v + 1] += self.lazy[v]
        self.lazy[2 * v + 1] += self.lazy[v]
        self.lazy[v] = 0

    def update(self, v, tl, tr, l, r, add):
        if l > r:
            return
        if l == tl and r == tr:
            self.tree[v] += add
            self.lazy[v] += add
        else:
            self.push(v)
            tm = (tl + tr) // 2
            self.update(2 * v, tl, tm, l, min(r, tm), add)
            self.update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add)
            self.tree[v] = max(self.tree[2 * v], self.tree[2 * v + 1])

    def query(self, v, tl, tr, l, r, k, b):
        if l > r:
            return float('-inf')
        if l == tl and r == tr:
            return min(self.tree[v], k * tl + b)
        self.push(v)
        tm = (tl + tr) // 2
        left_min = self.query(2 * v, tl, tm, l, min(r, tm), k, b)
        right_min = self.query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, k, b)
        return max(left_min, right_min)


def process_queries(n, q, arr, queries):
    segment_tree = SegmentTree(arr)
    result = []

    for query in queries:
        if query[0] == '?':
            l, r, k, b = map(int, query[1:])
            result.append(segment_tree.query(1, 1, n, l, r, k, b))
        elif query[0] == '+':
            l, r, x = map(int, query[1:])
            segment_tree.update(1, 1, n, l, r, x)

    return result


# Ваши входные данные
n, q = 6, 3
arr = [2, 4, 6, 8, 10, 12]
queries = [['?', '2', '5', '3', '0'], ['+', '2', '3', '6'], ['?', '2', '5', '3', '2']]

# Обработка запросов и вывод результата
result = process_queries(n, q, arr, queries)
for res in result:
    print(res)
