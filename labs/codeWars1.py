def two_sum(numbers, target):
    for i in range(len(numbers) - 1):
        for j in range(i + 1, len(numbers)):
            summa = numbers[i] + numbers[j]
            if summa == target:
                return i, j


print(two_sum([1234, 5678, 9012], 14690))


def two_sum_hash(numbers, target):
    num_indices = {}

    for i, num in enumerate(numbers):
        complement = target-num
        if complement in num_indices:
            return i, num_indices[complement]

        num_indices[num] = i


print(two_sum_hash([1234, 5678, 9012], 14690))


def valid_ISBN10(isbn):
    summa = 0
    for i, char in enumerate(isbn):
        if i == len(isbn)-1 and isbn[i] == "X":
            implement = (i+1) * 10
        else:
            implement = (i+1) * int(char)
        summa += implement

    expr = summa % 11
    if expr == 0:
        return True
    return False


print(valid_ISBN10("048665088X"))
