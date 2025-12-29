#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

typedef unsigned int u32;
typedef unsigned long long u64;

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

// Buffered 8-bit (256 buckets) LSD radix sort
void radix_sort_8bit_buffered(u32 *a, int n) {
    if (n <= 1) return;
    // tmp buffer for ping-pong
    u32 *tmp = (u32 *)malloc((size_t)n * sizeof(u32));
    // bucket count 2^8
    const int RAD = 256;
    // Tune this to fit L1; BUF_SIZE=16 gives ~16KB buffer (4*256*16 bytes)
    const int BUF_SIZE = 16;

    // small histogram and position arrays
    u32 counts[RAD];
    u32 pos[RAD];

    // per-bucket in-memory buffers (RAD * BUF_SIZE elements)
    u32 *buffers = (u32 *)malloc((size_t)RAD * BUF_SIZE * sizeof(u32));

    u32 *src = a;
    u32 *dst = tmp;

    for (int pass = 0; pass < 4; ++pass) {
        int shift = pass * 8;

        // build histogram
        memset(counts, 0, sizeof(counts));
        for (int i = 0; i < n; ++i) {
            counts[(src[i] >> shift) & 0xFFu]++;
        }

        // prefix-sum -> starting positions
        u32 sum = 0;
        for (int i = 0; i < RAD; ++i) {
            pos[i] = sum;
            sum += counts[i];
        }

        // buffer counters
        u32 buf_cnt[RAD];
        memset(buf_cnt, 0, sizeof(buf_cnt));

        // scatter with small per-bucket buffers, flushing in chunks
        for (int i = 0; i < n; ++i) {
            u32 v = src[i];
            unsigned b = (v >> shift) & 0xFFu;
            u32 idx = buf_cnt[b]++;
            buffers[b * BUF_SIZE + idx] = v;
            if (idx + 1 == (u32)BUF_SIZE) {
                // flush BUF_SIZE items for bucket b
                u32 write_pos = pos[b];
                memcpy(dst + write_pos, buffers + b * BUF_SIZE, BUF_SIZE * sizeof(u32));
                pos[b] = write_pos + BUF_SIZE;
                buf_cnt[b] = 0;
            }
        }

        // flush remaining buffered items (less than BUF_SIZE)
        for (int b = 0; b < RAD; ++b) {
            u32 k = buf_cnt[b];
            if (k) {
                u32 write_pos = pos[b];
                memcpy(dst + write_pos, buffers + b * BUF_SIZE, k * sizeof(u32));
                pos[b] = write_pos + k;
            }
        }

        // swap src/dst for next pass
        u32 *tmp_ptr = src;
        src = dst;
        dst = tmp_ptr;
    }
    free(buffers);
    free(tmp);
}

void init_data(u32 *a, int n, u32 seed) {
    for (int i = 0; i < n; i++) {
        seed = next_integer(seed);
        a[i] = seed;
    }
}

void main() {
    int n;
    u32 seed;
    if (scanf("%d%u", &n, &seed) != 2) return;

    u32 *a = (u32 *)malloc((size_t)n * sizeof(u32));
    if (!a) return;
    init_data(a, n, seed);

    // use the buffered 8-bit radix sort
    radix_sort_8bit_buffered(a, n);

    output_arr(a, (u32)n * sizeof(u32));
    free(a);
}
}

int main() {
    int task_id;
    if (scanf("%d", &task_id) != 1) return 0;

    switch (task_id) {
        case 1:
            Sorting::main();
            break;
    }

    return 0;
}
