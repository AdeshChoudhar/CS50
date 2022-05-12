while(True):
    # Inputting and validating amount of cash owned
    try:
        dollars = float(input("Change owed: "))
        if dollars >= 0:
            break
    except:
        pass

# Dollars to cents
cents = int(dollars * 100)

coins = 0

# Counting coins
for i in [25, 10, 5, 1]:
    coins = coins + cents // i
    cents = cents % i

print(coins)
