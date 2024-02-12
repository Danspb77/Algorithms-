s=input()
a,b=map(int, input().split())

arr=[]

for i in range(len(s)):
    arr.append(s[i])

arr[a-1], arr[b-1]=arr[b-1], arr[a-1]
new_pass= "".join(arr)
print(new_pass)

