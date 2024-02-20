# heap sort

# Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является индексом в arr[]. n - размер кучи

def heapify(arr, n, i):
    largest = i  # инициализация самого большого элемента как корня
    l = i*2+1  # left = 2*i + 1
    r = i*2+2  # right = 2*i + 2

    # проверяем существует ли левый дочерний эл. больший корня

    if l < n and arr[l] > arr[i]:
        largest = l

    # проверяем существует ли правый доч. эл . больший корня

    if r < n and arr[r] > arr[i]:
        largest = r

    # заменяем корень, если нужно

    if largest != i:
        arr[largest], arr[i] = arr[i], arr[largest]  # свап

        # применяем  heapify к корню

        heapify(arr, n, largest)

# основная функция для сортировки массива заданного размера

def heapSort (arr):
    n =len (arr)

    #  построение max -heap
    for i in range (n, -1, -1):
        heapify(arr, n, i)
        
    # один за другим извлекаем элементы
    for i in range(n-1 , 0 , -1):
        arr[i],arr[0]=arr[0],arr[i]
        heapify(arr, i, 0)

# Управляющий код для тестирования
arr = [ 12, 11, 13, 5, 6, 7]
heapSort(arr)
n =len(arr)
print ("Sorted array is")
for i in range(n):
    print ("%d" %arr[i])