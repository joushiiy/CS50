from cs50 import get_float

#variables
quart = 25;
qcount = 0;

dime = 10;
dcount = 0;

nick = 5;
ncount = 0;

penn = 1;
pcount = 0;

#input
def input():
    while True:
        a = get_float("Change owed: ")
        if a > 0:
            break
    return a

a = input()
a = round(a * 100)

while a >= quart:
    a = a - quart
    
    qcount = qcount + 1
    
while a >= dime:
    a = a - dime
    
    dcount = dcount + 1
    
while a >= nick:
    a = a - nick
    
    ncount = ncount + 1
    
while a >= penn:
    a = a - penn
    
    pcount = pcount + 1
    
print(qcount + dcount + ncount + pcount)