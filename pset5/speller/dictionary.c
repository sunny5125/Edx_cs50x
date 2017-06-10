#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "dictionary.h"

// define node structure
typedef struct node
{
    bool is_word;
    struct node* letters[27];
}
node;

//global variable
node* root;
node* cp;
int word_count;
bool isdictloaded;

void freefun(node* cp);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word){
    cp = root; 
    
    int word_len = strlen(word) + 1;
    int x;
    int c;
    for (int i = 0; i < word_len; i++){
        
        c = word[i];
        
        if (c >= 'a' && c <= 'z'){
            x = c - 'a';
        }
        else if (c >= 'A' && c <= 'Z'){
            x = c - 'A';
        }
        else if (c == '\''){
            x = c - 13;
        }
        else if (c == '\0'){
            if (cp->is_word == true){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            printf("error input word contains non-alpha or apost char !!\n");
            return false;
        }
        
        if (cp->letters[x] == NULL){
            return false;
        }
        else{
            cp = cp->letters[x];
        }
    }
    printf("error in check !!\n");
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary){
    isdictloaded = false;
    
    root = malloc(sizeof(node));
    if (root == NULL){
        printf("root pointer contains NULL");
        return false;
    }  
    
    root->is_word = NULL;
    for (int i = 0; i < 27; i++){
        root->letters[i] = NULL;
    }
    
 
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL){
        printf("opening dictionary file returns NULL");
        return false;
    }
    
    cp = root; 
    
    word_count = 0;
    int x;
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)){
        if (c != '\n'){
            if (c >= 'a' && c <= 'z'){
                x = c - 'a';
            }
            else if (c == '\''){
                x = c - 13;
            }
            else{
                printf("contains chars other than lowercase letters or apostrophes !!");
                return false;
            }
            
            if (cp->letters[x] != NULL){
                cp = cp->letters[x];
            }
            else{
                cp->letters[x] = malloc(sizeof(node));
                
                if (cp->letters[x] == NULL){
                    printf("mallocing subsequent nodes in trie, returns NULL");
                    return false;
                }
                
                cp = cp->letters[x];
                
                cp->is_word = false;
                for (int i = 0; i < 27; i++){
                    cp->letters[i] = NULL;
                }
            }
        }
        else{
            cp->is_word = true; 
            cp = root;
            word_count++;
        }        
    }
    
    fclose(fp);
    
    isdictloaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void){
    if (isdictloaded == true){
        return word_count;
    }
    else{
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void){
    // initialise cp to root
    cp = root;
    
    freefun(cp);
    
    return true;
}

void freefun(node* cp){
    for (int i = 0; i < 27; i++) {
        if (cp->letters[i] != NULL){   
         freefun(cp->letters[i]);        
     }
    }
    free(cp);      
}