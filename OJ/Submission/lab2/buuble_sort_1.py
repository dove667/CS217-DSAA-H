n = int(input())

arr = list(map(int,input().split())) 

count = 0

for i in range(n):
    for j in range(n-1,i,-1):
        if arr[j] < arr[j-1]:
            key = arr[j-1]
            arr[j-1] = arr[j]
            arr[j] = key
            count += 1
print(count)
        