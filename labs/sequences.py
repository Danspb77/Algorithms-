# count = 0
# p = 1
# for i in range(1, 11):
#     x = int(input())
#     if x > 0:
#         p = p * x
#         count = count + 1
# if count > 0:
#     print(p)
#     print(count)
# else:
#     print('NO')

# mx = -10000000000000000
# s = 0
# flag=True
# for i in range(10):
#     x = int(input())
#     if x < 0:
#         flag=False
#         s += x
#         if x > mx:
#             mx = x
# if  flag==True:
#     print("NO")
# else:
#     print(s)
#     print(mx)
    
# n = int(input())
# max_digit = 0
# flag=True
# while n > 0:
#     digit = n % 10
#     if digit % 3 == 0:
#         flag=False
#         if digit > max_digit:
#             max_digit =digit 
#     n = n // 10
# if flag:
#     print('NO')
# else:
#     print(max_digit)

# n=int(input())

# for i in range(1,n+1):
#     print(f"{i} {i} {i} {i} {i} {i}")

# def hex_string_to_RGB(hex_string): 
#     hex_string=hex_string[1:]
    
#     red=int(hex_string[:2],16)
#     green=int(hex_string[2:4],16)
#     blue=int(hex_string[4:6],16)
#     return {
#         "r":red,
#         "g":green,
#         "b":blue
#     }

# print(hex_string_to_RGB("#FF9933"))


def gen_dict(Name, Age):
    dict={}
    for i in range(len(Name)):
        dict[Name[i]]=Age[i]
    return dict
