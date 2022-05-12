from sys import argv, exit
import csv

# Checking no. of arguments
if len(argv) != 3:
    print("Usage: Incorrect number of command-line arguments!")
    exit(1)


# Opening the first file passed as command line argument in read mode
with open(argv[1], "r") as data:

    # Creating a reader using csv module
    dataReader = csv.reader(data)
    dataReader = list(dataReader)
    heads = list(dataReader)[0]

    # Opening the second file passed as command line argument in read mode
    with open(argv[2], "r") as seq:

        # Creating a reader
        seqReader = csv.reader(seq)
        sequence = list(seqReader)[0][0]

        # Initialising empty list
        strCount = []
        for k in range(1, len(heads)):
            max_c = 0
            # Finding in data
            for i in range(len(sequence) - len(heads[k])):
                c = 0
                # For getting the count
                for j in range(i, len(sequence), len(heads[k])):
                    # Matching the strings
                    if sequence[j : j + len(heads[k])] == heads[k]:
                        c = c + 1
                    else:
                        break
                max_c = max(max_c, c)
            strCount.append(max_c)

    # Matching the data
    for i in range(1, len(dataReader)):
        d = list(map(int, dataReader[i][1 :]))
        # If list matches, then print name
        if d == strCount:
            print(dataReader[i][0])
            exit(0)

# Closing the files
data.close()
seq.close()

# If no match found, print message
print("No match")
exit(1)
