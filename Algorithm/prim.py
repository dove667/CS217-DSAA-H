import heapq
from typing import List, Tuple


def prim(n: int, adj: List[List[Tuple[int, int]]]):
    used = [False] * n
    pq: List[Tuple[int, int, int]] = []  # (w, u, from)
    used[0] = True
    for v, w in adj[0]:
        heapq.heappush(pq, (w, v, 0))

    mst = []
    mst_weight = 0
    while pq and len(mst) + 1 < n:
        w, u, frm = heapq.heappop(pq)
        if used[u]:
            continue
        used[u] = True
        mst.append((frm, u, w))
        mst_weight += w
        for v, w2 in adj[u]:
            if not used[v]:
                heapq.heappush(pq, (w2, v, u))
    return mst_weight, mst


def main():
    n = 5
    adj = [[] for _ in range(n)]
    edges = [
        (0, 1, 2), (0, 3, 6), (1, 2, 3), (1, 3, 8), (1, 4, 5), (2, 4, 7), (3, 4, 9)
    ]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    w, mst = prim(n, adj)
    print("Prim MST weight:", w)
    for u, v, w in mst:
        print(f"{u} - {v} ({w})")


if __name__ == "__main__":
    main()
