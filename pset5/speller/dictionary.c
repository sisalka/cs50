// Implements a dictionary's functionality

#include <stdbool.h>
#include  <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // node.word
    struct node *next;     // node.next
}
node;

// node m;
// m.word
// m.next

// node *n;
// (*n).word === n->word
// (*n).next === n->next

// Number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char word_low[LENGTH + 1];
    strcpy(word_low,word);
    for (int i =0; i<strlen(word_low); i++){
        word_low[i] = tolower(word_low[i]);
    }
    int hash_value = hash(word_low);
    // printf("CHECK: %s je v buckete %d\n", word_low, hash_value);

    node *cursor = table[hash_value];
    while (cursor != NULL){
            if (strcasecmp(word_low, cursor->word) == 0) {
                //printf("Word '%s' was found equal to word '%s' in the bucket %d\n", word_low, cursor->word, hash_value);
                return true;

            }
            else {
                //printf("Next word is %s\n", cursor->word);
                //printf("Next pointer is %p\n", cursor->next);
                cursor = cursor->next;
            }
        }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int total = 0;

    for (int i=0; i < strlen(word); i++){
        total += 31*((int)word[i]);
    }

    return total % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word_dict[LENGTH + 1];
    FILE *input = fopen(dictionary, "r");
    if(input == NULL){
        printf("Error opening file\n");
        return false;
    }

    while( fscanf(input, "%s", word_dict) != EOF ){
        node *n = malloc(sizeof(node));
        if(n == NULL){
            printf("Error! memory not allocated.");
            return false;
        }

        strcpy(n->word, word_dict);
        n->next = NULL;

        int index = hash(word_dict);
        if (table[index] == NULL){
            table[index]= n;
        }
        else {
            n->next = table[index];
            table[index] = n;
        }

    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int all_nodes = 0;
    for ( int i = 0; i< N; i++){
        int nodes = 0;
        node *pointer = table[i];
        while (pointer != NULL){
            nodes ++;
            all_nodes++;
            pointer = pointer->next;
        }
        //printf ("Bucket %d has %d nodes.\n", i, nodes);
    }

    return all_nodes;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i=0;
    int volanie_free=0;
    node *cursor = table[i];
    for (i = 0; i<N ; i++){
        if (table[i] == NULL) {
            continue;
        }
        else {
            node *temp = table[i];
            cursor = table[i];
            while (cursor != NULL){
                cursor = cursor->next;
                free(temp);
                volanie_free ++;
                temp = cursor;
            }
        }
    }
    printf("%d nodes are free now\n", volanie_free);

    return true;
}


