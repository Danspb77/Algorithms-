N = int(input())
arr = [int(i) for i in input().split()]
x = int(input())
    




left=[]
right=[]

for l in arr:
    if l<x:
        left.append(l)
    else:
        right.append(l)
print(f"{len(left)}\n{len(right)}")



    
        

    
