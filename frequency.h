#include<stdlib.h>
#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean; 

typedef struct node { 
  
   char letter; 
   long unsigned int count; 
   struct node* children[NUM_LETTERS];
   boolean isEndOfWord;
   boolean hasChild;
   
} node; 


typedef struct trie {
   
   node* children[NUM_LETTERS];
   node* topical;
   char* word;
   int MaxWordLen;
   boolean empty;

} trie;

void memoryAlloctionError(void);
node* newNode(void);
node* resetNode(node* n, char ch);
void freeNode(node* n);
trie* newTrie(void);
trie* resetTrie(trie* t);
trie* createTrie(void);
boolean isEmpty(trie* root);
int charIndex(char c);
int readLetter(trie* root, int c);
trie* readText();
void printWordsReverse(trie* root);
void printTrieReverse(trie* root);
void printWords(trie* root);
void printTrie(trie* root);
void usage(char* programName, char* message);
