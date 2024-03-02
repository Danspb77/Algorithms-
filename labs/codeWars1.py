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
    if len(isbn) == 10:
        for i, char in enumerate(isbn):

            if char in "1234567890X":

                if char == "X":
                    if i == len(isbn)-1:
                        implement = (i+1) * 10
                    else:
                        return False

                else:
                    implement = (i+1) * int(char)
                summa += implement
            else:
                return False
        expr = summa % 11
        if expr == 0:
            return True
        return False
    else:
        return False


print(valid_ISBN10("47008252"))


# def is_solved(board):
#     for row in board:
#         if sum(row) == 3 and ('0' and '2') not in row:
#             return ("1 if X won,")

#         elif sum(row) == 6 and ('0' and '1') not in row:
#             return ("2 if O won,")
        
#         else:
            


# # not yet finished
# board = [[0, 0, 1],
#          [0, 1, 2],
#          [2, 1, 0]]

# # winning row
# boardX = [[1, 1, 1],
#           [0, 2, 2],
#           [0, 0, 0]]

# boardY = [[0, 1, 1],
#           [2, 2, 2],
#           [0, 0, 0]]

# print(is_solved(boardY))

import psycopg2 as ps

conn = ps.connect(
    dbname='laba4',
    user='postgres',
    password='first@27',
    host='localhost'
)

cur = conn.cursor()

sql = "SELECT * FROM user1_schema.cars WHERE brand = %s"  # Adjust your SQL query as needed

brand_value = 'BMW'
cur.execute(sql, (brand_value,))  # Pass parameters as a tuple

rows = cur.fetchall()
for row in rows:
    print(row)

cur.close()
conn.close()
