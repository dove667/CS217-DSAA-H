#pragma GCC optimize(2,3,"Ofast","unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <stdio.h>
#include <string.h>
#include <algorithm>

typedef unsigned int u32;
typedef unsigned long long u64;

u32 c[1<<16],U=(1<<16)-1;

inline u32 next_integer(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

bool output_arr(void *a, u32 size) {
    if (size % 4) {
        return puts("-1"), 0;
    }

    u32 blocks = size / 4;
    u32 *A = (u32 *)a;
    u32 ret = size;
    u32 x = 23333333;
    for (u32 i = 0; i < blocks; i++) {
        ret = ret ^ (A[i] + x);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
    }

    return printf("%u\n", ret), 1;
}

// ===== header ======

namespace Sorting {
void init_data(u32 *a, int n, u32 seed) {
    for (int i = 0; i < n; i++) {
        seed = next_integer(seed);
        a[i] = seed;
    }
}
void main() {
    int n;
    u32 seed;
    scanf("%d%u", &n, &seed);

    u32 *a = new u32[n];
    u32 *b = new u32[n];
    init_data(a, n, seed);
	
    for(int op=0;op<32;op+=16){
    	memset(c,0,sizeof(c));
		for(int i=n-1;~i;i--)c[(a[i]>>op)&U]++;
		for(int i=1;i<1<<16;i++)c[i]+=c[i-1];
		for(int i=n-1;~i;i--)b[--c[(a[i]>>op)&U]]=a[i];
		std::swap(a,b);
	}
	
    output_arr(a, n * sizeof(u32));
}
}

int main() {
    int task_id;
    scanf("%d", &task_id);

    switch (task_id) {
        case 1:
            Sorting::main();
            break;
    }

    return 0;
}
