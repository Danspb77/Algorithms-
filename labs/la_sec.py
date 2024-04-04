class Node:
    def __init__(self, data):
        self.data = data  # Значение элемента
        self.prev = None  # Ссылка на предыдущий элемент
        self.next = None  # Ссылка на следующий элемент

class CircularQueue:
    def __init__(self):
        self.head = None  # Начало очереди
        self.tail = None  # Конец очереди

    def enqueue(self, data):
        # Добавление элемента в очередь
        new_node = Node(data)  # Создание нового узла
        if self.head is None:
            # Если очередь пуста
            self.head = new_node
            self.tail = new_node
            self.head.prev = self.tail
            self.tail.next = self.head
        else:
            # Если очередь не пуста
            new_node.prev = self.tail
            new_node.next = self.head
            self.tail.next = new_node
            self.tail = new_node
            self.head.prev = self.tail

    def dequeue(self):
        # Удаление элемента из очереди
        if self.head is None:
            return None  # Если очередь пуста
        data = self.head.data
        if self.head == self.tail:
            # Если в очереди только один элемент
            self.head = None
            self.tail = None
        else:
            # Если в очереди больше одного элемента
            self.head = self.head.next
            self.tail.next = self.head
            self.head.prev = self.tail
        return data

    def is_empty(self):
        return self.head is None  # Проверка на пустоту очереди

    def introspective_sort(self):
        # Интроспективная сортировка
        lst = []
        node = self.head
        while node:
            lst.append(node.data)  # Создание списка из элементов очереди
            node = node.next
        self.head = None
        self.tail = None

        def introsort(lst, start, end, depth_limit):
            # Вспомогательная функция для сортировки списка
            if end - start > 1:
                if depth_limit == 0:
                    lst[start:end] = sorted(lst[start:end])  # Сортировка, если достигнут предел глубины
                    return
                else:
                    pivot = partition(lst, start, end)  # Выбор опорного элемента и разделение
                    introsort(lst, start, pivot, depth_limit - 1)
                    introsort(lst, pivot + 1, end, depth_limit - 1)

        def partition(lst, start, end):
            # Разделение списка для определения опорного элемента
            pivot = lst[start]
            i = start - 1
            j = end + 1
            while True:
                i += 1
                while lst[i] < pivot:
                    i += 1
                j -= 1
                while lst[j] > pivot:
                    j -= 1
                if i >= j:
                    return j
                lst[i], lst[j] = lst[j], lst[i]

        # Запуск сортировки
        introsort(lst, 0, len(lst), 2 * (len(lst)).bit_length())
        for item in lst:
            self.enqueue(item)  # Заново добавляем отсортированные элементы в очередь

# Пример использования:
cq = CircularQueue()
cq.enqueue(5)
cq.enqueue(3)
cq.enqueue(8)
cq.enqueue(2)
cq.enqueue(7)

print("Before sorting:")
node = cq.head
# while node:
#     print(node.data)  # Вывод элементов до сортировки
#     node = node.next
print(node.data)
cq.introspective_sort()  # Сортировка

print("\nAfter sorting:")
node = cq.head

print(node.data)  # Вывод элементов после сортировки
