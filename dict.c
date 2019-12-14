#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

typedef struct _Dic{
    pHash hash_table;
}Dictionary;

typedef struct _Dic_Def{
    char word[25];
    char translation[25];
}DicDef ;


/*********************************************************************************
Function name: HashWord
Description: hash function
Parameters:
 word - word in the dictionary
 size - size of the hash table
Return value: return the index in the hash array of the word if fails return -1
**********************************************************************************/
int HashWord(char* word, int size){
    int length = (int)strlen(word);
    if (length == 0 ) return -1; // empty word
    if (size == 0 ) return -1; //protect from zero division
    int a = (int)(word[0] - 'a')*_MAGIC_NUM_;
    return (a+length) % _DIC_SIZE_ ;
}

/*********************************************************************************
Function name: PrintEntry
Description: print a word and traslation of the dictionary
Parameters:
p_dicidef - pointer to a dictionary definition
Return value: return the index in the hash array of the word.
**********************************************************************************/
Result PrintEntry(pDicDef p_dicdef){
    if (p_dicdef == NULL) return FAIL;
    char* word = p_dicdef->word;
    char* trans = p_dicdef->translation;
    printf("%s : %s\n",word,trans);
    return  SUCCESS;
}

/*********************************************************************************
Function name: CompareWords
Description: compare between two words
Parameters:
word1
word2
Return value:return SAME or DIFFERENT.
**********************************************************************************/
CompResult CompareWords(char* word1, char* word2){
    return (strcmp(word1, word2) == 0)?(SAME):(DIFFERENT);
}

/*********************************************************************************
Function name: GetEntryKey
Description: get a definition and return the word
Parameters:
p_dicdef- pointer to a dictionary definition
Return value: return the word
**********************************************************************************/
char* GetEntryKey(pDicDef p_dicdef){
    return p_dicdef->word;
}

/*********************************************************************************
Function name: DestroyEntry
Description: get a definition and destroy it
Parameters:
p_dicdef- pointer to a dictionary definition
Return value: return FAILURE if something went wrong and SUCCES otherwise
**********************************************************************************/
Result DestroyEntry(pDicDef p_dicdef){
    if (p_dicdef == NULL) return FAIL;
    free(p_dicdef);
    return SUCCESS;
}

/*********************************************************************************
Function name: CreateDictionary
Description: create a dictionary
Parameters: no parameters
Return value: return pointer to dictionary.
**********************************************************************************/
pDic CreateDictionary(){
    pDic p_dic;
    HashFunc p_hashfunc= HashWord; //pointer to hashFunc
    PrintFunc p_printfunc = PrintEntry; //pointer to printFunc
    CompareFunc  p_comparefunc = CompareWords; //pointer to compareFunc
    GetKeyFunc p_getkey = GetEntryKey; //pointer to getKeyFunc


    p_dic->hash_table = HashCreate
}



















