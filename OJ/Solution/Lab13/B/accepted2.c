#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

/*Ioana, 2 BFS*/

#define MAXN 100000
#define MAXM 100000

struct AdjList{
    long m_count;
    long* m_members;
};
typedef struct AdjList AdjList;


long N, M;
long levels[MAXN];
long queue[MAXN];
long edges[MAXM][2];
AdjList neighbours[MAXN];

long longestshortest(long startvertex, int returnVertex)
{
    long first, last, crt, i, crtneighb;
    memset(levels, 0, N* sizeof(long));
    first = last = 0;  
    queue[0] = startvertex;
    levels[startvertex] = 1;  
    while (first <= last) {
        crt = queue[first];
        for (i = 0; i < neighbours[crt].m_count; ++i) {
            crtneighb = neighbours[crt].m_members[i];
            if (levels[crtneighb] == 0) {
                queue[++last] = crtneighb;
                levels[crtneighb] = levels[crt]+1;
            }
            
        }   
        ++first;               
    }
    if (last < N-1)
        return -1;
    if (!returnVertex) 
        return levels[queue[last]]-1;
    else
        return queue[last];
}

int main()
{
    long i, r1, r2;
    size_t ret;
    
    ret = scanf("%lu%lu",&N,&M);
    
    memset (neighbours, 0, N*sizeof(AdjList));

    for (i = 0; i < M; ++i){
        ret = scanf("%lu%lu", &r1, &r2);
        r1--;
        r2--;
        edges[i][0]=r1;
        edges[i][1]=r2;
        neighbours[r1].m_count++;
        neighbours[r2].m_count++;
    }
    
    (void)ret;
      
    for (i = 0; i < N; ++i) { 
        neighbours[i].m_members = (long*)malloc(neighbours[i].m_count*sizeof(long));
        neighbours[i].m_count = 0;
    }
    
    for (i = 0; i < M; ++i) {
        neighbours[edges[i][0]].m_members[neighbours[edges[i][0]].m_count++] = edges[i][1];
        neighbours[edges[i][1]].m_members[neighbours[edges[i][1]].m_count++] = edges[i][0];
    }
    
    long farthest = longestshortest(0,1);
    if (farthest == -1) 
        printf("-1\n");
    else {
        long estimatediam = longestshortest(farthest, 0);    
        printf("%ld\n", (long)(ceil(log2(estimatediam)))+1); 
    }
        
    for (i = 0; i < N; ++i) 
        free (neighbours[i].m_members);
    
    return 0;
}

