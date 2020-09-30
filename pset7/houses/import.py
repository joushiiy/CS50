import csv
from sys import argv, exit
from cs50 import SQL


#import csv
#check command-line arguments
if len(argv) !=2:
    print("Usage: python import.py characters.csv")
    exit(1)

db = SQL("sqlite:///students.db")

#open CSV file given command-line argument
with open(argv[1], "r") as charlist:
    reader = csv.DictReader(charlist)

    #for each row, parse name
    for row in reader:

        #split name
        x = row['name'].split()
        #if there is middle name
        if len(x) == 3:
            first = x[0]
            middle = x[1]
            last = x[2]
        #if no middle name
        elif len(x) == 2:
            first = x[0]
            middle = None
            last = x[1]
        house = row['house']
        birth = row['birth']

        #insert each student into the students table of students.db
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last ,house, birth)