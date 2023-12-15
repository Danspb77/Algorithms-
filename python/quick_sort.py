arr=[]
import random

# s -smaller
# b -bigger
def quicksort(nums):
   if len(nums) <= 1:
       return nums
   else:
       q = random.choice(nums)
   s_nums = [n for n in nums if n < q]
 
   e_nums = [q] * nums.count(q)
   b_nums = [n for n in nums if n > q]
   return quicksort(s_nums) + e_nums + quicksort(b_nums)
print(quicksort(arr))