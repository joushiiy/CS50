import csv
import re
from sys import argv, exit

#input
if len(argv) !=3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

#open csv file
with open(argv[1], 'r') as datafile:
    datareader = csv.reader(datafile)
    #get nucleotide list
    row1 = next(datareader)
    row1.pop(0)

#open txt file
with open(argv[2], 'r') as txtfile:
    text = txtfile.read()

#number of consecutive nucleotides
dataseq = []

#scan text file for substrings
for i in range(len(row1)):

    x = len(row1[i])

    counter = 1
    highestcount = 0

    for j in range(len(text)):
        if text[j:(j + x)] == row1[i]:
            if text[j:(j + x)] == text[j + x:j + x + x]:
                counter+=1

            else:
                if counter > highestcount:
                    highestcount = counter
                    counter = 1
                    continue

    dataseq.append(highestcount)

#create data table
datatable = {}

#compare data
with open(argv[1], 'r') as datafile:
    #get person's database
    database = csv.reader(datafile)
    for row in database:
        datatable[row[0]] = row[1:]

del datatable['name']
datatable = dict((k, [int(s) for s in v]) for k,v in datatable.items())

for name,data in datatable.items():
    if data == dataseq:
        print(name)
        break
else:
    print("No match")