#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char *u_str = (unsigned char *)str;

  while ((c = *u_str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  if (capacity < 1)
  {
    return NULL;
  }

  BasicHashTable *ht = malloc(sizeof(BasicHashTable *));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // Note, since we are only writing a resize function in hashtables.c
  //    I'm NOT going to conditionally check if the ht is full and if so resize it.

  // hash the key to get an array index
  unsigned int index = hash(key, ht->capacity);

  // check if the bucket at that index is occupied
  Pair *curr_pair = ht->storage[index];
  Pair *next_pair = NULL;

  // if it is occupied, walk through the Pair's to see if you find
  // check for a pair with the same key using strcmp.
  while (curr_pair != NULL && strcmp(curr_pair->key, key) != 0)
  {
    next_pair = curr_pair;
    curr_pair = next_pair;
  }

  // If you do, overwrite that value
  if (curr_pair != NULL)
  {
    curr_pair->value = value;
  }
  // If not, create a new pair and add it to the LinkedList
  else
  {
    // if it's not occupied, add a new Pair to the bucket
    Pair *new_pair = create_pair(key, value);
    ht->storage[index] = new_pair;
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  // hash the key to get an array index
  unsigned int index = hash(key, ht->capacity);
  // if key_found ? return value : return NULL
  return ht->storage[index] != NULL ? ht->storage[index]->value : NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));  // Here today...
  printf("%s", hash_table_retrieve(ht, "linee")); // (null)

  // hash_table_remove(ht, "line");

  // if (hash_table_retrieve(ht, "line") == NULL)
  // {
  //   printf("...gone tomorrow. (success)\n");
  // }
  // else
  // {
  //   fprintf(stderr, "ERROR: STILL HERE\n");
  // }

  destroy_hash_table(ht);

  return 0;
}
#endif
