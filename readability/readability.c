#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text, int length);
int count_words(string text, int length);
int count_sentences(string text, int length);

int main(void)
{
    string text = get_string("Text: ");
    int textLen = strlen(text);
    float grade = -1;

    int letters = count_letters(text, textLen);
    int words = count_words(text, textLen);
    int sentences = count_sentences(text, textLen);

    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;

    grade = 0.0588 * L - 0.296 * S - 15.8;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(grade));
    }
}

int count_letters(string text, int length)
{
    int numOfLetters = 0;
    for (int i = 0; i < length; i++)
    {
        char textChar = text[i];
        if (isupper(textChar) || islower(textChar))
        {
            numOfLetters++;
        }
    }
    return numOfLetters;
}

// attempt a solution that will tolerate multiple spaces between words or indeed, no words!
int count_words(string text, int length)
{
    // user enters nothing
    int numOfSpaces = 0;
    // user enters string without spaces
    if (length > 0)
    {
        numOfSpaces = 1;
    }
    // count spaces entered
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 32 && text[i + 1] == 32)
        {
            numOfSpaces += 0;
        }
        else if (text[i] == 32)
        {
            numOfSpaces++;
        }
    }
    return numOfSpaces;
}

int count_sentences(string text, int length)
{
    int numOfPeriods = 0;
    int numOfExPoints = 0;
    int numOfQMarks = 0;

    for (int i = 0; i < length; i++)
    {
        char textChar = text[i];
        if (textChar == 46)
        {
            numOfPeriods++;
        }
        if (textChar == 33)
        {
            numOfExPoints++;
        }
        if (textChar == 63)
        {
            numOfQMarks++;
        }
    }
    int numOfSentences = numOfPeriods + numOfExPoints + numOfQMarks;
    return numOfSentences;
}