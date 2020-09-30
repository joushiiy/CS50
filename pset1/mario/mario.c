#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Please select height\n");
    }

    // Range between 1 to 8 //
    while (h < 1 || h > 8);

    //Create height of sqaure block//
    for (int i = 0; i < h; i++)
    {
        //Create width of square block//
        for (int j = 0; j < h; j++)
        {
            //Create blank space of square block//
            if (j + i < h - 1)
            {
                printf(" ");
            }
            
            else
            {
                printf("#");
            }
        }
        
        printf("\n");
    }
}