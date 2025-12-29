from typing import List, Tuple
import sys
def solve(l: int, r: int, b: List[int], current_a: List[int], operations: List[Tuple[int, int]]):
    if l == r:
        return
    
    mid = (l + r) // 2
    
    for i in range(len(b)):
        if mid < b[i] <= r:
            current_a[i] += 1
            operations.append((2, i))
    
    for j in range(l + 1, mid + 1):
        indices_to_update = []
        for idx, val in enumerate(current_a):
            if val == j:
                indices_to_update.append(idx)
        
        if indices_to_update:
            for idx in indices_to_update:
                current_a[idx] += 1
            operations.append((1, j))
    
    solve(l, mid, b, current_a, operations)     
    solve(mid + 1, r, b, current_a, operations)  

def main_algorithm(b: List[int]) -> List[Tuple[int, int]]:
    n = len(b)
    a = [0] * n
    
    min_val = 0  
    max_val = max(b) 

    operations = []
    
    solve(min_val, max_val, b, a, operations)
    
    return operations

def print_operations(operations: List[Tuple[int, int]]):
    print(len(operations))
    for op_type, param in operations:
        if op_type == 1:
            print(f"1 {param}")
        else:
            print(f"2 {param + 1}")  # 索引从1开始显示

n = int(sys.stdin.readline().strip())
b = [int(x) for x in sys.stdin.readline().strip().split()]
ops = main_algorithm(b)
print_operations(ops)
