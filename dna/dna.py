from sys import argv
import csv


# with open(argv[1]) as f:
#     names = csv.reader(f)
    # for line in names:
    #     print(type(line))
    #     print(line)

f = open(argv[2], "r")
# print(f.readline())
seq = f.read()
# print (len(seq))


str_large =["AGATC", "TTTTTTCT","AATG","TCTAG","GATA","TATC","GAAA","TCTG"]

str_dict= {}
for str in str_large:
    founds = []

    # print(str)
    i = 0
    while i < len(seq)-len(str):
    #for i in range(len(seq)-len(str)):
        j=i+len(str)
        cons_found = 0
        # print(seq[i:j])
        if (seq[i:j] != str):
            i += 1
        else:
            while (seq[i:j] == str):
                i += len(str)
                j += len(str)
                cons_found +=1
                # input("while")
                founds.append(cons_found)
                # print("Found ", str, "at pos ", i)
                # print(founds)
            # input("for")

    str_dict[str]=max(founds)
    # print(str_dict)

with open(argv[1]) as f:
    next(f)
    names = csv.reader(f)
    for line in names:
        # print("dict: ", list(str_dict.values()))
        # print("line: ", line[1:])
        line_int = [int(a) for a in line[1:]]
        # print("line_int: ", line_int)
        if (list(str_dict.values()) == line_int):
            print(line[0])

