#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Checking only one argument is passed
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    // Checking length of argument is 26 or not
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];

    // Checking each characters is alphabet and occurs only once
    for (int i = 0; i < 25; i++)
    {
        if (! isalpha(key[i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (key[j] == key[i])
            {
                printf("Usage: %s key\n", argv[0]);
                return 1;
            }
        }
    }

    // Getting plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Printing each characters one by one by given key
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (islower(plaintext[i]))
        {
            printf("%c", tolower(key[plaintext[i] - 97]));
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key[plaintext[i] - 65]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    // Printing new line
    printf("\n");

    return 0;
}