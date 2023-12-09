def addTwoNumbers( l1, l2):
    s1=''
    s2=''
    for i in range(len(l1)-1,-1,-1):
        
        s1+=str(l1[i])
    for j in range(len(l2)-1,-1,-1):
        s2+=str(l2[j])

    ans =int(s1)+int(s2)
    ans=str(ans)
    m=[]
    for k in ans:
        m.append(int(k))
    m.reverse()
    return m
print(addTwoNumbers([2,4,3],[5,6,4]))


