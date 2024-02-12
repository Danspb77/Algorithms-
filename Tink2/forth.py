N=int(input())
steps=input()

def opti(N,steps):
    places=set()

    x,y=0,0

    places.add((x,y))

    for move in steps:
        if move == 'L':
            x -= 1
        elif move == 'R':
            x += 1
        elif move == 'U':
            y += 1
        elif move == 'D':
            y -= 1 

        if (x,y) in places:
            return "YES"
        
        places.add((x,y))

    return"NO"

print(opti(N,steps))

