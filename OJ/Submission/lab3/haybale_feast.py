n, m = (int(x) for x in input().split())
F = []
S = []
for _ in range(n):
    f, s =  (int(x) for x in input().split())
    F.append(f)
    S.append(s)
def merge(arr1:list[int], arr2:list[int]):
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
    return merged

def merge_sort(arr:list[int]):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

sorted_s = merge_sort(list(set(S)))
    
def can_achieve_min_spice(min_spice):
    max_sum = 0
    current_sum = 0
        
    # 滑动窗口：计算所有spiciness <= min_spice的连续子数组的最大flavor和
    for i in range(n):
        if S[i] <= min_spice:
            current_sum += F[i]
            max_sum = max(max_sum, current_sum)
        else:
            current_sum = 0
        
    return max_sum >= m
    
left, right = 0, len(sorted_s) - 1
result = -1
    
while left <= right:
    mid = (left + right) // 2
    if can_achieve_min_spice(sorted_s[mid]):
        result = sorted_s[mid]
        right = mid - 1
    else:
        left = mid + 1
    
print(result)

