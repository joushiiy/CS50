// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

int wordcounter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 73;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor-> word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number //
// djb2 //
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c = 0;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary file//
    FILE *pointer = fopen(dictionary, "r");
    if (pointer == NULL)
    {
        return 1;
    }

    char word[LENGTH + 1];

    //read strings from file//
    while (fscanf(pointer, "%s", word) != EOF)
    {
        //create a new node//
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return 1;
        }

        strcpy(tmp->word, word);

        //hash word/call hash function//
        int index = hash(word);

        //insert node into hash table//
        if (table[index] == NULL)
        {
            tmp->next = NULL;
            table[index] = tmp;
        }

        else
        {
            tmp->next = table[index];
            table[index] = tmp;
        }

        wordcounter++;
        
    }

    fclose(pointer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}