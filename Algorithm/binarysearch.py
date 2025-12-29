def binary_search(arr, target):
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2
        
        # Check if target is present at mid
        if arr[mid] == target:
            return mid
        
        # If target is greater, ignore left half
        elif arr[mid] < target:
            low = mid + 1
        
        # If target is smaller, ignore right half
        else:
            high = mid - 1
            
    # If we reach here, then the element was not present
    return -1

arr = [2, 3, 4, 10, 40]
target = 10
result = binary_search(arr, target)
if result != -1:
    print(f"Element is present at index {result}")
else:
    print("Element is not present in array")
