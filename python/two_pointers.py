def two_sum(numbers, target):
    for i in range(len(numbers)-1):
        for j in (i+1, len(numbers)-1):
            if numbers[i]+numbers[j]==target:
                return numbers[i],numbers[j]

print(two_sum([1234,5678,9012],1))

def two_sum2(numbers, target):
    arr=[]
    for i in (numbers):
        complement=target-i
        arr.append(complement)
        if complement in numbers:
            return True

    # for j in arr:
    #     if j in numbers:
    #         return True
        
print(two_sum2([0,9,1],17))

