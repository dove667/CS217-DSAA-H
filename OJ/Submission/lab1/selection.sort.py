n = int(input())
myls = list(map(int,input().split(" ")))


for j in range(len(myls)-1):
    small = j
    for i in range(j+1,len(myls)):
        if myls[small] > myls[i]:
            small = i
    key = myls[j]
    myls[j] = myls[small]
    myls[small] = key

myls = map(str,myls)
print(" ".join(myls))
