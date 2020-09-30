import csv
from sys import argv, exit
from cs50 import SQL

#check command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py [house name]")
    exit(1)

db = SQL("sqlite:///students.db")
nameroster = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[-1])

for row in nameroster:
    if row['middle'] != None:
        row['middle'] = row['middle'] + ' '
    else:
        row['middle'] = ''
    print(row['first'] + ' ' + row['middle'] + row['last'] + ', born ' + str(row['birth']))