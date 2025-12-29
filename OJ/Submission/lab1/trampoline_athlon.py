N = int(input().strip())

Cs = []
Ps = []
Ess = []

for _ in range(N):
    s = input().split()
    Cs.append(s[0])
    Ps.append(int(s[1]))
    Ess.append(list(map(int,s[2:])))

def sort(myls:list[int]) -> list[int]:
    for j in range(len(myls)-1):
        small = j
        for i in range(j+1,len(myls)):
            if myls[small] > myls[i]:
                small = i
        key = myls[j]
        myls[j] = myls[small]
        myls[small] = key
    return myls

def mat_sort (mylist:list[list[int]]) -> list[list[int]]:
    for j in range(len(mylist)):
        if j == 0:
            continue
        i = j - 1
        key = mylist[j]
        while (i >= 0 and mylist[i][1] < key[1]):
            mylist[i+1] = mylist[i]
            i = i - 1
        mylist[i+1] = key
    return mylist

def count_score(p:int,Es:list[int]) -> int:
    Es = sort(Es)[1:-1]
    score = p * 10
    for E in Es:
        score = score + E
    return score

scores = []
for p, Es in zip(Ps, Ess):
    scores.append(count_score(p, Es))

arrs = []
for C, score in zip(Cs, scores):
    arrs.append([C, score])

arrs = mat_sort(arrs)

medallists = []

for i in range(len(arrs)):
    team = arrs[i]

    first_diff_idx = -1
    for k in range(i - 1, -1, -1):
         if arrs[k][1] != team[1]:
             first_diff_idx = k
             break
    num_strictly_higher = first_diff_idx + 1

    if num_strictly_higher <= 2 and len(medallists) < 100:
        medallists.append(team)
    else:
        break

for winner in medallists:
    print(f"{winner[0]} {winner[1]}")