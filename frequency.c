#include<stdio.h>
#include<ctype.h>
#include"frequency.h"

void memoryAlloctionError(void) {

   printf("Memory allocation error. Aborting!\n");
   exit(1);
}

node* newNode(void){

   node* n;

   if(!(n = (node*)malloc(sizeof(node))))
     memoryAlloctionError();
   
   return n;
}

node* resetNode(node* n, char ch){
   n->letter = ch;
   n->count = 0;
   n->hasChild = FALSE;
   n->isEndOfWord = FALSE;
   for(int i=0 ; i<NUM_LETTERS ; ++i){ 
       (n->children)[i] = NULL;
   }
   return n; 
}

node* createNode(char ch){

   node* createdNode;
   createdNode = newNode();
   return  resetNode(createdNode, ch);
}

void freeNode(node* n){

   if(n==NULL){
     return;
   }
   if((n->hasChild) == 0){
     free(n);
   }
   else{
     for(int i=0 ; i<NUM_LETTERS ; ++i){
        freeNode((n->children)[i]);
     }
   }
   return;
}



trie* newTrie(void){

   trie* t;
   if(!(t = (trie*)malloc(sizeof(trie))))
      memoryAlloctionError();
   return t;
}



trie* resetTrie(trie* t){
   
   for(int i=0 ; i<NUM_LETTERS ; ++i){
      t->children[i] = NULL;
   }
   t->topical = NULL;
   t->empty = TRUE;
   t->MaxWordLen = 0;
   
   return t;

}



trie* createTrie(void){
   trie* createdTrie;
   createdTrie = newTrie();
   return resetTrie(createdTrie);
}

boolean isEmpty(trie* root){
    return root->empty;
}


int readLetter(trie* root, int c){
   int index;
   int wordLen = 0;
   if(!(isalpha(c))){
      if(root->topical != NULL){
        root->topical->count++;
        root->topical->isEndOfWord = TRUE;
        root->topical = NULL;
      }
      return wordLen;
   }
   wordLen++;
   c = tolower(c);
   index = c-'a';
   if(root->topical == NULL){ //new word - start from root
     if(root->children[index] == NULL)
        root->children[index] = createNode(c);
     root->topical = root->children[index];
     root->empty = FALSE;
   }
   else{
     root->topical->hasChild = TRUE;
     if(root->topical->children[index] == NULL)
        root->topical->children[index] = createNode(c);
     root->topical = root->topical->children[index];
   }
   return wordLen;
}

trie* readText(){
   
   int c;
   int wordLen;
   trie* root;
   root = createTrie();
   while((c=getchar()) != EOF){
        wordLen = readLetter(root,c);
        if(wordLen > root->MaxWordLen)
           root->MaxWordLen = wordLen;
   }
    free(root->word);
    if(!(root->word = (char*)malloc(1+sizeof(char)*(root->MaxWordLen))))
        memoryAlloctionError();
   return root;
}


void printWordsReverse(trie* root){
   
   int p = 0;
   int i;
   node* topical;
   root->word[p++] = root->topical->letter;


   if(root->topical->hasChild){
     for(i=NUM_LETTERS-1 ; i>=0 ; --i){
        if(root->topical->children[i] == NULL)
          continue;
        topical = root->topical; //remember
        root->topical = root->topical->children[i];
        printWordsReverse(root);
        root->topical = topical; //recall
        }
    }
    else{
        if(root->topical->isEndOfWord){
          root->word[p]='\0';
          printf("%s\t%ld\n", root->word, root->topical->count);
        }
        --p;
        return;
        }
    if(root->topical->isEndOfWord){
        root->word[p]='\0';
          printf("%s\t%ld\n", root->word, root->topical->count);
    }
    --p;

}



void printTrieReverse(trie* root){
     
     int i;
     if(root == NULL) return;
     if(isEmpty(root)) return;
     for(i=NUM_LETTERS-1 ; i>=0 ; --i){
        if(root->children[i] == NULL)
          continue;
        root->topical = root->children[i];
        printWordsReverse(root);
     }
}



void printWords(trie* root){

  int p = 0;
   node* topical;
   root->word[p++] = root->topical->letter;
   if(root->topical->isEndOfWord){
     root->word[p] = '\0';
     printf("%s\t%ld\n", root->word, root->topical->count);
   }
   if(root->topical->hasChild){
     for(int i=0 ; i<NUM_LETTERS ; ++i){
        if(root->topical->children[i] == NULL)
           continue;
        topical = root->topical;
        root->topical = root->topical->children[i];
        printWords(root);
        root->topical = topical;
     }
   }
   else{
        --p;
        return;
   }
   --p;
}



void printTrie(trie* root){

   if(root == NULL) return;
   if(isEmpty(root)) return;
   for(int i=0 ; i<NUM_LETTERS ; ++i){
      if(root->children[i] == NULL)
        continue;
      root->topical = root->children[i];
      printWords(root);
   }
} 





























































































































































































































































































































































