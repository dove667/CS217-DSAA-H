import sys
def reverse_ops(n, arr, val, heap_size, is_max):
    trace = []
    index = arr.index(val)
    i = heap_size - 1
    while arr[i] != val:
        if is_max and arr[i] < val or not is_max and arr[i] > val:
            trace.append(i)
            i = (i - 1) // 2
        else: 
            return -1
    for j in reversed(trace):
        arr[index], arr[j] = arr[j], arr[index]
        index = j

def main(n, insert_order, final):
    bin = []
    heap_size = n
    last = final[heap_size-1]
    for val in reversed(insert_order):
        if last != val:
            if last < val:
                bin.append(1)
                is_max = True
            elif last > val:
                bin.append(0)
                is_max = False
            state = reverse_ops(heap_size, final, val, heap_size, is_max)
            if state == -1:
                return -1
        else:
            bin.append(0)
        heap_size -= 1
    bin.reverse()
    return bin

if __name__ == '__main__':
    
    T = int(sys.stdin.readline().strip())
    for i in range(T):
        n = int(sys.stdin.readline().strip())
        insert_order = [int(x) for x in sys.stdin.readline().strip().split()]
        final = [int(x) for x in sys.stdin.readline().strip().split()]
        bin = main(n, insert_order, final)
        if bin == -1:
            sys.stdout.write("Impossible\n")
        else:
            sys.stdout.write(" ".join(map(str, bin)) + "\n")