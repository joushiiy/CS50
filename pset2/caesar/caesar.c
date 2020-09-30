#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//funtion declaration//
bool is_digit(string s);

int main(int argc, string argv[])
{
    //Input checker//
    if (argc == 2 && is_digit(argv[1]) && atoi(argv[1]) > 0)
    {
        //get string//
        int key = atoi(argv[1]);
        string text = get_string("plaintext: ");

        //output phrase//
        printf("ciphertext: ");

        for (int i = 0; i < strlen(text); i++)
        {
            //check for alphabet//
            char c = text[i];
            if (isalpha(c))
            {
                if (islower(c))
                {
                    char lower = (c - 'a' + key) % 26 + 'a';
                    printf("%c", lower);
                }

                else if (isupper(c))
                {
                    char upper = (c - 'A' + key) % 26 + 'A';
                    printf("%c", upper);
                }
            }
            //else if not an alphabet keep it same//
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");

    }
    //if not a a valid input print this//
    else
    {
        printf("Usage ./casesar key\n");
        return 1;
    }
    return 0;
}

//is a digit function//
bool is_digit(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if there is an alpha the code is invalid//
        if (isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}