#include <stdio.h>
#include <cs50.h>

int main(void)

{
    //input//
    string name = get_string("What's your name?\n");
    
    //output//
    printf("Hello, %s\nWhat's on today's menu?\n", name);

}