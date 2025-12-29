from collections import defaultdict


class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjacency_list = defaultdict(list)
        self.timer = 0
        self.disc = [-1] * vertices
        self.low = [-1] * vertices
        self.on_stack = [False] * vertices
        self.stack = []
        self.scc_list = []

    def add_edge(self, u, v):
        self.adjacency_list[u].append(v)

    def tarjan(self):
        for i in range(self.vertices):
            if self.disc[i] == -1:
                self.tarjan_dfs(i)

        print("Strongly Connected Components (Tarjan):")
        for scc in self.scc_list:
            print("SCC:", ' '.join(map(str, scc)))

    def tarjan_dfs(self, u):
        self.disc[u] = self.low[u] = self.timer
        self.timer += 1
        self.stack.append(u)
        self.on_stack[u] = True

        for v in self.adjacency_list[u]:
            if self.disc[v] == -1:
                self.tarjan_dfs(v)
                self.low[u] = min(self.low[u], self.low[v])
            elif self.on_stack[v]:
                self.low[u] = min(self.low[u], self.disc[v])

        if self.low[u] == self.disc[u]:
            scc = []
            while True:
                v = self.stack.pop()
                self.on_stack[v] = False
                scc.append(v)
                if v == u:
                    break
            self.scc_list.append(scc)


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
g.tarjan()
