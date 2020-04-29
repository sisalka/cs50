from cs50 import get_int
import math

ccn = get_int("Number: ")

def cifra(ccn,cifraord):

    n = math.floor(ccn/(10**cifraord))
    n = n%10
    return n

def isvalid(ccn):
    sum = 0
    for i in [1,3,5,7,9,11,13,15]:
        n = cifra(ccn,i)
        n = n*2
        if n > 9:
            n_prva = 1
            n_druha = n%10
            n = n_prva + n_druha
        sum += n

    for i in [0,2,4,6,8,10,12,14]:
        n = cifra(ccn,i)
        sum += n

    print(f"Sucet je {sum}")

    if sum%10 == 0:
        return True

def typecard(ccn):
    if isvalid(ccn) == True:
        if len(str(ccn)) == 15:
            n = cifra(ccn,14)
            m = cifra(ccn,13)
        else:
            n = cifra(ccn,15)
            m = cifra(ccn,14)
            k = math.floor(ccn/(10**10))

        if n == 4:
            print("VISA")
        elif n == 3 and (m == 4 or m == 7):
            print("AMEX")
        elif (n == 5 and m in [1,2,3,4,5]) or k in range(222100,272099):
            print("Master Card")
        else:
            print("INVALID")
    else:
        print("INVALID")

typecard(ccn)