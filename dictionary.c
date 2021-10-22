// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Dictionary word counter
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Create a copy of the word
    int n = strlen(word);
    char w_copy[LENGTH + 1];
    // All characters must be lower case for hash (since dictionary words are lowercase)
    for (int i = 0; i < n; i++)
    {
        w_copy[i] = tolower(word[i]);
    }
    // Add null terminator to end string
    w_copy[n] = '\0';

    // Initialize index for hashed word
    int h_index= hash(w_copy);

    // Set cursor at the start of the hash table at the correct index
    node *cursor = table[h_index];

    // If the word exists, using srtcasecmp, return true:
    // Check for word in linked list inside the hash table index while cursor does not point to NULL
    while (cursor != NULL)
    {
        // If strcasecmp returns true the word exists
        if (strcasecmp(cursor->word, w_copy) == 0)
        {
            return true;
        }
        // Else continue searching
        else
        {
            cursor = cursor->next;
        }
    }
    // Cursor has reached end of list and word was not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //hash function posted on reddit by delipity
    unsigned int hash = 0;
    int HASHTABLE_SIZE = N;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % HASHTABLE_SIZE;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *d_file = fopen(dictionary, "r");
    if (d_file == NULL)
    {
        return false;
    }

    char d_word[LENGTH + 1];

    while(fscanf(d_file, "%s", d_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        n->next = NULL;

        //copy word to new node
        strcpy(n->word, d_word);

        //find hash index
        int ind = hash(n->word);

        //add new node to hash table at the index
        n->next = table[ind];
        table[ind] = n;
        word_count++;
    }

    fclose(d_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp = NULL;
    node *cursor = NULL;

    for(int i = 0; i < N; i++)
    {
        cursor = table[i];
        while(cursor != NULL)
        {
        temp = cursor;
        cursor = cursor->next;
        free(temp);
        }
    }

    return true;
}
