#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cipher_text(string plainText, string key, int keyLen);
char codeChar(char character, string key);

int main(int argc, string argv[])
{
    // filter out invalid arguments and quit
    if (!argv[1] || argv[2])
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int keyLen = strlen(key);

    // filter invalid length and quit
    if (keyLen != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool notAlpha = 0;
    int values[keyLen + 1];
    bool duplicates = 0;

    // begin looping
    for (int i = 0; i < keyLen; i++)
    {
        // check for invalid characters
        if (!isalpha(key[i]))
        {
            notAlpha++;
        }

        // populate values array
        values[i] = tolower(key[i]);
    }

    // check for duplicate characters
    for (int i = 0; i < keyLen; i++)
    {
        int index = 1;
        for (int j = 0; j < keyLen; j++)
        {
            if (values[i] == values[i + index])
            {
                duplicates++;
            }
            else
            {
                index++;
            }
        }
    }

    // quit if there are invalid characters
    if (notAlpha)
    {
        printf("Characters must be alphabetic only.\n");
        return 1;
    }

    // quit if there are duplicates
    if (duplicates != 0)
    {
        printf("There must be only one of each letter.\n");
        return 1;
    }

    // start doing something!
    string plainText = get_string("plaintext: ");
    cipher_text(plainText, key, keyLen);
    return 0;
}

void cipher_text(string plainText, string key, int keyLen)
{
    int textLen = strlen(plainText);
    char codedText[textLen + 1];
    codedText[textLen + 1] = '\0';

    // get character encrypt and return
    for (int i = 0; i < textLen; i++)
    {
        // encrypt character
        char codedChar = codeChar(plainText[i], key);
        // add codedChar to codedText array
        strncat(codedText, &codedChar, 1);
    }
    printf("ciphertext: %s\n", codedText);
}

char codeChar(char character, string key)
{
    // mock key: ZYXWVUTSRQPONMLKJIHGFEDCBA
    char alphaU[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char alphaL[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};

    if (isupper(character))
    {
        char codedChar;
        for (int j = 0; j < 26; j++)
        {
            // when text char matches alphaU index, return indexed key
            if (character == alphaU[j])
            {
                codedChar = toupper(key[j]);
            }
        }
        return codedChar;
    }
    else if (islower(character))
    {
        char codedChar;
        for (int j = 0; j < 26; j++)
        {
            // when text char matches alphaU index, return indexed key
            if (character == alphaL[j])
            {
                codedChar = tolower(key[j]);
            }
        }
        return codedChar;
    }
    else
    {
        return character;
    }
}