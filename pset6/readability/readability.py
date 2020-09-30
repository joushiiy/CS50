from cs50 import get_string

#variables
letters = 0
words = 1
sentences = 0

#input
s = get_string("Text: ")

#letter, word and sentences counter
for l in s:
    if (l.isalpha()) == True:
        letters +=1

for i in range(len(s)):
    if s[i-1] != ' ' and s[i] == ' ':
        words +=1

for i in range(len(s)):
    if s[i] == '.' or s[i] == '?' or s[i] == '!':
        sentences +=1

#Coleman-Liau index
L = ((letters/words) * 100)
S = ((sentences/words) * 100)

index = round(0.0588 * L - 0.296 * S - 15.8)

if (index < 1):
    print("Before Grade 1")
    
elif (index >= 16):
    print("Grade 16+")
    
else:
    print(f"Grade {index}")