N = int(input())
mas = [int(i) for i in input().split()]

def quick_sort(mas):
    if len(mas) == 0:
        return []
    
    wall = 0
    p = mas[-1]

    for cur in range(len(mas)-2):
        if mas[cur] < mas[p]: 
            mas[wall], mas[cur] = mas[cur], mas[wall]
            wall += 1
    
    mas[wall], mas[p] = mas[p], mas[wall]
    return mas[:wall+1] + quick_sort[wall+1:]