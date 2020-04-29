from cs50 import get_string
import math

text = get_string("Text: ")

def count_letters(text):
    n = 0
    for i in text:
        if i.isalpha():
            n += 1
    # print(f"{n} letters")
    return n


def count_words(text):
    n=1
    for i in text:
        if i.isspace():
            n += 1
    # print(f"{n} words")
    return n

def count_sent(text):
    n= text.count('.') + text.count('!')+ text.count('?')
    # print(f"{n} sentences")
    return n

def grade(text):
    L = float((count_letters(text)/count_words(text))*100)
    S = float((count_sent(text)/count_words(text))*100)

    # print(f"{L} L")
    # print(f"{S} S")
    # print(f"{0.0588*L-0.296*S-15.8} Grade")
    # print(f"{round(0.0588*L-0.296*S-15.8)} math.floor Grade")

    return round(0.0588*L-0.296*S-15.8)

grade(text)

if grade(text)<1:
    print("Grade before 1")
elif grade(text) >16:
    print("Grade 16+")
else:
    print(f"Grade {grade(text)}")