n, m = map(int, input().split())
lines = []
for _ in range(n):
    s = input().strip()
    line = list(map(int, s.split(" ")))
    lines.append(line)
M = int(m * 1.5)

def mat_sort (mylist:list[list[int]]) -> list[list[int]]:
    for j in range(len(mylist)):
        if j == 0:
            continue
        i = j - 1
        key = mylist[j]
        while (i >= 0 and mylist[i][1] <= key[1]):
            if mylist[i][1] == key[1] and mylist[i][0] < key[0]:
                break
            mylist[i+1] = mylist[i]
            i = i - 1
        mylist[i+1] = key
    return mylist

sorted_lines = mat_sort(lines)
#print(sorted_lines)
equal = []
#print(f"M={M}")
for i in range(1, n - M + 1):
    if sorted_lines[M+i-1][1] == sorted_lines[M-1][1]:
        equal.append(sorted_lines[M+i-1])
        #print(f"i:{i},append{sorted_lines[M+i]}")
    else:
         break

#print(f"equal:\n{equal}")
cut_lines = sorted_lines[:M]
A = cut_lines[-1][1]
B = M + len(equal)

print(f"{A} {B}")

for line in cut_lines:
    line = " ".join((map(str,line)))
    print(line)

for line in equal:
    line = " ".join((map(str,line)))
    print(line)
