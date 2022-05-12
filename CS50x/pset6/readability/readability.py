# Inputting text
text = input("Text: ")

# Initialising count of number of letters, words, and sentences to be 0
l = w = s = 0

# Iterating through text character by character
for i in text:
    # If character is a alphabet, increment count of letters by 1
    if i.isalpha():
        l = l + 1
    # If character is a space, increment count of words by 1
    elif i == " ":
        w = w + 1
    # If character is a period or exclamation or question mark, increment count of sentences by 1
    elif i in [".", "!", "?"]:
        s = s + 1
# Increment once for the first word of text
w = w + 1

# L is the average number of letters per 100 words in the text
L = (l / w) * 100
# S is the average number of sentences per 100 words in the text.
S = (s / w) * 100

# Coleman-Liau index formula
index = round(0.0588 * L - 0.296 * S - 15.8)

# Deciding grade-level for reading and printing it
if (index >= 16):
    print("Grade 16+")
elif (index > 0):
    print("Grade", index)
else:
    print("Before Grade 1")
