#include <cs50.h>
#include <stdio.h>

int main()
{
    int h;

    //Taking input and verifying
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    //Building Pyramids
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < (h + 2 + i + 1); j++)
        {
            //Printing required spaces first
            if ((j < h - i - 1) || j == h || j == h + 1)
            {
                printf(" ");
            }
            //Then printing i hashes
            else
            {
                printf("#");
            }
        }
        //Printing new line
        printf("\n");
    }

}