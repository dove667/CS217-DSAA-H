from typing import List, Tuple


def kruskal(n: int, edges: List[Tuple[int, int, int]]):
    parent = list(range(n))
    rank = [0] * n

    def find(x: int) -> int:
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]

    def unite(a: int, b: int) -> bool:
        a, b = find(a), find(b)
        if a == b:
            return False
        if rank[a] < rank[b]:
            a, b = b, a
        parent[b] = a
        if rank[a] == rank[b]:
            rank[a] += 1
        return True

    edges_sorted = sorted(edges, key=lambda x: x[2])
    mst_weight = 0
    mst = []
    for u, v, w in edges_sorted:
        if unite(u, v):
            mst.append((u, v, w))
            mst_weight += w
    return mst_weight, mst


def main():
    n = 6
    edges = [
        (0, 1, 4), (0, 2, 4), (1, 2, 2), (2, 3, 3), (2, 5, 2),
        (2, 4, 4), (3, 4, 3), (5, 4, 3)
    ]
    w, mst = kruskal(n, edges)
    print("Kruskal MST weight:", w)
    for u, v, w in mst:
        print(f"{u} - {v} ({w})")


if __name__ == "__main__":
    main()
