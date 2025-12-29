import heapq
from typing import List, Tuple


def dijkstra(n: int, adj: List[List[Tuple[int, int]]], src: int = 0):
    INF = 10 ** 18
    dist = [INF] * n
    dist[src] = 0
    pq: List[Tuple[int, int]] = [(0, src)]

    while pq:
        d, u = heapq.heappop(pq)
        if d != dist[u]:
            continue  # stale entry
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heapq.heappush(pq, (nd, v))
    return dist


def main():
    n = 6
    adj = [[] for _ in range(n)]
    edges = [
        (0, 1, 7), (0, 2, 9), (0, 5, 14), (1, 2, 10), (1, 3, 15),
        (2, 3, 11), (2, 5, 2), (3, 4, 6), (4, 5, 9)
    ]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))  # undirected demo; drop for directed

    dist = dijkstra(n, adj, 0)
    for i, d in enumerate(dist):
        print(f"0 -> {i}: {d}")


if __name__ == "__main__":
    main()
