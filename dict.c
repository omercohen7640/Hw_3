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
    free(p_dicdef);
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
    DestroyFunc p_destroyfunc = DestroyEntry; //pointer to destroyFunc
    p_dic = (pDic)malloc(sizeof(Dictionary));
    p_dic->hash_table = HashCreate(((int)_DIC_SIZE_),p_hashfunc,p_printfunc,p_comparefunc,p_getkey,p_destroyfunc);
    return p_dic;
}

/*********************************************************************************
Function name: AddTranslation
Description: add definition to the the dictionary
Parameters:
p_dic - pointer to the dictionary
word - word the user want to add
translation - the word's translation
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result AddTranslation(pDic p_dic, char* word, char* translation){
    int max_size = _MAX_WORD_SIZE;
    pDicDef p_dicdef;
    if ( p_dic == NULL || strlen(word) > max_size || strlen(translation)> max_size)
    {
        return FAIL;
    }
    else{
        p_dicdef = (pDicDef)malloc(sizeof(DicDef));
        strcpy(p_dicdef->word,word);
        strcpy(p_dicdef->translation,translation);
        return HashAdd(p_dic->hash_table,p_dicdef);
    }
}

/*********************************************************************************
Function name: Translate
Description: the function search for a definition and print the definition
Parameters:
p_dic - pointer to the dictionary
word - word the user want to print it's definition
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result Translate(pDic p_dic, char* word){
    if (word == NULL) return FAIL;
    pDicDef p_dicdef = HashFind(p_dic->hash_table,word);
    printf("Translation: %s : %s\n",p_dicdef->word,p_dicdef->translation);
    return SUCCESS;
}

/*********************************************************************************
Function name: DeleteTranslation
Description: the function search for a definition by a word and deletes it
Parameters:
p_dic - pointer to the dictionary
word - word the user want to delete it's definition
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result DeleteTranslation(pDic p_dic, char* word){
    if (word == NULL) return FAIL;
    return HashRemove(p_dic->hash_table,word);
}

/*********************************************************************************
Function name: PrintDictionary
Description: the function print all definitions in dictionary
Parameters:
p_dic - pointer to the dictionary
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result PrintDictionary(pDic p_dic){
    if (p_dic == NULL) return FAIL;
    printf("Dictionary Contents\n");
    return HashPrint(p_dic->hash_table);
}















