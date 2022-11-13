#include <cs50.h>
#include <stdio.h>

void printHash(int n);
void printSpace(int n);

int main(void)
{
    // get user input and re-prompt until numbers are within 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    // for each row
    int hashes = 1;
    int spaces = height - 1;
    for (int i = 0; i < height; i++)
    {
        // print # of spaces before the left pyramid
        printSpace(spaces);

        // print # of hashes representing the left pyramid
        printHash(hashes);

        // print 2 spaces
        printf("  ");

        // print # of hashes representing right pyramid
        printHash(hashes);
        hashes++;
        spaces--;

        printf("\n");
    }
}

// function for number of times to print #
void printHash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
};

// function for number of times to print blank space
void printSpace(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
};