def rindex(lst, element):
    for i in range(len(lst) - 1, -1, -1):
        if lst[i] == element:
            return i

def solve():
    n = int(input())
    v = list(map(int, input().split())) 
    a = list(map(int, input().split()))  
    
    val_to_current_pos = {}
    for i in range(0, n):
        if a[i] not in val_to_current_pos:
            val_to_current_pos[a[i]] = []
        val_to_current_pos[a[i]].append(i)

    # The result binary string, to be filled from right to left.
    b = [' '] * n

    # Iterate backwards from the last insertion to the first.
    for i in range(n-1, -1, -1):
        val_to_check = v[i]
        current_pos = val_to_current_pos[val_to_check][-1]

        # --- Check if b_i = '0' (min-heap insertion) is possible ---
        possible0 = True
        # 1. Check swap conditions along the sift-up path.
        path_iter = i
        while path_iter != current_pos:
            # The value at the parent node before the swap is now at path_iter in h.
            val_at_parent_before_swap = a[path_iter]
            if val_to_check >= val_at_parent_before_swap:
                possible0 = False
                break
            path_iter = (path_iter-1) // 2
        # 2. Check the termination condition at the final position.
        if possible0 and current_pos > 0:
            parent_pos = (current_pos - 1) // 2
            if val_to_check < a[parent_pos]:
                possible0 = False

        # --- Check if b_i = '1' (max-heap insertion) is possible ---
        possible1 = True
        # 1. Check swap conditions.
        path_iter = i
        while path_iter != current_pos:
            val_at_parent_before_swap = a[path_iter]
            if val_to_check <= val_at_parent_before_swap:
                possible1 = False
                break
            path_iter = (path_iter-1) // 2
        # 2. Check termination condition.
        if possible1 and current_pos > 0:
            parent_pos = (current_pos - 1) // 2
            if val_to_check > a[parent_pos]:
                possible1 = False

        # --- Decide b_i and check for impossibility ---
        if not possible0 and not possible1:
            print("Impossible")
            return

        b[i] = '0' if possible0 else '1'

        # --- Revert heap state to before v[i] was inserted ---
        # This is equivalent to sifting v[i] down from 'current_pos' to 'i'.
        if current_pos != i:
            path_from_child = []
            temp = i
            while temp > current_pos:
                path_from_child.append(temp)
                temp = (temp - 1) // 2
            path_from_child.reverse()

            prev_pos = current_pos
            for next_pos in path_from_child:
                val1 = a[prev_pos]
                val2 = a[next_pos]
                
                a[prev_pos], a[next_pos] = a[next_pos], a[prev_pos]

                val_to_current_pos[val1].remove(prev_pos)
                val_to_current_pos[val2].append(prev_pos)
                val_to_current_pos[val1].append(next_pos)
                val_to_current_pos[val2].remove(next_pos)
                val_to_current_pos[val1].sort()
                val_to_current_pos[val2].sort()
                prev_pos = next_pos
            # 在a数组和索引表中删除最后一个元素
        val_to_del = a[-1]
        a.pop()
        #val_to_del = a[current_pos]
        val_to_current_pos[val_to_del].pop()

    print(''.join(b))

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()