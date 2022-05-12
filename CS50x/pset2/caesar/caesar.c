#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Checking argument passed is non-negative and only one argument is passed
    if (argv[1] < 0 || argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Checking all the characters in the given argument are digits
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (! isdigit(argv[1][i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }

    // Typecasting string to int
    int key = atoi(argv[1]);

    // Inputting plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Converting to ciphertext using given formula and modifications
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (islower(plaintext[i]))
        {
            printf("%c", 'a' + (plaintext[i] - 'a' + key) % 26);
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", 'A' + (plaintext[i] - 'A' + key) % 26);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    // Adding new line
    printf("\n");
}
