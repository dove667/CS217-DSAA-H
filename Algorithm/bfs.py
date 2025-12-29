from collections import deque

def bfs(adj, start):
    visited = [False] * len(adj)
    order = []
    queue = deque([start])
    visited[start] = True

    while queue:
        node = queue.popleft()
        order.append(node)

        for neighbor in adj[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)

    return order


def main():
    graph = [
        [1, 2],    # 0
        [0, 3, 4], # 1
        [0, 4],    # 2
        [1, 4],    # 3
        [1, 2, 3], # 4
    ]

    start_node = 0
    visit_order = bfs(graph, start_node)
    print(f"BFS visit order starting from node {start_node}: {visit_order}")


if __name__ == "__main__":
    main()
