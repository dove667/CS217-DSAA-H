import sys
n = int(sys.stdin.readline())
count = 0
arr = [int(x) for x in sys.stdin.readline().split()]

def merge(arr1:list[int], arr2:list[int]):
    global count
    i, j = 0, 0
    arr1.append(float('inf'))
    arr2.append(float('inf'))
    merged = []
    for _ in range(len(arr1) + len(arr2)-2):
        if arr1[i] <= arr2[j]:
            merged.append(arr1[i])
            i += 1
        else:
            merged.append(arr2[j])
            j += 1
            if (arr1[i] != float('inf')):
                count += len(arr1)-1-i
            
    return merged

def merge_sort(arr:list[int]):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

merge_sort(arr)

print(count)