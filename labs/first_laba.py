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


# # Управляющий код для тестирования
# arr = [12, 11, 13, 5, 6, 7]
# heapSort(arr)
# print("Sorted array is:", arr)


# arr: Исходный массив чисел, который требуется отсортировать.
# N -длина массива arr
# low: Индекс начала текущего подмассива.
# high: Индекс конца текущего подмассива.
# max_depth: Максимальная глубина рекурсии для алгоритма introsort.
# pivot_index: Индекс опорного элемента, используемого для разделения массива.
# pivot: Опорный элемент, выбранный для сравнения и разделения массива в процессе быстрой сортировки.
# i: Индекс элемента массива.
# j: Индекс элемента массива в цикле.
# left_child: Индекс левого потомка в куче.
# right_child: Индекс правого потомка в куче.
# largest: Индекс наибольшего элемента в куче.


def introsort(arr):
    N =len(arr)
    # определение максимальной глубины рекурсии
    max_depth = 2 * int(math.log(N, 2))

    # Вызов вспомогательной функции с массивом, инициализирующей верхние и нижние индексы и максимальную глубину рекурсии
    introsort_helper(arr, 0, N - 1, max_depth)


def introsort_helper(arr, low, high, max_depth):

    # если длина массива меньше или равна 1, то он уже отсортирован
    if low >= high:
        return

    # если глубина рекурсии превышает максимальную глубину, то переключаемся на heapsort
    if max_depth == 0:
        heapsort(arr, low, high)
        return
    print(arr)
    # иначе используем quicksort для разделения массива и сортировки каждой части рекурсивно
    pivot_index = partition(arr, low, high)
    introsort_helper(arr, low, pivot_index - 1, max_depth - 1)
    introsort_helper(arr, pivot_index + 1, high, max_depth - 1)


def partition(arr, low, high):

    # выбираем крайний правый элемент в качестве опорного
    pivot = arr[high]
    i = low - 1

    # проход по массиву, перемещение элементов меньших чем опорный на левую сторону
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
            # print(f'partition sort: i={i}, j={j}, pivot={pivot}, arr={arr}')

    # перемещение опорного элемента на правильную позицию
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def heapsort(arr, low, high):

    # Преобразуем массив в max heap
    heapify(arr, low, high)

    # Извлекаем элементы из кучи один за другим
    for i in range(high, low - 1, -1):
        arr[i], arr[low] = arr[low], arr[i]
        # print(f"heapsort: i={i}, low={low}, high= {high}, arr={arr}")
        heapify(arr, low, i - 1)


def heapify(arr, low, high):

    # Построение max heap снизу вверх

    for i in range(high // 2, low - 1, -1):
        heapify_helper(arr, low, high, i)


def heapify_helper(arr, low, high, i):

    # Поддержание свойства max heap путем рекурсивного обмена элементов
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


# Пример использования:

try:
    with open('./file1.txt', "r") as file:
        arr = [int(num.strip(',')) for num in file.read().split()]
        introsort(arr)
        print("Sorted array:", arr)
except:
    print("Что-то шло нее так. Проверьте путь к файлу и входные данные")

import random

# Генерируем список из 10000 случайных чисел от 0 до 9999
numbers = [random.randint(0, 99) for _ in range(100)]

# Преобразуем список чисел в строку, разделяя числа пробелами
numbers_str = ' '.join(map(str, numbers))

print(numbers_str)


# def insertion_sort(arr):
#     N = len(arr)
#     for i in range(1, N):
#         for j in range(i, 0, -1):
#             if arr[j] < arr[j-1]:
#                 arr[j], arr[j-1] = arr[j-1], arr[j]
#             else:
#                 break
#     return arr


# arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
# print(insertion_sort(arr))
