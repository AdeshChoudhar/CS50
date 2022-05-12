#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main()
{
    float dollars;
    int cents, count = 0;

    //Taking input in dollars
    dollars = get_float("Change owed: ");
    //Dollars to cents
    cents = round(dollars * 100);

    //Counting coins till cents becomes 0
    while (cents != 0)
    {
        if (cents >= 25)
        {
            cents = cents - 25;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
        }
        else
        {
            cents = cents - 1;
        }

        //Incrementing counter of coins each time loop runs
        count++;
    }

    //Printing count of coins
    printf("%d", count);
}
