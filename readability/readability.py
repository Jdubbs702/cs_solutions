from cs50 import get_string

text = get_string("Text: ")

# each letter is an alphabetic character
letter_count = 0
# each space is a word
word_count = 1
# each . ! or ? is a sentence
sentence_count = 0

for char in text:
    ascii_val = ord(char)
    if char.isalpha():
        letter_count += 1
    if ascii_val == 32:
        word_count += 1
    if ascii_val == 46 or ascii_val == 33 or ascii_val == 63:
        sentence_count += 1

# Luhn's formula: .0588 * L - 0.296 * S - 15.8
# L = avg num of letters per 100 words
L = letter_count / word_count * 100
# S = avg num of sentences per 100 words
S = sentence_count / word_count * 100

result = .0588 * L - 0.296 * S - 15.8
grade = round(result)

if grade >= 16:
    print(f"Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
