// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// follow loaded state and track number of words (in load() function)
bool loaded = false;
unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    int hash_value = hash(word);

    // access linked list at the index in the hash table
    node *cursor = table[hash_value];
    int difference;
    // traverse linked list, looking for the word (strcasecmp)
    while (cursor != NULL)
    {
        difference = strcasecmp(cursor->word, word);
        if (difference == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // A Good Hash Function Should:
    //  use only the data being hashed; use all the data being hashed;
    //  be deterministic; uniformly distribute data; generate very different hash codes for very similar data

    // take alphabetic word as input (possibly with apostrophes),
    // output numerical index between 0 and N-1, inclusive
    int index = 0;
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        char cap_letter = toupper(word[i]);
        // printf("%c", cap_letter);
        sum += cap_letter;
    }
    int hash = sum % 1000;
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // null out table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open dictionary file
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    // create buffer to read into
    char word[LENGTH];

    // read strings one at a time
    while (fscanf(d, "%s", word) != EOF)
    {
        // create and populate new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        // hash word to get hash value
        int _hash = hash(word);
        // insert node into hash table at the hash value location

        if (table[_hash] == NULL)
        {
            n->next = NULL;
            table[_hash] = n;
        }
        else
        {
            n->next = table[_hash];
            table[_hash] = n;
        }
        count++;
    }

    fclose(d);
    loaded = true;

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // for each pointer in array(head of linked list)
    for (int i = 0; i < N; i++)
    {
        // create temp and cursor variables/set both pointing to head of linked list
        node *temp = table[i];
        node *cursor = table[i];
        // repeat until reached NULL node:
        while (cursor != NULL)
        {
            // move cursor to next item;
            cursor = cursor->next;
            // free node
            free(temp);
            // set temp as cursor
            temp = cursor;
        }
    }
    return true;
}