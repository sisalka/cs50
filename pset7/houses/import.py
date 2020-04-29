import csv
from sys import argv
from cs50 import SQL

if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

db = SQL("sqlite:///students.db")
# db.execute("CREATE TABLE students_db (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")


with open(argv[1]) as f:
    students = csv.DictReader(f)
    for student in students:
        s = student['name']
        student['first'] = s.split()[0]
        if len(s.split())>2:
            student['middle'] = s.split()[1]
            student['last'] = s.split()[2]
        else:
            student['middle'] = 'NULL'
            student['last'] = s.split()[1]
        # print(student['first'],student['middle'], student['last'])
        # print(student)

        birth=int(student['birth'])
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
            student['first'], student['middle'], student['last'], student['house'], birth)