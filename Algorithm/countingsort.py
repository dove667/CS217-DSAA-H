def counting_sort(arr):
    if not arr:
        return []
    
    min_val = min(arr)
    max_val = max(arr)
    range_val = max_val - min_val + 1
    
    count = [0] * range_val
    for x in arr:
        count[x - min_val] += 1
    
    for i in range(1, range_val):
        count[i] += count[i - 1]
    
    output = [0] * len(arr)
    for i in range(len(arr) - 1, -1, -1):
        idx = arr[i] - min_val
        count[idx] -= 1
        output[count[idx]] = arr[i]
    
    return output


data = [4, -1, 3, 0, 3, -1, 2, 4, 0]
print("Original array:", data)
sorted_data = counting_sort(data)
print("Sorted array:", sorted_data)
