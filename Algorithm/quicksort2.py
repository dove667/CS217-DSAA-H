def partition_3way(arr, low, high):
    if low >= high:
        return low, high
    
    pivot = arr[high]
    lt = low
    gt = high
    i = low
    
    while i <= gt:
        if arr[i] < pivot:
            arr[lt], arr[i] = arr[i], arr[lt]
            lt += 1
            i += 1
        elif arr[i] > pivot:
            arr[i], arr[gt] = arr[gt], arr[i]
            gt -= 1
        else:
            i += 1
    
    return lt, gt


def quick_sort_3way(arr, low, high):
    if low < high:
        lt, gt = partition_3way(arr, low, high)
        quick_sort_3way(arr, low, lt - 1)
        quick_sort_3way(arr, gt + 1, high)


arr = [12, 11, 13, 5, 6, 7, 5, 12, 11 ,7, 7, 7]
print("Original array:", arr)
quick_sort_3way(arr, 0, len(arr) - 1)
print("Sorted array:", arr)
