#! /usr/bin/python3

import sys
import math
    
n,m = map(int,input().split())

ledges = [None]*m
counts = [0]*n
neighb = [None]*n
levels = [None]*n
queue = [None]*n

def longestshortest(startvertex):
    for i in range(0, n):
        levels[i] = 0
    first = last = 0  
    queue[0] = startvertex
    levels[startvertex] = 1
    while (first <= last):
        #print(first)
        crt = queue[first]
        for i in range(0,counts[crt]):
            crtneighb = neighb[crt][i]
            if (levels[crtneighb] == 0):
                last = last + 1
                queue[last] = crtneighb
                levels[crtneighb] = levels[crt]+1
        first = first + 1
    if (last < n-1):
        return 0;
    return levels[queue[last]]    
        
ctr = 0

for i in range (0,m):
    i,j = map(int,input().split())
    i = i-1
    j = j-1
    
    ledges[ctr] = (i,j)
    counts[i] = counts[i] + 1
    counts[j] = counts[j] + 1
    ctr = ctr + 1
    
for i in range(0,n):
    neighb[i] = [None] * counts[i]
    counts[i] = 0
    

for [i,j] in ledges:
    neighb[i][counts[i]]=j
    counts[i] = counts[i] + 1
    neighb[j][counts[j]]=i
    counts[j] = counts[j] + 1
    
    
estimatediam = longestshortest(0)

if (estimatediam == 0): 
    print('-1');
else:
    print(math.ceil(math.log2(estimatediam-1))+1) 
  
     

