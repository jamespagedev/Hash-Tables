#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the
  next `LinkedPair` in the list of `LinkedPair` nodes.
 */
typedef struct LinkedPair
{
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable
{
  int capacity;
  int count;
  LinkedPair **storage;
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = (LinkedPair *)malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
    pair = NULL;
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
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

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  if (capacity < 1)
  {
    return NULL;
  }

  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->count = 0;
  ht->storage = (LinkedPair **)calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // hash the key to get an array index
  unsigned int index = hash(key, ht->capacity);

  // check if the element in the array index is null
  //    if so, create a new LinkPair and assign it to the index, and exit the function
  if (ht->storage[index] == NULL)
  {
    LinkedPair *new_pair = create_pair(key, value);
    ht->storage[index] = new_pair;
    ht->count++;
    return;
  }

  // Continue if a link list exists at the array index...
  LinkedPair *curr_pair = ht->storage[index];
  LinkedPair *next_pair = curr_pair->next;

  // While key is not found in node of link list
  //    check every node until key is found or until the last node is the curr_pair
  while (next_pair != NULL && strcmp(curr_pair->key, key) != 0)
  {
    curr_pair = next_pair;
    next_pair = curr_pair->next;
  }

  // If key is found, overwrite that value
  if (strcmp(curr_pair->key, key) == 0)
  {
    printf("key is already in use, value will be overwritten...\n");
    curr_pair->value = value;
  }
  // If not, create a new pair and add it to the LinkedList (not to be confused with the index)
  else
  {
    // if it's not occupied, add a new Pair to the bucket
    LinkedPair *new_pair = create_pair(key, value);
    curr_pair->next = new_pair;
  }
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  return key;
}

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{
}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht = create_hash_table(ht->capacity * 2);

  return new_ht;
}

#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, (char *)"line_1", (char *)"Tiny hash table\n");
  hash_table_insert(ht, (char *)"line_2", (char *)"Filled beyond capacity\n");
  hash_table_insert(ht, (char *)"line_3", (char *)"Linked list saves the day!\n");

  // printf("%s", hash_table_retrieve(ht, (char *)"line_1"));
  // printf("%s", hash_table_retrieve(ht, (char *)"line_2"));
  // printf("%s", hash_table_retrieve(ht, (char *)"line_3"));

  // int old_capacity = ht->capacity;
  // ht = hash_table_resize(ht);
  // int new_capacity = ht->capacity;

  // printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  // destroy_hash_table(ht);

  return 0;
}
#endif
