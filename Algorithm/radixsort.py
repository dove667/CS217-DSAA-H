def counting_sort_by_digit(arr, exp):
    n = len(arr)
    count = [0] * 10
    
    for i in range(n):
        digit = (arr[i] // exp) % 10
        count[digit] += 1
    
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    output = [0] * n
    for i in range(n - 1, -1, -1):
        digit = (arr[i] // exp) % 10
        count[digit] -= 1
        output[count[digit]] = arr[i]
    
    return output


def radix_sort(arr):
    if not arr:
        return []
    
    max_val = max(arr)
    exp = 1
    
    while max_val // exp > 0:
        arr = counting_sort_by_digit(arr, exp)
        exp *= 10
    
    return arr


a1 = [170, 45, 75, 90, 802, 24, 2, 66]
a2 = [3, 3, 2, 1, 0, 2, 5, 5]
a3 = []
a4 = [1000, 5, 300, 12, 9999, 7]

print("input1:", a1)
print("radix1:", radix_sort(a1))

print("input2:", a2)
print("radix2:", radix_sort(a2))

print("input3:", a3)
print("radix3:", radix_sort(a3))

print("input4:", a4)
print("radix4:", radix_sort(a4))
