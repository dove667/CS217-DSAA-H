def dfs(adj, start, visited, order):
    visited[start] = True
    order.append(start)

    for neighbor in adj[start]:
        if not visited[neighbor]:
            dfs(adj, neighbor, visited, order)


def main():
    graph = [
        [1, 2],    # 0
        [0, 3, 4], # 1
        [0, 4],    # 2
        [1, 4],    # 3
        [1, 2, 3], # 4
    ]

    start_node = 0
    visited = [False] * len(graph)
    visit_order = []

    dfs(graph, start_node, visited, visit_order)
    print(f"DFS visit order starting from node {start_node}: {visit_order}")


if __name__ == "__main__":
    main()
