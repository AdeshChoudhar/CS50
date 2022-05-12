# Taking height of pyramid until valid number is entered
while(True):
    # Validating input
    try:
        n = int(input("Height: "))
        if 0 < n < 9:
            break
    except:
        continue

# Buiding pyramid
for i in range(n):
    print(" " * (n - 1 - i) + "#" * (i + 1))
