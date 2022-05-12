#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define N 10000

// Defines struct for a node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *table[N];

// From Github by 'choaimeloo'
// Hash function posted on Reddit by 'delipity'
// The word you want to hash is contained within new node, arrow, word.
// Hashing that will give you the index. Then you insert word into linked list.
int hash_index(char *hash_this)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(hash_this); i < n; i++)
    {
        hash = (hash << 2) ^ hash_this[i];
    }
    return hash % N;
}

// For counting the total words
int word_count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Scan file till EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory a node for each new word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, word);

        int h = hash_index(n->word);

        node *head = table[h];

        // Inserts new nodes at beginning of lists
        if (head == NULL)
        {
            table[h] = n;
            word_count++;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
            word_count++;
        }
    }
    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Creates copy of word on which hash function can be performed
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[n] = '\0';
    int h = hash_index(word_copy);

    node *cursor = table[h];

    // While cursor does not point to NULL, search dictionary for word.
    while (cursor != NULL)
    {
        // If strcasecmp returns true, then word has been found
        if (strcasecmp(cursor->word, word_copy) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Returns number of words
unsigned int size(void)
{
    return word_count;
}

// Unloading dictionary from memory
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        if (head == NULL)
        {
            continue;
        }

        if (head->next == NULL)
        {
            continue;
        }

        node *cursor = head->next;

        while(cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

    }
    return true;
}