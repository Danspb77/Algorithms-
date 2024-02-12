
# a - коэффицент перед х**2



print("Введите коэффициенты а, b, c")



a,b,c= map(float,input().split())



if a==0:
    if b==0:
        if c==0:
            print("X- любое число")
        else:
            print("Решений нет")    
    else:
        ans=-c/b
        print(ans)


else:
    D=b**2-4*a*c
    if D>0:
        ans1=(-b+D**0.5)/(2*a)
        ans2=(-b-D**0.5)/(2*a)
        print (ans1, ans2)
    else:
        if D==0:
            ans=-b/(2*a)
            print(ans)
        else:
            print("Решений нет")    