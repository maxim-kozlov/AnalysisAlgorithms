from sorts import *

arr = list(map(int, input("Введите массив: ").split()))

print("Сортировка пузырьком с флагом:")
print(bubble_sort(arr))

print("Сортировка вставками")
print(insertion_sort(arr))

print("Сортировка выбором")
print(selection_sort(arr))

