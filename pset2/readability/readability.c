#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    //varaibles//
    int letter = 0;
    int words = 1;
    int sentences = 0;

    //input//
    string sentence = get_string("Text: ");


    for (int i = 0; i < strlen(sentence); i++)
    {
        //letter counter//
        if (isalpha(sentence[i]))
        {
            letter++;
        }

        //word counter//
        if (sentence[i - 1] != ' ' && sentence[i] == ' ')
        {
            words++;
        }

        //sentence counter
        if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!')
        {
            sentences++;
        }
    }
    //Coleman-Liau index//
    float L = (((float)letter / words) * 100);
    float S = (((float)sentences / words) * 100);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //output//
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}