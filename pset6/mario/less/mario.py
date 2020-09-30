from cs50 import get_int


#input and checker
def checker():
    #break loop
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

h = checker()

for i in range(h):
    for j in range(h):
        if i + j < h -1:
            print(" ", end="")

        else :
            print("#", end="")
    print()