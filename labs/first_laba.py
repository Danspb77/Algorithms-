# Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является индексом в arr[]. n - размер кучи
import math


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


def introsort(arr):
    # Determine the maximum depth for quicksort recursion
    
    max_depth = 2 * int(math.log(len(arr), 2))

    # Call the helper function with the array, initial low and high indices, and maximum depth
    introsort_helper(arr, 0, len(arr) - 1, max_depth)


def introsort_helper(arr, low, high, max_depth):
    # If the length of the array is less than or equal to 1, it is already sorted
    if low >= high:
        return

    # If the recursion depth exceeds the maximum depth, switch to heapsort
    if max_depth == 0:
        heapsort(arr, low, high)
        return

    # Otherwise, use quicksort to partition the array and sort each partition recursively
    pivot_index = partition(arr, low, high)
    introsort_helper(arr, low, pivot_index - 1, max_depth - 1)
    introsort_helper(arr, pivot_index + 1, high, max_depth - 1)


def partition(arr, low, high):
    # Choose the rightmost element as the pivot
    pivot = arr[high]
    i = low - 1

    # Iterate through the array, swapping elements smaller than the pivot to the left
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    # Move the pivot to its correct position
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def heapsort(arr, low, high):
    # Convert the array into a max heap
    heapify(arr, low, high)

    # Extract elements from the heap one by one
    for i in range(high, low - 1, -1):
        arr[i], arr[low] = arr[low], arr[i]
        heapify(arr, low, i - 1)


def heapify(arr, low, high):
    # Build a max heap from the bottom up
    for i in range(high // 2, low - 1, -1):
        heapify_helper(arr, low, high, i)


def heapify_helper(arr, low, high, i):
    # Maintain the max heap property by recursively swapping elements
    left_child = 2 * i + 1
    right_child = 2 * i + 2
    largest = i

    if left_child <= high and arr[left_child] > arr[largest]:
        largest = left_child
    if right_child <= high and arr[right_child] > arr[largest]:
        largest = right_child

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify_helper(arr, low, high, largest)


# Example usage:
arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
introsort(arr)
print("Sorted array:", arr)
