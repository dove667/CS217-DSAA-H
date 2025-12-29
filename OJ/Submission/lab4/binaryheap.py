import sys
import heapq

def solve_heap_problem():
    n = int(sys.stdin.readline())
    if n == 0:
        print(0)
        return

    min_heap = []
    
    result_operations = []

    for _ in range(n):
        line = sys.stdin.readline().strip()
        parts = line.split()
        command = parts[0]

        if command == "insert":
            val = int(parts[1])
            heapq.heappush(min_heap, val)
            result_operations.append(line)
        
        elif command == "getMin":
            val = int(parts[1])
            
            while min_heap and min_heap[0] < val:
                heapq.heappop(min_heap)
                result_operations.append("removeMin")

            if not min_heap or min_heap[0] > val:
                heapq.heappush(min_heap, val)
                result_operations.append(f"insert {val}")
                
            result_operations.append(line)

        elif command == "removeMin":
            if not min_heap:
                result_operations.append("insert 1") 
            else:
                heapq.heappop(min_heap)
            result_operations.append("removeMin")

    print(len(result_operations))
    for op in result_operations:
        print(op)

solve_heap_problem()