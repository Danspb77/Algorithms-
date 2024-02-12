N=int(input())
arr= list(map(int,input().split()))

unique=list(set(arr))

for el in unique:
    if arr.count(el) !=4:
        print(el)
        

