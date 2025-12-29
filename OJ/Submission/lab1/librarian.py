n, q = map(int, input().strip().split(" "))

books = []
for _ in range(n):
    books.append(input().strip())

demands = []
for _ in range(q):
    length, demand = input().strip().split(" ")
    demands.append(demand)

books_ok = [[]for _ in range(q)]
for i in range(q):
    for book in books:
        if book.endswith(demands[i]):
            books_ok[i].append(book)
        
def sort(myls):
    for j in range(len(myls)-1):
        small = j
        for i in range(j+1,len(myls)):
            if myls[small] > myls[i]:
                small = i
        key = myls[j]
        myls[j] = myls[small]
        myls[small] = key
    return myls

books_ok = [list(map(int, books)) for books in books_ok]
for i in books_ok:
    if i:
        i = sort(i)

for books in books_ok:
    print(books[0]) if books else print(-1)
    