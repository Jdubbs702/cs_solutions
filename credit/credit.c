#include <cs50.h>
#include <stdio.h>

long getLast(long n);
long dropLast(long n, int divider);

int main(void)
{
    // prompt for input
    const long number = get_long("Number: ");

    // check length
    long length13 = 1000000000000;
    long length14 = 10000000000000;
    long length15 = 100000000000000;
    long length16 = 1000000000000000;
    long length17 = 10000000000000000;

    if (number < length13 && number >= length17)
    {
        printf("INVALID\n");
        return 0;
    };

    long nRef = number;
    long nRef2 = number;

    // calc checksum
    long firstSum = 0;
    long secondSum = 0;

    // get last digit and drop
    long croppedNumber = dropLast(number, 10);

    do
    {
        // get last digit of cropped number
        long targetNum = getLast(croppedNumber);

        // drop last two digits
        croppedNumber = dropLast(croppedNumber, 100);

        // multiply target num by 2
        long targetNumBy2 = targetNum * 2;

        // get product's digits
        long digit1 = getLast(targetNumBy2);
        long digit2 = (targetNumBy2 - (digit1)) / 10;

        // add digit(s) to firstSum
        firstSum += (digit1 + digit2);
    } while (croppedNumber > 0);

    printf("First Sum: %li\n", firstSum);

    // get numbers from digits that weren't manipulated
    do
    {
        // get last digit in number
        long targetNum = getLast(nRef);

        // drop last two digits
        nRef = dropLast(nRef, 100);

        // add targetNum to secondSum
        secondSum += targetNum;
    } while (nRef > 0);
    printf("Second Sum: %li\n", secondSum);

    long totalSum = firstSum + secondSum;
    printf("Total Sum: %li\n", totalSum);

    long lastOfSum = getLast(totalSum);

    // get first 2 digits of number
    long firstTwo = 0;

    do
    {
        nRef2 = dropLast(nRef2, 10);

        if (nRef2 < 100)
        {
            firstTwo += nRef2;
        }
    } while (nRef2 > 99);
    printf("First Two: %li\n", firstTwo);

    // check length & starting digits for matching card type
    // Print: AMEX, MASTERCARD, VISA, or INVALID
    long firstOne = dropLast(firstTwo, 10);

    if (lastOfSum == 0)
    {
        if (
            (firstTwo == 34 || firstTwo == 37) &&
            (number >= length15 && number < length16))
        {
            printf("AMEX\n");
        }
        else if (
            (firstTwo >= 51 && firstTwo <= 55) &&
            (number >= length16 && number < length17))
        {
            printf("MASTERCARD\n");
        }
        else if (
            (firstOne == 4) && ((number >= length13 && number < length14) || (number >= length16 && number < length17)))
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

long getLast(long n)
{
    return n % 10;
};

long dropLast(long n, int divider)
{
    return (n - (getLast(n))) / divider;
};