from sys import argv
from cs50 import SQL

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

db = SQL("sqlite:///students.db")

house_input = argv[1]

people = db.execute("select first, middle, last, birth from students where house = ? group by first order by last", house_input)

# print(people[0]['first'])

for i in range(len(people)):
    first = people[i]['first']
    middle = people[i]['middle']
    last = people[i]['last']
    birth = people[i]['birth']
    if middle == "NULL":
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")