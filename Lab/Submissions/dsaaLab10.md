# Exercise Sheet 10

**Handout:** November 11th — **Deadline:** November 25th before 4pm

---

### **Question 10.1** (0.5 Marks)

Insert the keys 8, 2, 1, 3, 6, 10, 9 in this order into an empty AVL tree. Draw the tree constructed after each insertion and after each (double-)rotation (cf. the example in the lecture notes). Write down the balance degree for each node next to the node as shown in the lecture notes.

```
                    8(1)               8(2)          2(0)
8(0) --insert 2-->  /   --insert 1-->   /   --R-->  /    \          
                  2(0)                2(1)         1(0)  8(0)
                                      /
                                    1(0)   


                 2(-1)                   2(-2)                
                 /   \                   /   \              
--insert 3--> 1(0)  8(1) --insert 6--> 1(0)  8(2)   
                     /                       /           
                   3(0)                    3(-1)         
                                               \
                                               6(0)
                                    
          2(-1)                     2(-2)
          /   \                     /   \
--LR--> 1(0)  6(0) --insert 10--> 1(0)  6(-1)       
              /  \                      /  \
            3(0) 8(0)                3(0)  8(-1)
                                              \
                                              10(0)

         6(0)                      6(-1)
        /    \                    /    \ 
--R--> 2(0)  8(-1) --insert 9--> 2(0)  8(-2)
      /   \      \              /   \      \
    1(0)  3(0)   10(0)        1(0)  3(0)   10(1)
                                           /
                                         9(0) 
            6(0)
          /      \ 
--RL--> 2(0)      9(0)
       /   \     /    \
     1(0) 3(0)  8(0) 10(0)                                 
```


### **Question 10.2** (0.5 marks)

Say the minimum number of nodes that an AVL tree of height h = 10 must contain.

#### Answer:

Due to the theorem discussed in the lecture, we know that the minimum number of nodes `A(h)` in an AVL tree of height `h` satisfies the recurrence relation:

$$A(h) = A(h-1) + A(h-2) + 1$$

with base cases:
- `A(0) = 1` (an AVL tree of height 0 has 1 node)
- `A(1) = 2` (an AVL tree of height 1 has 2 nodes)
Calculating the values up to `h = 10`:
- `A(2) = A(1) + A(0) + 1 = 2 + 1 + 1 = 4`
- `A(3) = A(2) + A(1) + 1 = 4 + 2 + 1 = 7`
- `A(4) = A(3) + A(2) + 1 = 7 + 4 + 1 = 12`
- `A(5) = A(4) + A(3) + 1 = 12 + 7 + 1 = 20`
- `A(6) = A(5) + A(4) + 1 = 20 + 12 + 1 = 33`
- `A(7) = A(6) + A(5) + 1 = 33 + 20 + 1 = 54`
- `A(8) = A(7) + A(6) + 1 = 54 + 33 + 1 = 88`
- `A(9) = A(8) + A(7) + 1 = 88 + 54 + 1 = 143`
- `A(10) = A(9) + A(8) + 1 = 143 + 88 + 1 = 232`

Therefore, an AVL tree of height h = 10 must contain at least 232 nodes.