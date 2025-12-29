n = int(input())

mylist = list(map(int, input().split()))

for j in range(len(mylist)):
    if j == 0:
        continue
    i = j - 1
    key = mylist[j]
    while (i >= 0 and mylist[i] > key):
        mylist[i+1] = mylist[i]
        i = i - 1
    mylist[i+1] = key

mylist_sort = " ".join(map(str,mylist))
print(mylist_sort)