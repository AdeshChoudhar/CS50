#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main()
{
    // Taking Number
    long int N = get_long("Number: "), n;
    int s = 0, rem, i;

    // Creating dummy variable for process
    n = N;

    // Algorithm Starts

    // Sum accordingly
    for (i = 0; n > 0; i++)
    {
        // Taking last digit of the number
        rem = n % 10;
        // Removing last digit of the number
        n = n / 10;

        // Conditions of sum
        if (i % 2 == 0)
        {
            s = s + rem;
        }
        else
        {
            rem = rem * 2;
            s = s + rem / 10 + rem % 10;
        }
    }

    // Verifying checksum
    if (s % 10 == 0)
    {
        // m2 is first two digits of number
        int m2 = N / pow(10, i - 2);
        // m1 is first digit of number
        int m1 = N / pow(10, i - 1);

        // Verifying card descriptions
        if (i == 15 && ((m2 == 34) || (m2 == 37)))
        {
            printf("AMEX\n");
        }
        else if (i == 16 && (m2 == 51 || m2 == 52 || m2 == 53 || m2 == 54 || m2 == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((i == 13 || i == 16) && (m1 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}