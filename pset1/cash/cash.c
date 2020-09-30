#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //variables//
    float quart = 25;
    int qcount = 0;

    float dime = 10;
    int dcount = 0;

    float nick = 5;
    int ncount = 0;

    float penn = 1;
    int pcount = 0;


    //negative value checker//
    float change;
    do
    {
        //user input//
        change = get_float("Change owed:\n");
    }
    while (change < 0);


    change = round(change * 100);


    //coin slotter//
    while (round(change) >= quart)
    {
        //Minus away quarters//
        change = change - quart;

        qcount++;
    }

    while (round(change) >= dime)
    {
        //Minus away dime//
        change = change - dime;

        dcount++;
    }

    while (round(change) >= nick)
    {
        //Minus away nickles//
        change = change - nick;

        ncount++;
    }

    while (round(change) >= penn && change != 0)
    {
        //Minus away pennies//
        change = change - penn;

        pcount++;
    }

    //coin counter//
    int coin = (qcount + dcount + ncount + round(pcount));
    printf("%i\n", coin);

}