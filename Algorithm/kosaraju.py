from collections import defaultdict


class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjacency_list = defaultdict(list)
        self.reverse_adjacency_list = defaultdict(list)

    def add_edge(self, u, v):
        self.adjacency_list[u].append(v)
        self.reverse_adjacency_list[v].append(u)

    def kosaraju(self):
        stack = []
        visited = [False] * self.vertices

        def fill_order(u):
            visited[u] = True
            for neighbor in self.adjacency_list[u]:
                if not visited[neighbor]:
                    fill_order(neighbor)
            stack.append(u)

        for i in range(self.vertices):
            if not visited[i]:
                fill_order(i)

        visited = [False] * self.vertices
        print("Strongly Connected Components:")

        def dfs_reverse(u):
            visited[u] = True
            print(u, end=' ')
            for neighbor in self.reverse_adjacency_list[u]:
                if not visited[neighbor]:
                    dfs_reverse(neighbor)

        while stack:
            u = stack.pop()
            if not visited[u]:
                print("SCC: ", end='')
                dfs_reverse(u)
                print()


g = Graph(8)
g.add_edge(0, 1)
g.add_edge(1, 2)
g.add_edge(2, 3)
g.add_edge(2, 4)
g.add_edge(3, 0)
g.add_edge(4, 5)
g.add_edge(5, 6)
g.add_edge(6, 4)
g.add_edge(6, 7)

print("Graph edges: 0->1, 1->2, 2->3, 2->4, 3->0, 4->5, 5->6, 6->4, 6->7")
g.kosaraju()
