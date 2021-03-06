#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 * <p>
 * @author <b>Logan Reed</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      size;        /**< size of hash table         */
  node_t** hash_table;  /**< array of linked list heads */
  char**   addr_table;  /**< look up symbols by addr    */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int table_size) {
	sym_table_t* s = malloc(sizeof(sym_table_t));
	s -> size = table_size;
	s -> hash_table = calloc(table_size, sizeof(node_t*));
	s -> addr_table = calloc(LC3_MEMORY_SIZE, sizeof(char*));
	return s;
}

/** @todo implement this function */
void symbol_add_unique (sym_table_t* symTab, const char* name, int addr) {
	int hashvalue = symbol_hash(name);// The hash value of name
	int index = hashvalue % (symTab -> size); //Is the head of the list
	//Create a node, fill it with the information, and stick it in the list
	node_t* node = malloc(sizeof(node_t));
	node -> next = symTab -> hash_table[index];//goes to rest of list
	symTab -> hash_table[index] = node;//makes it new head
	node -> hash = hashvalue;
	node -> symbol.name = strdup(name);
	node -> symbol.addr = addr;
    
	
    	if(symTab -> addr_table[addr] == NULL)
    	{
            symTab -> addr_table[addr] = node -> symbol.name;
    	}
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  return symTab -> addr_table[addr];
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data){
	for(int i = 0; i < symTab -> size; i++)
	{
		if(symTab -> hash_table[i] != NULL)
		{	
			node_t* node = symTab -> hash_table[i];
			while(node != NULL)
			{
				(*fnc)(&node -> symbol, data);
				node = node -> next;
			}
		}
	}
}


/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
	*hash = symbol_hash(name);
	*index = (*hash % symTab -> size);
	node_t* node = symTab -> hash_table[*index];
	while(node != NULL)
	{
		if(node -> hash == *hash)
		{	
			//strcmp
			if(strcasecmp(name, node -> symbol.name) == 0)
			{
				return node;
			}
		}
		node = node -> next;
	}
	return NULL;
  
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
	int hash = 0;
	int index = 0;
 	if(symbol_search(symTab, name, &hash, &index) == NULL)
	{
		symbol_add_unique(symTab, name, addr);
		return 1;
	}
	
	return 0;
		
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
  int hash = 0;
  int index = 0;
  node_t* node = symbol_search(symTab, name, &hash, &index);
	if(node != NULL)
	{
		return &(node -> symbol);
	}
	return NULL;
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
	for(int i = 0; i < symTab -> size; i++)//free's all nodes in linked list
	{
		if(symTab -> hash_table[i] != NULL)
        	{
            node_t* node = symTab -> hash_table[i];
            while(node != NULL)
            {
                node_t* temp = node -> next;
                free(node -> symbol.name);
                free(node);
                node = temp;
            }
            symTab -> hash_table[i] = NULL;//setting each head to null, after freeing each node
        }
    }
    for(int i = 0; i < LC3_MEMORY_SIZE; i++)//all pointers in addr_table set to NULL
    {
        symTab -> addr_table[i] = NULL;
    }
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
    symbol_reset(symTab);
    free(symTab->addr_table);
    free(symTab->hash_table);
    free(symTab);
}

