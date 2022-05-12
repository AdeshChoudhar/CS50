#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{
    // Taking a text as input
    string text = get_string("Text: ");
    int letters = 0, words = 1, sentences = 0, index;
    float L, S;

    // Calculating letters, words and sentences
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calculating required parameters
    L = ((float)letters / (float)words) * 100;
    S = ((float)sentences / (float)words) * 100;

    // Using Coleman-Liau index formula
    index = round(0.0588 * L - 0.296 * S - 15.8);

    // Printing according to value of index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

}