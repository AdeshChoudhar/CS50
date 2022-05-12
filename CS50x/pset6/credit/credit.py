# Taking and validating credit card number as input
while True:
    try:
        number = list(map(int, input("Number : ")))
        break
    except:
        pass

# Conditionally calculating two parts of checksum
checka = checkb = 0
for i in range(len(number)):
    # If length of number is even, for the first part of checksum, start from 0th index
    if len(number) % 2 == 0:
        if i % 2 == 0:
            checka = checka + (2 * number[i]) // 10 + (2 * number[i]) % 10
        else:
            checkb = checkb + number[i]
    # If length of number is odd, for the first part of checksum, start from 1st index
    else:
        if i % 2 == 0:
            checkb = checkb + number[i]
        else:
            checka = checka + (2 * number[i]) // 10 + (2 * number[i]) % 10

# Checksum
checksum = checka + checkb

# Validation of card number
if checksum % 10 == 0:
    # Validation of different card types
    if (len(number) == 15 and (number[0] == 3 and number[1] in [4, 7])):
        print("AMEX")
    elif (len(number) == 16 and (number[0] == 5 and number[1] in [1, 2, 3, 4, 5])):
        print("MASTERCARD")
    elif (len(number) in [13, 16] and number[0] == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
