from collections import deque, defaultdict


class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjacency_list = defaultdict(list)

    def add_edge(self, u, v):
        self.adjacency_list[u].append(v)

    def topological_sort_kahn(self):
        in_degree = [0] * self.vertices

        for i in range(self.vertices):
            for neighbor in self.adjacency_list[i]:
                in_degree[neighbor] += 1

        queue = deque()
        for i in range(self.vertices):
            if in_degree[i] == 0:
                queue.append(i)

        result = []
        while queue:
            u = queue.popleft()
            result.append(u)

            for neighbor in self.adjacency_list[u]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        print("Topological order (Kahn's Algorithm):", ' '.join(map(str, result)))

    def topological_sort_dfs(self):
        visited = [False] * self.vertices
        stack = []

        def dfs_util(u):
            visited[u] = True

            for neighbor in self.adjacency_list[u]:
                if not visited[neighbor]:
                    dfs_util(neighbor)

            stack.append(u)

        for i in range(self.vertices):
            if not visited[i]:
                dfs_util(i)

        result = stack[::-1]
        print("Topological order (DFS):", ' '.join(map(str, result)))


g = Graph(6)
g.add_edge(5, 2)
g.add_edge(5, 0)
g.add_edge(4, 0)
g.add_edge(4, 1)
g.add_edge(2, 3)
g.add_edge(3, 1)

print("Graph edges: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1")
g.topological_sort_kahn()
g.topological_sort_dfs()
