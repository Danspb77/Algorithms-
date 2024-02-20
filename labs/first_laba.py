# Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является индексом в arr[]. n - размер кучи
def heapify(arr, n, i):
    largest = i  # Инициализация самого большого элемента как корня
    l = 2 * i + 1  # left = 2*i + 1
    r = 2 * i + 2  # right = 2*i + 2

    # Проверяем, существует ли левый дочерний элемент, больший корня
    if l < n and arr[l] > arr[largest]:
        largest = l

    # Проверяем, существует ли правый дочерний элемент, больший корня
    if r < n and arr[r] > arr[largest]:
        largest = r

    # Заменяем корень, если нужно
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # Свап
        # Применяем heapify к корню
        heapify(arr, n, largest)

# Основная функция для сортировки массива заданного размера
def heapSort(arr):
    n = len(arr)

    # Построение max-heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Один за другим извлекаем элементы
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # Свап корня с последним элементом
        heapify(arr, i, 0)

# Управляющий код для тестирования
arr = [12, 11, 13, 5, 6, 7]
heapSort(arr)
print("Sorted array is:", arr)
